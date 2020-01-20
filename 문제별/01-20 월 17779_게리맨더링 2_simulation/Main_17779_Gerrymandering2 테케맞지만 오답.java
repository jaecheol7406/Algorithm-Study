//https://www.acmicpc.net/problem/17779
import java.util.Scanner;

public class Main_17779_Gerrymandering2 {
	static int N;
	static int [] popSum = new int[5];
	static int[][] A, memo;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt(); sc.nextLine();
		A = new int[N+1][N+1];
		for(int i=1; i<=N; i++)
			for(int j=1; j<=N; j++)
				A[i][j] = sc.nextInt();//(1,1)부터 시작
		sc.close();
		
		int minDiff = Integer.MAX_VALUE;
		for(int x=1; x<=N-2; x++) 
			for(int y=2; y<=N-1; y++) 
				for(int d2=1; d2<=N-y; d2++)
					for(int d1=1; d1<=N-x-d2; d1++) 
					{
						memo = new int[N + 1][N + 1];
						popSum = new int[5];

						if(x+d1>N || y-d1<1) continue;
						if(x+d2>N || y+d2>N) continue;
						if(x+d1-d2>N || y+d2-d1<1 || y+d2-d1>N) continue;
						if(y+d2-d1 <1 || y+d2-d1>N) continue;
						if(x+d1+d2>N) continue;

						
						markPrecinct5_2(x, y, d1, d2);
						calcPop(x, y, d1, d2);
						int diff = getPopDiff();
						if(diff <= minDiff) {
							minDiff = diff;
							for(int i=0; i<=N; i++) {
								for(int j=0; j<=N; j++)
									System.out.print(memo[i][j] + " ");
								System.out.println();
							}
							System.out.printf("x=%d, y=%d, d1=%d, d2=%d\n", x, y, d1, d2);
						}
						
					}
		 System.out.println(minDiff);
		//답 인구1등과 꼴등의 차이 최솟값 ( 차이가적어야한다)
		
//		1.기준점 (x, y)와 경계의 길이 d1, d2를 정한다. (d1, d2 ≥ 1, 1 ≤ x < x+d1+d2 ≤ N, 1 ≤ y-d1 < y < y+d2 ≤ N)
	}
	static void markPrecinct5(int x, int y, int d1, int d2) {
		for(int r=x; r<=x+d1; r++)
			for(int c=y; c>=y-d1; c--) 
				memo[r][c] = 5;
		for(int r=x; r<=x+d2; r++)
			for(int c=y; c<=y+d2; c++) 
				memo[r][c] = 5;
		for(int r=x+d1; r<=x+d1+d2; r++)
			for(int c=y-d1; c<=y-d1+d2; c++)
				memo[r][c] = 5;
		for(int r=x+d2; r<=x+d2+d1; r++)
			for(int c=y+d2; c>=y+d2-d1; c--)
				memo[r][c] = 5;
	
		//경계선 내부
		for(int r= x+1; r< x+d1+d2; r++) {
			int found=0;//1이면 마크, 2가되면 안함
			for(int c=y-d1; c<=y+d2; c++) {
				if(memo[r][c] == 5) found++;
				if(found == 1)
					memo [r][c] = 5;
			}
		}
	}
	static void markPrecinct5_2(int x, int y, int d1, int d2) {//(x,y)를 for좌표에서 빼기
		
		for(int m1=0; m1<=d1; m1++) {
			memo[x + m1][y - m1] = 5;			//경계선1
			memo[x+d2 + m1][y+d2 - m1] = 5; //경계선4
		}
		for(int m2=0; m2<=d2; m2++) {
			memo[x + m2][y + m2] = 5; 			//경계선 2
			memo[x+d1 + m2][y-d1 + m2] = 5;		//경계선 3
		}
//		경계선 내부
		for(int r= 1; r< d1+d2; r++) {
			int found=0;//1이면 마크, 2가되면 안함
			for(int c=-d1; c<=d2; c++) {
				if(memo[x+r][y+c] == 5) found++;
				if(found == 1)
					memo [x+r][y+c] = 5;
			}
		}
	}

	static void calcPop(int x, int y, int d1, int d2) {
 		for(int i=1; i<x+d1; i++)
			for(int j=1; j<=y; j++) {
				if(memo[i][j] == 5)
					popSum[4] += A[i][j];
				else {
//					memo[i][j] = 1;
					popSum[0] += A[i][j];
				}
			}
		
		for(int i=1; i<=x+d2; i++)
			for(int j=y+1; j<=N; j++){
				if(memo[i][j] == 5)
					popSum[4] += A[i][j];
				else{
//					memo[i][j] = 2;
					popSum[1] += A[i][j];
				}
			}
		for(int i=x+d1; i<=N; i++)
			for(int j=1; j<y-d1+d2; j++){
				if(memo[i][j] == 5)
					popSum[4] += A[i][j];
				else{
//					memo[i][j] = 3;
					popSum[2] += A[i][j];
				}
			}
		for(int i=x+d2+1; i<=N; i++)
			for(int j=y-d1+d2; j<=N; j++){
				if(memo[i][j] == 5)
					popSum[4] += A[i][j];
				else{
//					memo[i][j] = 4;
					popSum[3] += A[i][j];
				}
			}
				
	}
	
	static int getPopDiff() {//인구차이 
		int max = 0, min= 101;
		for(int p : popSum) {
			if(max < p)
				max = p;

			if(min > p)
				min = p;
		}
		return max-min;
	}

}
