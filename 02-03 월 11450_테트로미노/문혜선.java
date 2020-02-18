// 162552 KB, 1008 ms, 2658 B
import java.util.Scanner;

public class 테트로미노_내풀이 {
	static int N, M, resultMax=0;
	static int[][] A;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt(); M = sc.nextInt(); sc.nextLine();
		A = new int [N][M];
		for(int i=0; i<N; i++)
			for(int j=0; j<M; j++)
				A[i][j] = sc.nextInt();
		sc.close();
//	테트로미노 하나를 적절히 놓아서 테트로미노가 놓인 칸에 쓰여 있는 수들의 합을 최대로 하는 프로그램을 작성 -> map안에 여러개를 넣는게 아니라 1개만 넣어 점수를 많이 얻는 방식 
		skyblue();
		yellow();
		shape3x2();
		shape2x3();
		
		System.out.println(resultMax);
	}
	static void skyblue() {
		//가로4칸
		for(int i=0; i<N; i++)
			for(int j=0; j<M-3; j++) {
				int localSum= A[i][j] + A[i][j+1] + A[i][j+2] + A[i][j+3];
				resultMax = Math.max(resultMax, localSum);
			}
				
		//세로4칸
		for(int i=0; i<N-3; i++)
			for(int j=0; j<M; j++) {
				int localSum= A[i][j] + A[i+1][j] + A[i+2][j] + A[i+3][j];
				resultMax = Math.max(resultMax, localSum);
			}
	}
	static void yellow() {
		for(int i=0; i<N-1; i++)
			for(int j=0; j<M-1; j++) {
				int localSum= A[i][j] + A[i][j+1] + A[i+1][j] + A[i+1][j+1];
				resultMax = Math.max(localSum, resultMax);
			}
				
	}
//	총 6칸 > 현재까지Max + 2개 이면 최댓값 갱신
	static void shape3x2() {
		for(int i=0; i<N-2; i++)
			for(int j=0; j<M-1; j++) 
			{ 
				int sum6 = A[i][j] + A[i][j+1] + A[i+1][j] + A[i+1][j+1] + A[i+2][j] + A[i+2][j+1];

				if(A[i][j] + resultMax < sum6) {//13 15 16
					resultMax = Math.max(sum6- A[i][j] - A[i+1][j], resultMax);
					resultMax = Math.max(sum6- A[i][j] - A[i+2][j], resultMax);
					resultMax = Math.max(sum6- A[i][j] - A[i+2][j+1], resultMax);
				}
				if (A[i][j+1] + resultMax < sum6) {// 24 25 26
					resultMax = Math.max(sum6- A[i][j+1] - A[i+1][j+1], resultMax);
					resultMax = Math.max(sum6- A[i][j+1] - A[i+2][j], resultMax);
					resultMax = Math.max(sum6- A[i][j+1] - A[i+2][j+1], resultMax);
				}
				resultMax = Math.max(sum6- A[i+1][j] - A[i+2][j], resultMax);//35
				resultMax = Math.max(sum6- A[i+1][j+1] - A[i+2][j+1], resultMax);//46
				
			}
	} 
	static void shape2x3() {//총 8가지
		for(int i=0; i<N-1; i++)
			for(int j=0; j<M-2; j++) 
			{
				int sum6 = A[i][j] + A[i][j+1] + A[i][j+2] + A[i+1][j] + A[i+1][j+1] + A[i+1][j+2];
				  
				if(A[i][j] + resultMax < sum6) {//12 13 16 
					resultMax = Math.max(sum6- A[i][j] - A[i][j+1], resultMax);
					resultMax = Math.max(sum6- A[i][j] - A[i][j+2], resultMax);
					resultMax = Math.max(sum6- A[i][j] - A[i+1][j+2], resultMax);
				}
				resultMax = Math.max(sum6- A[i][j+1] - A[i][j+2], resultMax);//23
				resultMax = Math.max(sum6- A[i][j+2] - A[i+1][j], resultMax);//34
				if (A[i + 1][j] + resultMax < sum6) {
					resultMax = Math.max(sum6 - A[i+1][j] - A[i+1][j+1], resultMax);// 45
					resultMax = Math.max(sum6 - A[i+1][j] - A[i+1][j+2], resultMax);// 46
				}
				resultMax = Math.max(sum6- A[i+1][j+1] - A[i+1][j+2], resultMax);//56
			}
	}   
}
/*
4 4
0 0 0 0
0 0 1 0
0 0 2 3
0 0 4 0

에서 9라고 오답뜬다! -> 고침(오타)

*/