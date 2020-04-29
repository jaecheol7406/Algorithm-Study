package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
/*
 * 1953. [모의 SW 역량테스트] 탈주범 검거
 * 
 * main -> solve
 * 
 * bfs로 좌표, 시간값 큐에 넣어 방문할 수 있는 곳 방문 표시해주면서 개수 더해나감, 시간 L 되면 끝남.
 * 방문할 수 있는지 판단은 0,1,2,3 동서남북으로 놓고, type에 구조물 1 ~ 7 까지 방향 넣어놓음.
 * 이후 한 좌표의 동서남북에 대해 각 방향의 반대방향이 존재하면 갈 수 있는것을 판단함. 
 */
public class Solution {
	static int[] dx = {0,0,1,-1};
	static int[] dy = {1,-1,0,0};
	
	static int[][] type = {{}, {0,1,2,3}, {2,3}, {0,1}, {0,3}, {0,2}, {1,2}, {1,3}};
	
	static int T, N, M, R, C, L;
	static int[][] map;
	static boolean[][] locate;
	static int locateCount;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		for(int t = 1; t <= T; t++) {
			String[] input = br.readLine().split(" ");
			N = Integer.parseInt(input[0]);
			M = Integer.parseInt(input[1]);
			R = Integer.parseInt(input[2]);
			C = Integer.parseInt(input[3]);
			L = Integer.parseInt(input[4]);
			
			map = new int[N][M];
			for(int i = 0; i < N; i++) {
				input = br.readLine().split(" ");
				for(int j = 0; j < M; j++)
					map[i][j] = Integer.parseInt(input[j]);
			}
			
			locate = new boolean[N][M];
			
			locateCount = 0;
			
			solve();
			
			System.out.println("#" + t + " " + locateCount);
		}
	}
	
	static void solve() {
		Queue<int[]> q = new LinkedList<>();
		q.add(new int[] {R,C,1});
		
		while(!q.isEmpty()) {
			int[] node = q.poll();
			int x = node[0];
			int y = node[1];
			int t = node[2];
			
			if(!locate[x][y]) {
				locate[x][y] = true;
				locateCount++;
			}
			
			if(t == L) {
				continue;
			}
			
			int[] dir = type[map[x][y]];
			for(int i = 0; i < dir.length; i++) {
				int d = dir[i];
				int nextX = x + dx[d];
				int nextY = y + dy[d];
				
				if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < M) || map[nextX][nextY] == 0)
					continue;
				
				if(locate[nextX][nextY])
					continue;
				
				int mustBe = 5 - d;
				if(d == 0 || d == 1)
					mustBe = 1 - d;
				int[] nextDir = type[map[nextX][nextY]];
				for(int j = 0; j < nextDir.length; j++) {
					int nextD = nextDir[j];
					if(nextD == mustBe) {
						q.add(new int[] {nextX, nextY, t + 1});
						break;
					}
				}
			}
		}
	}
}
