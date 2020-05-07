package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
/*
 * 17135_캐슬 디펜스 (틀렸습니다.)
 * 
 * solve -> copy, (simulation -> attack, down)
 * 
 * 조합으로 궁수 3군데 배치해놓고, simulation 돌려본다.
 * simulation에서는 attack, down 으로 적 죽이고 내리는 것을 적이 모두 없어질 때까지  반복한다.
 * attack으로 죽이는데 거리가 같으면 가장 왼쪽꺼 죽이기 때문에 서북남 순으로 bfs 돌려서 적 있으면 죽인다.(가장 처음 만나는 적이 가장 가깝고 왼쪽일 것이다.)
 *  
 * 
 * 반례
 * 10 10 8
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
28
 */
public class Main {
	static int[] dx = {0,-1,1}; // 서북남
	static int[] dy = {-1,0,0};
	
	static int N,M,D;
	static int[][] map;
	static int enemyNum;
	static int archerNum = 3;
	static int[] archerPos = new int[archerNum];
	static int maxRemove;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		D = Integer.parseInt(input[2]);
		
		map = new int[N][M];
		for(int i = 0; i < N; i++) {
			input = br.readLine().split(" ");
			for(int j = 0; j < M; j++) {
				map[i][j] = Integer.parseInt(input[j]);
				if(map[i][j] == 1)
					enemyNum++;
			}
		}
		
		solve();
		System.out.println(maxRemove);
	}
	
	static void solve() {
		for(int i = 0; i < M - 2; i++) {
			for(int j = i + 1; j < M - 1; j++) {
				for(int k = j + 1; k < M; k++) {
					archerPos[0] = i;
					archerPos[1] = j;
					archerPos[2] = k;
					
					int[][] temp = copy(map);
					if(simulation(temp)) {
						maxRemove = enemyNum;
						return;
					}
				}
			}
		}
	}
	
	static boolean simulation(int[][] map) {
		int remove = 0;
		int tempEnemyNum = enemyNum;
		
		if(enemyNum == 0)
			return true;
		
		while(true) {
			int re = attack(map);
			remove += re;
			tempEnemyNum -= re;
			if(remove == enemyNum)
				return true;
			if(tempEnemyNum == 0)
				break;
			
			re = down(map);
			tempEnemyNum -= re;
			if(tempEnemyNum == 0)
				break;
		}
		
		if(remove > maxRemove)
			maxRemove = remove;
		return false;
	}
	
	static int attack(int[][] map) {
		int remove = 0;
		int[][] removePos = new int[archerNum][2];
		for(int i = 0; i < archerNum; i++) {
			removePos[i][0] = -1;
			
			int pos = archerPos[i];
			
			boolean[][] visit = new boolean[N][M];
			Queue<int[]> q = new LinkedList<>();
			q.add(new int[] {N - 1, pos, 0});
			visit[N - 1][pos] = true;
			
			while(!q.isEmpty()) {
				int[] info = q.poll();
				int x = info[0];
				int y = info[1];
				int dist = info[2];
				
				if(map[x][y] == 1) {
					removePos[i][0] = x;
					removePos[i][1] = y;
					break;
				}
				
				if(dist == D - 1)
					continue;
				
				for(int j = 0; j < 3; j++) {
					int nx = x + dx[j];
					int ny = y + dy[j];
					
					if(!(0 <= nx && nx < N && 0 <= ny && ny < M) || visit[nx][ny])
						continue;
					
					q.add(new int[] {nx, ny, dist + 1});
					visit[nx][ny] = true;
				}
			}
		}
		
		for(int i = 0; i < archerNum; i++) {
			int[] p = removePos[i];
			if(p[0] == -1)
				continue;
			
			if(map[p[0]][p[1]] == 1) {
				map[p[0]][p[1]] = 0;
				remove++;
			}
		}
		
		return remove;
	}
	
	static int down(int[][] map) {
		int remove = 0;
		for(int j = 0; j < M; j++) {
			if(map[N - 1][j] == 1)
				remove++;
		}
		
		for(int i = N - 2; i >= 0; i--) {
			map[i + 1] = map[i].clone();
		}
		
		map[0] = new int[M];
		
		return remove;
	}
	
	static int[][] copy(int[][] map) {
		int[][] temp = new int[map.length][map[0].length];
		for(int i = 0; i < map.length; i++)
			temp[i] = map[i].clone();
		return temp;
	}
}