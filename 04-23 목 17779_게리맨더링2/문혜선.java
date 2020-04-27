import java.util.Arrays;
/*
  순서 : main - drawnFill5 - sumPopByDistrict
  drawnFill5() : 지역구를 그리고 5번지역구 부분을 표시
  sumPopByDistrict() : 지역구 인구별로 계산해서 districtPop[]배열에 저장한다

  알고
  문제조건에 나온 수식을 그대로 가져다 써서 for문을 이용하여 조건값을 만든다
  1,4번지역구값과 2,3번지역구의 값이 유사하므로 함께 묶어서 for문을 만든다 - 2차원배열 M에 표시
  구간별로 districtPop에 저장하되 해당자리가 m인 부분은 제외한다
  5번지역구는 마름모모양 found변수를 이용해서 found==1이면 인구의 합을 더한다
  내림차순으로 정렬해 첫번째인덱스와 마지막인덱스값의 차이를 구한다
*/
import java.util.Scanner;

public class Main {
	static int N, ansDiff=Integer.MAX_VALUE;
	static int[] districtPop = new int[6];
	static int[][] A, M;//A는 인구수, M은 지역구번호
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N =sc.nextInt(); sc.nextLine();
		A = new int[N+1][N+1];
		for(int i=1; i<=N; i++)	for(int j=1; j<=N; j++)
			A[i][j] = sc.nextInt();
		sc.close();
		
	for(int x=1; x<N-2; x++)	for(int y=1; y<N-1; y++)
		for(int d2=1; d2<=N-y; d2++)	for(int d1=1; d1<=N-x-d2; d1++) 
		{
			if(x+d1+d2 > N || y-d1 <1 || y+d2 > N) continue;
			M = new int[N+1][N+1];
			districtPop = new int[6];
			drawnFill5(x, y, d1, d2);
			sumPopByDistrict(x, y, d1, d2);
			Arrays.sort(districtPop);
			int diff = districtPop[5] - districtPop[1];
			if (ansDiff > diff) 
				ansDiff = diff;
		}
		System.out.println(ansDiff);
	}
	static void drawnFill5(int x, int y, int d1, int d2) {
		for(int i=0; i<=d1; i++) {
			M[x+i][y-i] = 5;//1번
			M[x+d2 +i][y+d2 -i] = 5; //4번
		}
		for(int j=0; j<=d2; j++) {
			M[x+j][y+j] = 5; //2번
			M[x+d1 +j][y-d1 +j] = 5; //3번
		}
		for(int i=x+1; i<x+d1+d2; i++) {
			int found=0;
			for(int j=1; j<=N; j++) {
				if(M[i][j] == 5) found++;
				if(found ==2) break;
				if(found ==1) 
					M[i][j] = 5;
			}
		}
	}
	static void sumPopByDistrict(int x, int y, int d1, int d2) {
		int sum1=0;
		for(int i=1; i<x+d1; i++)	for(int j=1; j<=y; j++) {
			if(M[i][j] != 5) sum1 += A[i][j];
		}
		districtPop[1] = sum1;
		int sum2=0;
		for(int i=1; i<=x+d2; i++)	for(int j=y+1; j<=N; j++) {
			if(M[i][j] != 5) sum2 += A[i][j];
		}
		districtPop[2] = sum2;
		int sum3=0;
		for(int i=x+d1; i<=N; i++)	for(int j=1; j<y-d1+d2; j++)
			if(M[i][j] != 5) sum3 += A[i][j];
		districtPop[3] = sum3;
		int sum4=0;
		for(int i= x+d2 +1; i<=N; i++)	for(int j=y-d1+d2; j<=N; j++)
			if(M[i][j] != 5) sum4 += A[i][j];
		districtPop[4] = sum4;
		int sum5=0;
		for(int i=x; i<=x+d1+d2; i++) for(int j=y-d1; j<=y+d2; j++)
			if(M[i][j] == 5) sum5 += A[i][j];
		districtPop[5] = sum5;
		return;	
	}
}