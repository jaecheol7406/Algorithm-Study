/*
	���� : main 
	�˰�
	������  ����ü�� �޾Ƽ�  list�� ����
	Ž�������� ��-��-��-�� ������ �ؼ� �켱���� ť�� ��������ʰ� bfs�� �̿�
	Ž���ؾ��� ��ǥ�� ť���־ Ž��
	
	�ȵȺκ�
	BFS�����鼭 �����ؾ� �ϴºκ��� remove����(������ �ȵ�)
	�����ۿ����� ó���� �ȵ�
*/
import java.awt.Point;
import java.util.ArrayList;
import java.util.Scanner;

public class �Ʊ���_��Ǯ�� {
	static int N, A[][], r, c, sharkSize=2, compass[][]= {{-1,0}, {0,-1}, {1,0}, {0,1}};//�ϼ�����
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N=sc.nextInt(); sc.nextLine();
		A=new int[N][N];
		ArrayList<fish> fishes = new ArrayList<>();
		boolean check[][] = new boolean[N][N]; 
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) {
			A[i][j] = sc.nextInt();
			if(A[i][j] == 9) {r=i; c=j; check[i][j]=true; continue;}
			if(A[i][j] != 0) {
				fishes.add(new fish(i, j, A[i][j]) );
			}
		}
		sc.close();
//		System.out.println(fishes.indexOf(new fish(0,2,1 )));
		
		int ansSec=0;
		ArrayList<Point> pos1 = new ArrayList<>(), pos2 = new ArrayList<>();
		pos1.add(new Point(r, c));
		check[r][c] = true;

		while(fishes.size() > 0) {//BFS
			while (!pos1.isEmpty()) {
				int x=pos1.get(0).x, y=pos1.remove(0).y;
				for (int d = 0; d < 4; d++) {
					int nr = x + compass[d][0], nc = y	 + compass[d][1];
					if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
					if(check[nr][nc]) continue;
					if (A[nr][nc] > sharkSize) continue;
					else if (A[nr][nc] != 0 && A[nr][nc] < sharkSize) {
						sharkSize++;
						A[nr][nc] = 0;
						if (fishes.remove(new fish(nr, nc, A[nr][nc] )) ==true)
//							System.out.println("1���� ��Ƹ��� ..��������" + fishes.size());
							;
					}
					check[nr][nc] = true;
					pos2.add(new Point(nr,nc));
				}
			}
			pos1.addAll(pos2);
			pos2.clear();
			ansSec++;
			
		}
		
		System.out.println(ansSec);
	}
	static class fish{
		int r, c, size;
		public fish(int r, int c, int size) {
			super();
			this.r = r;
			this.c = c;
			this.size = size;
		}
		
	}
}
