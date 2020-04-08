package _2020_04;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Deque;
import java.util.LinkedList;

/*
 * 3190_뱀
 */
public class Main {
	// 북동남서
	static int[] dx = {-1,0,1,0};
	static int[] dy = {0,1,0,-1};
	
	static int N, K, L;
	static int[][] map;
	static int[][] dirInfo;
	static int dirInfoIdx;
	
	static int dir = 1;
	static Deque<int[]> snake = new LinkedList<int[]>();
	static {
		snake.add(new int[2]);
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = toInt(br.readLine());
		map = new int[N][N];
		map[0][0] = 2;

		K = toInt(br.readLine());
		for(int i = 0; i < K; i++) {
			String[] input = br.readLine().split(" ");
			map[toInt(input[0]) - 1][toInt(input[1]) - 1] = 1; // 사과
		}
		
		L = toInt(br.readLine());
		dirInfo = new int[L][2];
		for(int i = 0; i < L; i++) {
			String[] input = br.readLine().split(" ");
			dirInfo[i][0] = toInt(input[0]);
			if(input[1].equals("L"))
				dirInfo[i][1] = -1;
			else
				dirInfo[i][1] = 1;
		}
		
		solve();
	}
	
	static int toInt(String s) {
		return Integer.parseInt(s);
	}
	
	static void print() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				System.out.print(map[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
	}
	
	static void solve() {
		print();
		int t = 0;
		while(true) {
			t++;
			
			int[] front = snake.getFirst();
			
			int nextX = front[0] + dx[dir];
			int nextY = front[1] + dy[dir];
			
			if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < N))
				break;
			
			if(map[nextX][nextY] == 2)
				break;
			
			snake.addFirst(new int[] {nextX, nextY});
			
			if(map[nextX][nextY] != 1) {
				int[] back = snake.removeLast();
				map[back[0]][back[1]] = 0;
			}
			
			map[nextX][nextY] = 2;
			
			if(dirInfoIdx < dirInfo.length) {
				int dirInfoT = dirInfo[dirInfoIdx][0];
				if(dirInfoT == t) {
					dir += dirInfo[dirInfoIdx++][1];
					if(dir < 0)
						dir = 3;
					else
						dir %= 4;
				}
			}
			
			print();
		}
		
		System.out.println(t);
	}
}
