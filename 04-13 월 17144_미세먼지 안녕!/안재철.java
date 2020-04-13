package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 17144_미세먼지 안녕!
 * 
 * main -> solve -> clean
 * 
 * solve에서 확산 후 clean 함수로 청소.
 * 
 * 확산 : map의 중앙 미세먼지 감소시키고, N * M temp 행렬 만든 후 확산으로 인해 추가된 미세먼지정보 저장함. 이후 temp에 있는 값들 map에 모두 더함.
 * clean에서는 up, down 따로 좌표 증가, 감소시키며 값 밀어나감.
 */
public class Main2 {
	static int[] dx = {0,0,1,-1};
	static int[] dy = {1,-1,0,0};

	static int N, M, T;
	static int[][] map;

	static int[] up = new int[2];
	static int[] down = new int[2];
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		T = Integer.parseInt(input[2]);
		
		boolean find = false;
		map = new int[N][M];
		for(int i = 0; i < N; i++) {
			input = br.readLine().split(" ");
			for(int j = 0; j < M; j++) {
				map[i][j] = Integer.parseInt(input[j]);

				if(find)
					continue;
				
				if(map[i][j] == -1) {
					find = true;
					up[0] = i;
					up[1] = j;
					down[0] = i + 1;
					down[1] = j;
				}
			}
		}

		System.out.println(solve());
	}

	static int solve() {
		int t = 0;
		while(true) {
			int[][] temp = new int[N][M];
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < M; j++) {
					if(map[i][j] <= 0)
						continue;
					
					int spread = map[i][j] / 5;

					for(int k = 0; k < 4; k++) {
						int nextX = i + dx[k];
						int nextY = j + dy[k];

						if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < M))
							continue;

						if(map[nextX][nextY] == -1)
							continue;

						temp[nextX][nextY] += spread;
						map[i][j] -= spread;
					}
				}
			}
			
			if(++t == T) {
				int sum = 0;
				for(int i = 0; i < N; i++) {
					for(int j = 0; j < M; j++) {
						map[i][j] += temp[i][j];
						sum += map[i][j];
					}
				}
				return sum - clean() + 2;
			}
			
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < M; j++) {
					map[i][j] += temp[i][j];
				}
			}
			clean();
		}
	}
	
	static void print() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++)
				System.out.print(map[i][j] + " ");
			System.out.println();
		}
		System.out.println();
	}
	
	static int clean() {
		int cleanAmount = 0;
		
		int upX = up[0];
		int upY = up[1];

		int prev = 0;
		while(true) {
			if(++upY == M)
				break;

			int now = map[upX][upY];
			map[upX][upY] = prev;
			prev = now;
		}
		upY--;

		while(true) {
			if(--upX == -1)
				break;

			int now = map[upX][upY];
			map[upX][upY] = prev;
			prev = now;
		}
		upX++;

		while(true) {
			if(--upY == -1)
				break;

			int now = map[upX][upY];
			map[upX][upY] = prev;
			prev = now;
		}
		upY++;

		while(true) {
			if(++upX == up[0]) {
				cleanAmount += prev;
				break;
			}

			int now = map[upX][upY];
			map[upX][upY] = prev;
			prev = now;
		}		
		
		
		int downX = down[0];
		int downY = down[1];

		prev = 0;
		while(true) {
			if(++downY == M)
				break;

			int now = map[downX][downY];
			map[downX][downY] = prev;
			prev = now;
		}
		downY--;

		while(true) {
			if(++downX == N)
				break;

			int now = map[downX][downY];
			map[downX][downY] = prev;
			prev = now;
		}
		downX--;

		while(true) {
			if(--downY == -1)
				break;

			int now = map[downX][downY];
			map[downX][downY] = prev;
			prev = now;
		}
		downY++;
		
		while(true) {
			if(--downX == down[0]) {
				cleanAmount += prev;
				break;
			}

			int now = map[downX][downY];
			map[downX][downY] = prev;
			prev = now;
		}
		
		return cleanAmount;
	}
}