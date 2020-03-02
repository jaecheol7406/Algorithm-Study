/*
  	봄/여름, 가을/겨울을 묶어서 각각 이중for문
	봄에 죽은 나무는 바로 더하지않고, int soil에 담아 나무탐색이 끝난후 양분에 더한다
	한 좌표에 2개이상의 나무가 들어가므로 2차원 ArrayList
	
	<착각>
	문제좌표 1부터, 코딩은 0부터 -> 입력좌표-1
	양분초기값이 S [][] != A[][]  S=5로 고정이다
	
 */
import java.util.ArrayList;
import java.util.Scanner;

public class 나무제태크_내풀이 {
	static int N, M, K, ansSurvivor=0;
	static int [][] A, S, compass = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
	static ArrayList<Integer> T [][];

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N =sc.nextInt(); M =sc.nextInt(); K =sc.nextInt(); sc.nextLine();
		A = new int [N][N];//양분
		S = new int [N][N];//양분
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) A[i][j] = sc.nextInt();
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) S[i][j] = 5;
		T = new ArrayList[N][N];//나무정보
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) T[i][j] = new ArrayList<>();
		for(int i=0; i<M; i++) {
			int r=sc.nextInt(), c=sc.nextInt();
			T[r-1][c-1].add(sc.nextInt());
		}
		sc.close();
		
		for(int y=0; y<K; y++) 
		{
			for(int i=0; i<N; i++) for(int j=0; j<N; j++) {
				if(T[i][j].size() ==0) continue;
				T[i][j].sort(null);
				int soil=0;
				for(int k=0; k<T[i][j].size(); k++) {
					int age= T[i][j].get(k);
					if(S[i][j] >= age) {
						S[i][j] -= age;
						T[i][j].set(k, age +1);
					}
					else {
						soil += age / 2;
						T[i][j].remove(k); k--;
					}
				}
				S[i][j] += soil;
			}
			for(int i=0; i<N; i++) for(int j=0; j<N; j++) {
				S[i][j] += A[i][j];//겨울
				if(T[i][j].size() ==0) continue;//가을
				boolean flag=false;
				for(int a : T[i][j]) if(a%5 ==0) flag=true;//나이가 5의배수인 나무가 1개만있어도 true
				if(! flag) continue;
				
				for(int d=0; d<8; d++) {
					int ni = i+compass[d][0], nj = j+compass[d][1];
					if(ni<0 || nj<0 || ni>=N || nj>=N) continue;
					T[ni][nj].add(1);
				}
			}
		}
		for(int i=0; i<N; i++) for(int j=0; j<N; j++)
			ansSurvivor += T[i][j].size();
			
		System.out.println(ansSurvivor);
	}
}
