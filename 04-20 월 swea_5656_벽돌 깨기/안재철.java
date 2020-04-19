package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
/*
 * 5656. [모의 SW 역량테스트] 벽돌 깨기
 * 
 * main -> solve -> dfs -> (copyOf, shot)    shot -> down
 * 
 * 0 ~ W (y 좌표)를 중복 순열로 N번 쏴보는 모든 경우의 수에 대해 수행했다. (dfs로 구현)
 * 
 * dfs에는 쏘는 횟수 shotNum, 현재 상태 map, 남아있는 벽돌 개수 remain을 넣는다.
 * 
 * shotNum == N 즉 N번 다 쏘면 최소값 갱신시켜서 return 0해주고, remain == 0이면 최소값 0으로 갱신하고 return -1한다.
 * -> 이렇게 하는 이유는, N번 다 쏘기 전에 남아있는 벽돌이 0개면 더 쏠필요 없이 정답은 0이니까 dfs의 return값을 -1 플래그로 전달해 더이상 하지않고 끝내버린다.
 * N번 다쏘거나 dfs가 종료되어 더 해야할필요가 있으면 return 0 해줘서 정상적으로 진행한다.
 * 
 * 
 * dfs에서는 0 ~ W 까지 인덱스에 대해 쏴봐서 shot 메소드로 map 상태 변경시켜주고 그 map으로 dfs에 전달한다. shot 메소드는 깨진 벽돌의 개수를 return 해주는데,
 * 0개면 해당 줄에 벽돌이 없었다는 뜻이므로 dfs 안해주고 다음 인덱스로 간다.
 * 
 * shot에서는 해당 인덱스에 대해 깨뜨리는데, 맨 위가 1이면 그것만 깨지므로 해당 벽돌 깨고 1 return해서 끝내는데, 
 * 그 이상 숫자면 큐에 넣어 bfs 해준다. (4방향에대해 가면서 1 초과인 벽돌이 여러개 나타날 수 있기 때문에) 그러면서 1인건 꺠뜨리면서 count++해주며 간다.
 * 다 깨뜨리면 down으로 내리고, count return해주고 끝낸다.
 */
public class Main {
	static int[] dx = {0,0,1,-1};
	static int[] dy = {1,-1,0,0};
	
	static int T;
	static int N,W,H;
	static int[][] map;
	
	static int brickNum;
	static int minRemain;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		T = Integer.parseInt(br.readLine());
		for(int t = 1; t <= T; t++) {
			String[] input = br.readLine().split(" ");
			N = Integer.parseInt(input[0]);
			W = Integer.parseInt(input[1]);
			H = Integer.parseInt(input[2]);
			
			map = new int[H][W];
			for(int i = 0; i < H; i++) {
				input = br.readLine().split(" ");
				for(int j = 0; j < W; j++) {
					map[i][j] = Integer.parseInt(input[j]);
					if(map[i][j] > 0)
						brickNum++;
				}
			}
			
			minRemain = brickNum;
			
			solve();
			System.out.println("#" + t + " " + minRemain);
			
			brickNum = 0;
		}
	}
	
	static void solve() {
		dfs(0, map, brickNum);
	}
	
	static int dfs(int shotNum, int[][] map, int remain) {
		if(remain == 0) {
			minRemain = 0;
			return -1;
		}
		
		if(shotNum == N) {
			if(minRemain > remain)
				minRemain = remain;
			
			return 0;
		}
		
		for(int i = 0; i < W; i++) {
			int[][] temp = copyOf(map);
			int crackCount = shot(temp, i);
			
			if(crackCount == 0)
				continue;
			
			if(dfs(shotNum + 1, temp, remain - crackCount) == -1)
				return -1;
		}
		
		return 0;
	}
	
	static int shot(int[][] map, int w) {
		for(int i = 0; i < H; i++) {
			if(map[i][w] == 0)
				continue;
			
			if(map[i][w] == 1) {
				map[i][w] = 0;
				return 1;
			}
			
			int count = 0;
			
			boolean[][] visit = new boolean[H][W];
			
			Queue<int[]> q = new LinkedList<>();
			q.add(new int[] {i, w});
			visit[i][w] = true;
			
			while(!q.isEmpty()) {
				int[] pos = q.poll();
				int x = pos[0];
				int y = pos[1];
				
				int v = map[x][y];
				map[x][y] = 0;
				count++;
				
				for(int len = 1; len <= v - 1; len++) {
					for(int d = 0; d < 4; d++) {
						int nextX = x + dx[d] * len;
						int nextY = y + dy[d] * len;
						
						if(!(0 <= nextX && nextX < H && 0 <= nextY && nextY < W))
							continue;
						
						if(map[nextX][nextY] == 0)
							continue;
						
						if(map[nextX][nextY] == 1) {
							map[nextX][nextY] = 0;
							count++;
							continue;
						}
						
						if(visit[nextX][nextY])
							continue;
						
						q.add(new int[] {nextX, nextY});
						visit[nextX][nextY] = true;
					}
				}
			}
			
			down(map);
			
			return count;
		}
		
		return 0;
	}
	
	static void down(int[][] map) {
		for(int j = 0; j < W; j++) {
			int idx = H - 1;
			for(int i = H - 1; i >= 0; i--) {
				if(map[i][j] != 0) {
					map[idx][j] = map[i][j];
					if(i != idx--)
						map[i][j] = 0;
				}
			}
		}
	}
	
	static int[][] copyOf(int[][] arr){
		int[][] newArr = new int[arr.length][arr[0].length];
		for(int i = 0; i < arr.length; i++) {
			newArr[i] = arr[i].clone();
		}
		return newArr;
	}
}