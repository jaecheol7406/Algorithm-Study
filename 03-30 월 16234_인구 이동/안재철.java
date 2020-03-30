import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
/*
 * 16234_인구 이동
 * main() -> solve() -> bfs()
 * 
 * 1. main()에서 입력받은 후 solve() 호출
 * 2. solve()에서 bfs로 국경선 열어간 후 같은 연합끼리 평균 구하고 구한 평균값 저장.
 * 3. 열 국경선 없어 연합 만들 수 없으면 break, 5. 로 넘어감
 * 4. 적어도 하나의 연합 만들 수 있으면 인구이동수 ++ 후 2. 로 돌아가 반복
 * 5. 인구이동수 (moveCount) 출력 후 종료
 */
public class Main {
	static int[] dx = {0, 0, 1, -1};
	static int[] dy = {1, -1, 0, 0};
	
	static int N,L,R;
	static int[][] map;
	static boolean[][] visit;
	
	static int moveCount;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		L = Integer.parseInt(input[1]);
		R = Integer.parseInt(input[2]);
		
		map = new int[N][N];
		for(int i = 0; i < N; i++) {
			input = br.readLine().split(" ");
			for(int j = 0; j < N; j++) {
				map[i][j] = Integer.parseInt(input[j]);
			}
		}
		
		visit = new boolean[N][N];
		
		solve();
	}
	
	static void solve() {
		while(true) {
			boolean move = false;
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					if(!visit[i][j] && bfs(i, j))
						move = true;
				}
			}
			if(!move)
				break;
			
			moveCount++;
			visit = new boolean[N][N];
		}
		System.out.println(moveCount);
	}
	
	static boolean bfs(int x, int y) {		
		List<int[]> shareList = new ArrayList<>();
		shareList.add(new int[] {x, y});
		int sum = 0;
		
		Queue<int[]> q = new LinkedList<>();
		q.add(new int[] {x, y});
		
		while(!q.isEmpty()) {
			int[] pos = q.poll();
			x = pos[0];
			y = pos[1];
			
			sum += map[x][y];
			visit[x][y] = true;
			
			for(int i = 0; i < 4; i++) {
				int nextX = x + dx[i];
				int nextY = y + dy[i];
				
				if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < N))
					continue;
				
				if(visit[nextX][nextY])
					continue;
				
				int now = map[x][y];
				int next = map[nextX][nextY];
				int diff = Math.abs(next - now);
				if(L <= diff && diff <= R) {
					q.add(new int[] {nextX, nextY});
					shareList.add(new int[] {nextX, nextY});
					visit[nextX][nextY] = true;
				}
			}
		}
		
		if(shareList.size() == 1)
			return false;
		
		int avg = sum / shareList.size();
		for(int[] pos : shareList) {
			map[pos[0]][pos[1]] = avg;
		}
		return true;
	}
}