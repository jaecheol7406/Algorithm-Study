/*
	순서 : main 입력-for문으로 T초가될때까지 전체반복
	
	알고리즘 : 미세먼지확산(빈칸만 있는부분이어야하고 같은초에 동시에 퍼지므로 이중for문으로 탐색하면서 순간으로 바뀌어서 빈칸이 사라지지않도록 방지해야한다 //막혔떤부분)
			완전한 빈칸 0, 빈칸이지만 다음초부터는 미세먼지역으로 바뀜 1, 기존미세먼지나 공기청정기 2으로 표시해서 배열탐색이 끝난다음에 전체적으로 1->2로 변경시킨다
			순환부분은 순환방향과 반대방향으로 덮어쓰기로한다. 단 공기청정기근처부분은 제외한다
			t초 for문이 끝난후에  -1값을 제외하고 A값의 누적합을 구한다
	
*/
import java.util.Arrays;
import java.util.Scanner;

public class 미세먼지안녕_내풀이 {
	static int R, C, T, ansDust=0, A[][], compass[][] ={{0,-1},{-1,0},{0,1},{1,0}};
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		R=sc.nextInt(); C=sc.nextInt(); T=sc.nextInt(); sc.nextLine();
//		완전한 빈칸 0, 빈칸이지만 다음초부터는 미세먼지역으로 바뀜 1, 기존미세먼지나 공기청정기 2
		int mapD[][] = new int[R][C];
		A=new int[R][C];
		for(int i=0; i<R; i++) for(int j=0; j<C; j++) {
			A[i][j] = sc.nextInt();
			if(A[i][j] != 0 || A[i][j] == -1)
				mapD[i][j] = 2;
		}
		sc.close();
		
		for(int i=0; i<R; i++) for(int j=0; j<C; j++) {
		}
		
		for(int sec=0; sec<T; sec++) {
			//미세먼지확산
			for(int i=0; i<R; i++) for(int j=0; j<C; j++) {
				if(A[i][j]==-1 || A[i][j]==0) continue;
				int subCnt=0;
				for(int d=0; d<4; d++) {
					int ni=i+compass[d][0], nj=j+compass[d][1];
					if(ni<0 || nj<0 || ni>=R || nj>=C) continue;
					if(A[ni][nj] == -1) continue;
					if(mapD[ni][nj] ==2) continue;
					subCnt++;
					mapD[ni][nj] = 1;
					A[ni][nj] += A[i][j]/5;
				}
				A[i][j] -= A[i][j]/5 * subCnt;
			}
			
			for(int i=0; i<R; i++) for(int j=0; j<C; j++) 
				if(mapD[i][j] == 1)
					mapD[i][j] = 2;
			for(int i=0; i<R; i++)
			System.out.println(Arrays.toString(A[i]));
			
			int r=0,c=0;
			while(A[r][0]==-1) r++;
			int r1=r,  r2=r+1;
			
			while(r>1) { A[r-1][0] = A[r-2][0]; r--;}
			while(c<C -1) { A[0][c] = A[0][c+1]; c++;}
			r=0;
			while(r<r1 -1) {A[r][C-1]=A[r+1][C-1]; r++;}
			c=1;
			while(c<C-1) {A[r1][c+1]=A[r1][c]; c++;}
			
			
		}
		
		for(int i=0; i<R; i++) for(int j=0; j<C; j++) 
			if(A[i][j]!=-1 && A[i][j]!=0) 
				ansDust += A[i][j];
		System.out.println(ansDust);
	}

}
