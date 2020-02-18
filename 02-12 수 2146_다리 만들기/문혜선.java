//365924 KB, 2184 ms, 1931 B
import java.util.*;

public class Main {
	static int N, ansMin=Integer.MAX_VALUE;
	static int [][] map, G, D,  compass= {{0,1}, {0,-1}, {1,0}, {-1,0}};

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt(); sc.nextLine();
		// map = M = new int[N][N]; 얇은복사
		map = new int[N][N];
		G = new int[N][N];//Group
		D = new int[N][N];
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < N; j++)
				map[i][j] = sc.nextInt();
		sc.close();

		int colorNum = 1;
		for (int i = 0; i < N; i++)	for (int j = 0; j < N; j++)
				if (map[i][j] == 1 && G[i][j] ==0)
					numbering_DFS(i, j, colorNum++);
		
		Queue<P> que;
		for(int n=1; n<colorNum; n++) 
		{
			que = new LinkedList<P>();
			for (int i = 0; i < N; i++)	for (int j = 0; j < N; j++) 
			{
				D[i][j] = -1; 
				if(G[i][j] != n) continue;
				D[i][j] = 0;
				que.add(new P(i, j));
			}
				while(! que.isEmpty()) {
					P p = que.poll();
					for(int d=0; d<4; d++) 
					{
						int ni = p.x+compass[d][0], nj = p.y+compass[d][1];
						if(ni<0 || nj<0 || ni>=N || nj>=N) continue;
						if(D[ni][nj] != -1) continue;
						D[ni][nj] = 1 + D[p.x][p.y]; 
						que.add(new P(ni,nj));
					}
				}
				
			for (int i=0; i<N; i++) for (int j=0; j<N; j++) 
                if (G[i][j]!=0) 
                	if(D[i][j] != 0)
                    if (D[i][j]-1 < ansMin) 
                        ansMin = D[i][j]-1;
			
		}
	
		System.out.println(ansMin);
	}
	static void numbering_DFS(int i, int j, int colorNum) {//구역별로 전체번호 매기기
		map[i][j] = 0;
		G[i][j] = colorNum;
		for (int d = 0; d < 4; d++) 
		{
			int ni = i + compass[d][0], nj = j + compass[d][1];
			
			if (ni < 0 || nj < 0 || ni >= N || nj >= N) continue;
			if (map[ni][nj] == 0) continue;
			numbering_DFS(ni, nj, colorNum);
		}
		return;
	}
	static class P{
		int x, y;
		public P(int x, int y) {
			this.x = x;
			this.y = y;
		}
		
	}
}
	