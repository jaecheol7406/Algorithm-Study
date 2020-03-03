import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
/*
 * 2234_성곽
 * 1. input()으로 n, m, map, visit 입력받음
 * 2. solve()에서 map을 bfs 써서 방의 좌표들 rooms ArrayList에 저장, roomSize에 방의 크기 저장
 * 3. bfs 끈난 후 서로 다른 방에 대해 isAdjoin() 함수로 인접하는지 확인 (각각의 좌표들에 대해 서로 맨하탄 디스턴스가 1인 좌표 있으면 인접함) 후 인접하면 두 방의 크기 maxSize에 갱신
 * 4. 출력 
 */
public class Main3 {
	public static final int[][] moveDir = new int[][] {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	
	static int n, m;
	static int[][] map;
	static boolean[][] visit;
	
	static ArrayList<Integer> roomSize = new ArrayList<>();
	static ArrayList<ArrayList<int[]>> rooms = new ArrayList<>();
	static int maxSize = -1;
	
	public static void main(String[] args) {
		input();
		solve();
		
		System.out.println(rooms.size());
		System.out.println(Collections.max(roomSize));
		System.out.println(maxSize);
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		m = sc.nextInt();
		
		map = new int[m][n];
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				map[i][j] = sc.nextInt();
		
		visit = new boolean[m][n];
			
		sc.close();
	}
	
	static void solve() {
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				if(!visit[i][j])
					bfs(i, j);
			}
		}
		
		for(int i = 0; i < rooms.size() - 1; i++) {
			for(int j = i + 1; j < rooms.size(); j++) {
				if(isAdjoin(rooms.get(i), rooms.get(j)))
					maxSize = Integer.max(maxSize, roomSize.get(i) + roomSize.get(j));
			}
		}
	}
	
	static void bfs(int i, int j) {
		ArrayList<int[]> room = new ArrayList<>();
		
		Queue<int[]> q = new LinkedList<int[]>();
		q.add(new int[]{i, j});
		
		while(!q.isEmpty()) {
			int[] pos = q.poll();
			int x = pos[0];
			int y = pos[1];
			
			room.add(pos);
			visit[x][y] = true;
			
			int val = map[x][y];
			String bi = Integer.toBinaryString(val);
			int len = 4 - bi.length();
			for(int k = 0; k < len; k++)
				bi = "0" + bi;
			
			for(int ii = bi.length() - 1; ii >= 0; ii--) {
				char c = bi.charAt(ii);
				if(c == '1')
					continue;
				
				int nextX = x + moveDir[ii][0];
				int nextY = y + moveDir[ii][1];
				
				if(visit[nextX][nextY])
					continue;
				
				q.add(new int[] {nextX, nextY});
				visit[nextX][nextY] = true;
			}
		}
		roomSize.add(room.size());
		rooms.add(room);
	}
	
	static boolean isAdjoin(ArrayList<int[]> r1, ArrayList<int[]> r2) {
		for(int[] r1pos : r1) {
			for(int[] r2pos : r2) {
				if(Math.abs(r1pos[0] - r2pos[0]) + Math.abs(r1pos[1] - r2pos[1]) == 1)
					return true;
			}
		}
		return false;
	}
}