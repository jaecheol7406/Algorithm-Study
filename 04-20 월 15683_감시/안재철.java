package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
/*
 * 15683_감시
 * 
 * main -> solve -> dfs -> copy, see
 * 
 * cctv의 방향정보를 CCTV 배열에 3차원배열로 1 ~ 5 인덱스에 저장해놓는다 (각각의 cctv는 2차원배열로, 반복문으로 한번에 순회하기 위해 모두 2차원배열로 두었다.)
 * 이후 cctvs에 cctv가 있는 좌표 저장해놓고,  각 cctv에 대해 탐색할 수 있는 모든 방향에 대해 탐색해본다.
 * 이때 각 재귀함수에서는 현재 map 상태를 넘겨 temp에 복사한 후 see 함수로 해당 방향에 대해 탐색해 탐색된 곳을 7로 저장해놓는다.
 */
public class Main {
	static int[] dx = {0,0,1,-1}; // 동서남북
	static int[] dy = {1,-1,0,0};
	
	static int[][][] CCTV = {{{}},
			{{0}, {1}, {2}, {3}}, // 1번 : 동, 서, 남, 북
			{{0,1}, {2,3}}, // 2번 : 동서, 남북
			{{0, 3}, {0, 2}, {1, 2}, {1, 3}}, 
			{{1,2,3}, {0,2,3}, {0,1,3}, {0,1,2}}, 
			{{0,1,2,3}}};
	
	static int N, M;
	static int[][] map;
	static ArrayList<int[]> cctvs = new ArrayList<>();  
	static int empty;
	
	static int minRemain;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		
		map = new int[N][M];
		for(int i = 0; i < N; i++) {
			input = br.readLine().split(" ");
			for(int j = 0; j < M; j++) {
				map[i][j] = Integer.parseInt(input[j]);
				if(1 <= map[i][j] && map[i][j] <= 5)
					cctvs.add(new int[] {i, j});
				else if(map[i][j] == 0)
					empty++;
			}
		}
		
		minRemain = empty;
		
		solve();
	}
	
	static void solve() {
		dfs(0, map, empty);
		System.out.println(minRemain);
	}
	
	static void dfs(int idx, int[][] map, int remain) {
		if(idx == cctvs.size()) {
			if(minRemain > remain)
				minRemain = remain;
			
			return;
		}
		
		int[] ccPos = cctvs.get(idx);
		int x = ccPos[0];
		int y = ccPos[1];
		
		int ccNum = map[x][y];
		int[][] cc = CCTV[ccNum];
		for(int[] dir : cc) {
			int[][] temp = copy(map);
			int seeCount = see(temp, x, y, dir);
			dfs(idx + 1, temp, remain - seeCount);
		}
	}
	
	static int see(int[][] map, int x, int y, int[] dir) {
		int count = 0;
		for(int d : dir) {
			int nextX = x;
			int nextY = y;
			
			while(true) {
				nextX += dx[d];
				nextY += dy[d];
				
				if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < M))
					break;
				
				if(map[nextX][nextY] == 6)
					break;
				
				if(map[nextX][nextY] == 7)
					continue;
				
				if(1 <= map[nextX][nextY] && map[nextX][nextY] <= 5)
					continue;
				
				count++;
				map[nextX][nextY] = 7;
			}
		}
		
		return count;
	}
	
	static int[][] copy(int[][] arr){
		int[][] re = new int[arr.length][arr[0].length];
		for(int i = 0; i < arr.length; i++) {
			re[i] = arr[i].clone();
		}
		return re;
	}
}
