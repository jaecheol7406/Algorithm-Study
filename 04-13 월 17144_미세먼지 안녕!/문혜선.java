/*
	���� : main �Է�-for������ T�ʰ��ɶ����� ��ü�ݺ�
	
	�˰��� : �̼�����Ȯ��(��ĭ�� �ִºκ��̾���ϰ� �����ʿ� ���ÿ� �����Ƿ� ����for������ Ž���ϸ鼭 �������� �ٲ� ��ĭ�� ��������ʵ��� �����ؾ��Ѵ� //�������κ�)
			������ ��ĭ 0, ��ĭ������ �����ʺ��ʹ� �̼����������� �ٲ� 1, �����̼������� ����û���� 2���� ǥ���ؼ� �迭Ž���� ���������� ��ü������ 1->2�� �����Ų��
			��ȯ�κ��� ��ȯ����� �ݴ�������� �������Ѵ�. �� ����û�����ó�κ��� �����Ѵ�
			t�� for���� �����Ŀ�  -1���� �����ϰ� A���� �������� ���Ѵ�
	
*/
import java.util.Arrays;
import java.util.Scanner;

public class �̼������ȳ�_��Ǯ�� {
	static int R, C, T, ansDust=0, A[][], compass[][] ={{0,-1},{-1,0},{0,1},{1,0}};
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		R=sc.nextInt(); C=sc.nextInt(); T=sc.nextInt(); sc.nextLine();
//		������ ��ĭ 0, ��ĭ������ �����ʺ��ʹ� �̼����������� �ٲ� 1, �����̼������� ����û���� 2
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
			//�̼�����Ȯ��
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
