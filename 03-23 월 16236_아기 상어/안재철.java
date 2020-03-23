import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
/*
 * 16236_아기 상어 (실패, 디버깅중)
 * 1. input
 * 		baby : 현재 아기상어 위치 저장
 * 		babySize : 아기상어 크기
 * 		eatCount : 먹은횟수(크기 커지면 0으로 초기화)
 * 		T : 전체 시간
 * 2. solve() 에서 매 반복문마다 bfs() 호출
 * 3. bfs() 
 * 		현재 아기상어 위치(baby) 기준으로 북, 서 순으로  탐색해서 잡아먹을 수 있는 상어 처음 만나면 그 위치가 최단거리이므로 잡아먹은 후 return true 해서 끝내고 2.로 복귀
 * 		(잡아먹을 때 bfs에 저장한 시간 T에 더함)
 * 		만약 return false 되면 잡아먹을 수 있는 상어가 없단 뜻이므로 반목문 종료, 4.로 점프
 * 4. T 출력
 * 		
 */
public class Main2 {
	static int[] dx = {-1, 0, 1, 0};
	static int[] dy = {0, -1, 0, 1};
	
	static int N;
	static int[][] map;
	static boolean[][] visit;
	
	static int[] baby;
	static int babySize = 2;
	static int eatCount;
		
	static int T;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		map = new int[N][N];
		for(int i = 0; i < N; i++) {
			String[] input = br.readLine().split(" ");
			for(int j = 0; j < N; j++) {
				int n = Integer.parseInt(input[j]);
				if(n != 0)
					map[i][j] = n;
				
				if(n == 9)
					baby = new int[] {i, j};
			}
		}
		
		solve();
	}
	
	static void solve() {
		while(true) {
			visit = new boolean[N][N];
			if(!bfs())
				break;
		}
		System.out.println(T);
	}
	
	static boolean bfs() {
		Queue<int[]> q = new LinkedList<int[]>();
		int[] firstinfo = new int[] {baby[0], baby[1], 0};
		q.add(firstinfo);
		
		while(!q.isEmpty()) {
			int[] info = q.poll();
			int x = info[0];
			int y = info[1];
			int t = info[2];
			visit[x][y] = true;
			
			if(1 <= map[x][y] && map[x][y] <= 6 && babySize > map[x][y]) {
				map[x][y] = 9;
				map[baby[0]][baby[1]] = 0;
				baby = new int[] {x, y};
				if(++eatCount == babySize) {
					babySize++;
					eatCount = 0;
				}
				
				T += t;
				
				return true;
			}
			
			for(int i = 0; i < 4; i++) {
				int nextX = x + dx[i];
				int nextY = y + dy[i];
				
				if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < N))
					continue;
				
				if(visit[nextX][nextY])
					continue;
				
				if(map[nextX][nextY] != 0 && babySize < map[nextX][nextY])
					continue;
				
				q.add(new int[] {nextX, nextY, t + 1});
				visit[nextX][nextY] = true;
			}
		}
		
		return false;
	}
}