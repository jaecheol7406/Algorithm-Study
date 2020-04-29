package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
/*
 * 11559_Puyo Puyo
 * 
 * main -> solve -> bfs, down
 * 
 * 문제 그대로 구현하였다.
 * bfs로 4개 이상인 곳 찾아 터뜨리고, 내리는 걸 더이상 터지지 않을 때 까지 반복한다.
 * 
 */
public class Main {
	static int[] dx = {0,0,1,-1};
	static int[] dy = {1,-1,0,0};
	
	static int N = 12, M = 6;
	static char[][] map;
	static boolean[][] visit;

	static int combo;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		map = new char[N][M];
		for(int i = 0; i < N; i++) {
			String s = br.readLine();
			for(int j = 0; j < M ;j++)
				map[i][j] = s.charAt(j);
		}
		
		solve();
	}
	
	static void solve() {
		int startX = 0;
		while(true) {
			visit = new boolean[N][M];
			
			boolean flag = false;
			boolean flag2 = false;
			
			for(int i = startX; i < N; i++) {
				for(int j = 0; j < M; j++) {
					if(map[i][j] == '.')
						continue;
					
					if(!flag) {
						flag = true;
						startX = i;
					}
					
					if(visit[i][j])
						continue;
					
					if(bfs(i, j, map[i][j]) && !flag2)
						flag2 = true;
				}
			}
			
			if(!flag2)
				break;
			
			combo++;
			
			down();
		}
		
		System.out.println(combo);
	}
	
	static boolean bfs(int startX, int startY, char color) {
		Queue<int[]> q = new LinkedList<int[]>();
		q.add(new int[] {startX, startY});
		visit[startX][startY] = true;
		
		List<int[]> poss = new ArrayList<>();
		
		while(!q.isEmpty()) {
			int[] pos = q.poll();
			int x = pos[0];
			int y = pos[1];
			
			poss.add(pos);
			
			for(int i = 0; i < 4; i++) {
				int nextX = x + dx[i];
				int nextY = y + dy[i];
				
				if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < M))
					continue;
				
				if(visit[nextX][nextY] || color != map[nextX][nextY])
					continue;
				
				q.add(new int[] {nextX, nextY});
				visit[nextX][nextY] = true;
			}
		}
		
		if(poss.size() >= 4) {
			for(int[] pos : poss) {
				map[pos[0]][pos[1]] = '.';
			}
			
			return true;
		}

		return false;
	}
	
	static void down() {
		for(int j = 0; j < M; j++) {
			int idx = N - 1;
			for(int i = N - 1; i >= 0; i--) {
				if(map[i][j] != '.') {
					map[idx][j] = map[i][j];
					if(idx-- != i)
						map[i][j] = '.';
				}
			}
		}
	}
}