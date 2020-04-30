/*
	���� : main �Է� - ��������ȣ,�湮�迭 ť2������ - L�ʰ� �Ǳ������� ������ ���� ����
	�˰���
	 1)���� for���� �����ϸ鼭 �������̺갡 �������� ���� ����, �����ߺ�0�� ����, (r,c)��(nr,nc)���� �������� ���ο���Ǿ��ִ��� üũ �Ѵ����� ť���߰�
	 2) ť1���� �ϸ� �ð��뺰�� �и��� �����Ƿ� Q1���� �̹����� ��ǥ��, Q2���� �����߰��Ǵ� ��ǥ�� �߰�
	 3) Q1�� ���  �ش��ʰ� �����Ƿ� Q2���� ������ Q2�ʱ�ȭ
*/
import java.awt.Point;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Ż�ֹ��˰�_��Ǯ�� {
	static final int compass[][] = {{-1,0},{0,1}, {1,0}, {0,-1}}; //�ϵ�����
	//�ϵ����� ���� �������������ع������ �� ���̺갡 ����Ǿ��ִ��� ����Ȯ��
	static final int pipeOpened[][] = { {},{1,1,1,1},{1,0,1,0}, {0,1,0,1}, {1,1,0,0},{0,1,1,0},{0,0,1,1},{1,0,0,1}};
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int testCase=sc.nextInt(); sc.nextLine();
		for(int tc=1; tc<=testCase; tc++) {
			int N=sc.nextInt(), M=sc.nextInt(), R=sc.nextInt(), C=sc.nextInt(), L=sc.nextInt(); sc.nextLine();
			int map[][] = new int[N][M];
			for(int i=0; i<N; i++) for(int j=0; j<M; j++) map[i][j]=sc.nextInt();
			
			int ansCnt=1, time=1;
			Queue<Point> Q1 = new LinkedList<>(), Q2 = new LinkedList<>();
			boolean visited[][] = new boolean[N][M];
			Q1.add(new Point(R,C));
			visited[R][C] = true;
			while(time < L)
			{
				while(! Q1.isEmpty()) {
				int r=Q1.peek().x, c=Q1.remove().y;
				
				for(int d=0; d<4; d++) {
					if( pipeOpened[ map[r][c] ][d] ==0) continue;//�Ȱ��� ���� ����
					
					int nr=r+compass[d][0], nc=c+compass[d][1];
					if(nr<0||nc<0||nr>=N||nc>=M) continue;
					if(visited[nr][nc]) continue;//4���� �����鼭 ���������� �ߺ�����
					if(map[nr][nc] ==0) continue;//���������� �κ� ����
					if(pipeOpened[ map[nr][nc] ][ (d+2)%4 ] == 0) continue;//���������ִ��� ��ȣ���� �ȵǸ� ����
					
					ansCnt++;
					visited[nr][nc] = true;;
					Q2.add(new Point(nr, nc));//����ȸ���� ����� ť�� 2���� ���
					
				}
				}
				Q1.addAll(Q2);
				Q2.clear();
				time++;
			}
			
			System.out.println("#"+tc+ " " + ansCnt);
		}
		sc.close();
		
	}
}
