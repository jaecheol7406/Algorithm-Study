import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
/*
 * 11559_Puyo Puyo
 * 1. char형 2차원배열 field에 입력
 * 2. bfs로 field 탐색해서 부서질 뿌요의 모든 좌표들 deletePos에 저장
 * 		deletePos는 key : 열좌표값, value : 행좌표값들을 저장하는 HashMap임.  즉 부서질 뿌요의 좌표값들을 열 좌표값 별로 저장.
 * 3. 부서질 뿌요가 없으면 break 후 combo 횟수 출력 
 * 4. 있으면 deletePos 순회하여 열별로 붙어있는 행 개수만큼 밑으로 내린다. (down() 함수)
 * 5. combo++
 * 6. 2번으로 돌아가서 반복
 */
public class Main {
	public static final int[] dx = {0, 0, 1, -1};
	public static final int[] dy = {1, -1, 0, 0};
	
	static char[][] field = new char[12][6];
	static boolean[][] visit = new boolean[12][6];
	
	static HashMap<Integer, ArrayList<Integer>> deletePos = new HashMap<>();
	static int combo;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		for(int i = 0; i < 12; i++) {
			String s = br.readLine();
			for(int j = 0; j < 6; j++)
				field[i][j] = s.charAt(j);
		}
		solve();
	}
	
	static void solve() {
		int startX = 0, startY = 0;
		int nextStartX = 0, nextStartY = 0;
		while(true) {
			boolean meet = false;
			for(int i = startX; i < 12; i++) {
				for(int j = startY; j < 6; j++) {
					if(!visit[i][j] && field[i][j] != '.') {
						if(!meet) {
							meet = true;
							nextStartX = i;
							nextStartY = j;
						}
						
						bfs(i, j);
					}
				}
			}
			
			if(deletePos.isEmpty())
				break;
			
			down();
			combo++;
			
			deletePos = new HashMap<>();
			visit = new boolean[12][6];
			
			startX = nextStartX;
			startY = nextStartY;
		}
		System.out.println(combo);
	}
	
	static void bfs(int x, int y) {
		Queue<int[]> q = new LinkedList<>();
		q.add(new int[]{x, y});
		char color = field[x][y];
		ArrayList<int[]> poss = new ArrayList<>();
		
		while(!q.isEmpty()) {
			int[] pos = q.poll();
			visit[pos[0]][pos[1]] = true;
			poss.add(new int[] {pos[0], pos[1]});
			
			for(int i = 0; i < 4; i++) {
				int nextX = pos[0] + dx[i];
				int nextY = pos[1] + dy[i];
				
				if(!(0 <= nextX && nextX < 12 && 0 <= nextY && nextY < 6))
					continue;
				
				if(visit[nextX][nextY] || field[nextX][nextY] != color)
					continue;
				
				visit[nextX][nextY] = true;
				q.add(new int[] {nextX, nextY});
			}
		}
		
		if(poss.size() >= 4) {
			for(int[] pos : poss) {
				ArrayList<Integer> xs = deletePos.get(pos[1]);
				if(xs == null)
					xs = new ArrayList<>();
				xs.add(pos[0]);
				deletePos.put(pos[1], xs);
			}
		}
	}
	
	static void down() {
		// 한 줄(열)씩 수행
		for(int y : deletePos.keySet()) {
			ArrayList<Integer> xs = deletePos.get(y);
			Collections.sort(xs);
			
			int firstIdx = xs.get(0);
			int prev = firstIdx;
			for(int i = 1; i < xs.size(); i++) {
				int now = xs.get(i);
				if(now - prev == 1) {
					prev++;
					continue;
				}
				
				int popLen = prev - firstIdx + 1;
				// down
				for(int movedIdx = firstIdx - 1; movedIdx >= 0; movedIdx--)
					field[movedIdx + popLen][y] = field[movedIdx][y];
				for(int j = 0; j < popLen; j++)
					field[j][y] = '.';
				
				firstIdx = now;
				prev = now;
			}
			int popLen = prev - firstIdx + 1;
			// down
			for(int movedIdx = firstIdx - 1; movedIdx >= 0; movedIdx--)
				field[movedIdx + popLen][y] = field[movedIdx][y];
			for(int j = 0; j < popLen; j++)
				field[j][y] = '.';
		}
	}
}