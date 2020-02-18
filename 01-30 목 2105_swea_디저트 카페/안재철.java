import java.util.Scanner;
/* 2105_swea_디저트 카페
 */
public class Main {
	public static final int[][] moveDir = new int[][]{{1, -1}, {1, 1}, {-1, 1}, {-1, -1}}; // 남서, 동남, 동북, 북서 (반시계방향으로 대각선이동)
	static int T;
	static int N;
	static int[][] map;
	static int targetX, targetY;
	static int maxDessertCount = -1;
	
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		T = sc.nextInt();

		for(int t = 1; t <= T; t++) {
			
			N = sc.nextInt();
			map = new int[N][N];
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++)
					map[i][j] = sc.nextInt();
			}
			
			solve();
			print(t);
			
			maxDessertCount = -1;
		}
		
		sc.close();
	}
	
	static void solve() {
		for(int i = 0; i < N - 2; i++) {
			for(int j = 1; j < N - 1; j++) {				
				targetX = i;
				targetY = j;
				dfs(0, i, j, new boolean[101], 0);
			}
		}
	}
	
	static void dfs(int dir, int x, int y, boolean[] dessert, int dessertCount) {
		if(dir != 0 && x == targetX && y == targetY) {
			maxDessertCount = Integer.max(maxDessertCount, dessertCount);
			return;
		}
		
		if(dessert[map[x][y]])
			return;
		
		dessert[map[x][y]] = true;
		dessertCount++;
		
		int nextX = 0, nextY = 0;
		// 남서방향일 때
		if(dir == 0) {
			// 그대로 남서방향으로 가는경우
			nextX = x + moveDir[0][0];
			nextY = y + moveDir[0][1];
			if((0 <= nextX && nextX < N && 0 <= nextY && nextY < N))
				dfs(0, nextX, nextY, dessert.clone(), dessertCount);
			
			// 시작점이 아닐 경우 동남쪽으로도 가봄
			if(dessertCount != 1){
				nextX = x + moveDir[1][0];
				nextY = y + moveDir[1][1];
				if((0 <= nextX && nextX < N && 0 <= nextY && nextY < N))
					dfs(1, nextX, nextY, dessert.clone(), dessertCount);
			}
		} else if(dir == 1) { // 동남방향일 때
			// 그대로 동남쪽으로 가는경우,
			nextX = x + moveDir[1][0];
			nextY = y + moveDir[1][1];
			if((0 <= nextX && nextX < N && 0 <= nextY && nextY < N))
				dfs(1, nextX, nextY, dessert.clone(), dessertCount);
			
			// 북동쪽으로 가는 경우
			nextX = x + moveDir[2][0];
			nextY = y + moveDir[2][1];
			if((0 <= nextX && nextX < N && 0 <= nextY && nextY < N))
				dfs(2, nextX, nextY, dessert.clone(), dessertCount);
		} else if(dir == 2) { // 북동방향일 때
			// 사각형을 만들기 위해 북서쪽으로 꺽어야 하는 좌표이면 북서방향으로 꺽음
			if(targetX - x == targetY - y)
				dfs(3, x + moveDir[3][0], y + moveDir[3][1], dessert.clone(), dessertCount);
			// 아니면 북동쪽으로 쭉 감
			else {
				nextX = x + moveDir[2][0];
				nextY = y + moveDir[2][1];
				if((0 <= nextX && nextX < N && 0 <= nextY && nextY < N))
					dfs(2, nextX, nextY, dessert.clone(), dessertCount);
			}
		} else { // 북서방향일 때는 원점으로 돌아오고있는 경우이므로 조건검사할 필요 없이 그대로 감. (여기까지 왔다는 것은 앞에서 사각형이 문제없이 만들어졌다는 것)
			dfs(3, x + moveDir[3][0], y + moveDir[3][1], dessert.clone(), dessertCount);
		}
	}
	
	static void print(int t) {
		System.out.println("#" + t + " " + maxDessertCount);
	}
}