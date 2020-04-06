import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
/*
 * 17142_연구소 3
 */
public class Main2 {
	static int[] dx = {0,0,1,-1};
	static int[] dy = {1,-1,0,0};
	
	static int N, M;
	static int[][] map;
	static ArrayList<int[]> possible = new ArrayList<>();
	static int empty;
	
	static Queue<int[]> active = new LinkedList<>();
	static int min;

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		
		min = N * N;
		
		map = new int[N][N];
		for(int i = 0; i < N; i++) {
			input = br.readLine().split(" ");
			for(int j = 0; j < N; j++) {
				int v = Integer.parseInt(input[j]);
				map[i][j] = v;

				if(v == 2)
					possible.add(new int[] {i, j});
				else if(v == 0)
					empty++;
			}
		}

		solve();
		if(min == N * N)
			System.out.println(-1);
		else
			System.out.println(min);
	}

	static void solve() {
		if(empty == 0) {
			System.out.println(0);
			System.exit(0);
		}
		
		dfs(new boolean[possible.size()], new int[M], 0, 0);
	}

	static void dfs(boolean[] check, int[] arr, int start, int idx) {
		if(idx == M) {
			
			active = new LinkedList<>();
			int[][] temp = copyOf(map);
			
			for(int i = 0; i < M; i++) {
				int[] possiblePos = possible.get(arr[i]);
				temp[possiblePos[0]][possiblePos[1]] = 3;
				active.add(possiblePos);
			}
			
			spread(temp);

			return;
		}

		for(int i = start; i < possible.size(); i++) {
			if(!check[i]) {
				check[i] = true;
				arr[idx] = i;
				dfs(check, arr, i + 1, idx + 1);
				check[i] = false;
			}
		}
	}
	// 2차원배열 복사
	static int[][] copyOf(int[][] source){
		int[][] copy = new int[source.length][source[0].length];

		for(int i = 0; i < source.length; i++) {
			copy[i] = source[i].clone();
		}

		return copy;
	}
	
	static void print(int[][] map) {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				System.out.print(map[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
	}
	
	static void spread(int[][] map) { // 0 : 빈칸, 1 : 벽, 2 : 비활성화, 3 : 활성화
		int t = 0;
		int emp = empty;
		
		while(true) {
			t++;
						
			int qSize = active.size();
			for(int i = 0; i < qSize; i++) {
				int[] act = active.poll();
				
				for(int k = 0; k < 4; k++) {
					int nextX = act[0] + dx[k];
					int nextY = act[1] + dy[k];
					
					if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < N))
						continue;
					
					if(map[nextX][nextY] == 1 || map[nextX][nextY] == 3)
						continue;
					
					if(map[nextX][nextY] == 0)
						emp--;
					
					map[nextX][nextY] = 3;
					
					active.add(new int[] {nextX, nextY});
				}
			}
			
			if(emp == 0) {
				min = Integer.min(min, t);
				return;
			}
			
			if(t >= N * N)
				return;
		}
	}
}