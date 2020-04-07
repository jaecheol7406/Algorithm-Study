package _2020_04;

import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 14503_로봇 청소기
 * 
 * main() -> solve()
 * 
 * dir : 0 ~ 3 북 동 남 서 순으로 놓고 dir-- 하면서 탐색하였다.
 * ex) 현재 남쪽(2) 이면 2 -> 1 -> 0 -> 3
 * 0이면 가서 2로 바꾼 후 (청소) 똑같이 반복..
 * 4방향 모두 0 아닌데 현재 방향의 뒤가 벽이면 끝내고, 벽 아니면 (0으로 빈칸이거나 2로 청소) 방향 그대로 후진 후 4방향 탐색 반복..
 * 청소할 때마다 clean++해서 최종 출력.
 */
public class Main {
	static int[] dx = {-1, 0, 1, 0};
	static int[] dy = {0, 1, 0, -1};
	
	static int N, M;
	static int[][] map;
	static int[] pos;
	static int dir;
	
	static int clean;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		
		input = br.readLine().split(" ");
		pos = new int[2];
		pos[0] = Integer.parseInt(input[0]);
		pos[1] = Integer.parseInt(input[1]);
		dir = Integer.parseInt(input[2]);
		
		map = new int[N][M];
		for(int i = 0; i < N; i++) {
			input = br.readLine().split(" ");
			for(int j = 0; j < M; j++) {
				map[i][j] = Integer.parseInt(input[j]);
			}
		}
		
		solve();
		System.out.println(clean);
	}
	
	static void solve() {
		while(true) {
			if(map[pos[0]][pos[1]] == 0) {
				map[pos[0]][pos[1]] = 2;
				clean++;
			}

			int i = 0;
			for(; i < 4; i++) {
				dir--;
				if(dir == -1)
					dir = 3;
				
				int nextX = pos[0] + dx[dir];
				int nextY = pos[1] + dy[dir];
				
				if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < M))
					continue;
				
				if(map[nextX][nextY] != 0)
					continue;
				
				pos[0] = nextX;
				pos[1] = nextY;
				break;
			}
			
			if(i < 4)
				continue;
			
			int backX = pos[0] + dx[(dir + 2) % 4];
			int backY = pos[1] + dy[(dir + 2) % 4];
			
			if(map[backX][backY] == 1)
				break;
			
			pos[0] = backX;
			pos[1] = backY;
		}
	}
}
