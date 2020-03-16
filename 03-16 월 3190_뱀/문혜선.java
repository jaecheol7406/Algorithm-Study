//15924 KB, 164 ms, 1448 B
import java.util.ArrayList;
import java.util.Scanner;
/*
 * ���� ��ġ�ϴ°��� Arraylist��   ��ǥ�� �߰��Ͽ� snakePosť
 * 			���� ����, ������ġ, ��ǥ �߰����� for-each�˻�
 * 
 * �����ɸ��κ� 
 * 1) ���� + ����� ���ٿ� �Է¹����� ����ó���κ� next()�δ� char�Է��� �ȵ�
 *  		  String���ιް� charAt(0)
 * 2) �迭������ for���Ǻ����� ���鶧 : i���� ���� �ִ°� ���Ծ �ε�������
 */

public class Main {
	static int N, K, L, A[][], ansSec=1, compass[][] ={{0,1}, {1,0}, {0,-1}, {-1,0}};
	static ArrayList<P> snakePos = new ArrayList<>();
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N =sc.nextInt(); sc.nextLine(); K =sc.nextInt(); sc.nextLine();
		A = new int[N][N];
		for(int i=0; i<K; i++) 
			A[sc.nextInt() -1][sc.nextInt() -1] = 5;
		L = sc.nextInt(); sc.nextLine();
		int[][] changeDir = new int[L][2];
		for(int i=0; i<L; i++) {
			changeDir[i][0] = sc.nextInt(); 
			char c = sc.next().charAt(0); sc.nextLine();
			if(c == 'D') changeDir[i][1]=1; else changeDir[i][1]=-1;
			
		}
		sc.close();
		int dir=0, r=0, c=0;
		
		snakePos.add(new P(0,0));
		loop :
		while(true) {
			int nr =r+compass[dir][0], nc = c+compass[dir][1];
//			�������� : ���� �����ų� �ڽŰ� �ε���
			if(nr<0 || nr>=N || nc<0 || nc>=N) break;
			for(P p : snakePos) 
				if(nr==p.r && nc==p.c) 
					break loop;
			
//			��������鼭 ��ġ�̵�
			snakePos.add(new P(nr,nc));//���ο� ��ġ��
			if(A[nr][nc] == 5) //����� 5
				A[nr][nc] =0;//1ĭ�� ����� 1���� �ִٰ� �����ϹǷ� ����������� ���� 0
			else 
				snakePos.remove(0);//����� �ȸ�����츸 ��ġ�̵��ϸ鼭 ù������
			
//			x�ʰ� �Ǹ� ���� �ٲٱ�
			int i=0;
			for(; i<L && changeDir[i][0] <= ansSec; i++) {//�ɺ������� �迭���϶� ����
				if(changeDir[i][0] != ansSec) continue;
				
				int nDir = (dir + changeDir[i][1]) % 4;
				if(nDir == -1) nDir=3;
				dir = nDir;
			}
//			���� loop�� ���� �����ǰ��� ���ο���� �ٲٱ�
			r=nr; c=nc; 
			
			ansSec++;
		}
		System.out.println(ansSec);
	}
	static class P{
		int r, c;
		public P(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}
}