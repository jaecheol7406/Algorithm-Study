import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
/*
 * 11559_Puyo Puyo
 * 1. char형 2차원배열 field에 입력
 * 2. bfs로 field 탐색해서 부서질 뿌요의 모든 좌표들을 '.'로 채움
 * 3. 부서질 뿌요가 없으면 break 후 combo 횟수 출력 
 * 4. 있으면 '.' 제외한 문자들을 내리고 나머지는 '.'로 채움 (down() 함수)
 * 5. combo++
 * 6. 2번으로 돌아가서 반복
 */
public class Main {
	public static final int[] dx = {0, 0, 1, -1};
	public static final int[] dy = {1, -1, 0, 0};
	
	static char[][] field = new char[12][6];
	static boolean[][] visit = new boolean[12][6];
	
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
			boolean pop = false;
			for(int i = startX; i < 12; i++) {
				for(int j = startY; j < 6; j++) {
					if(!visit[i][j] && field[i][j] != '.') {
						if(bfs(i, j))
							pop = true;
					}
				}
			}
			
			if(!pop)
				break;
			
			down();
			combo++;
			
			visit = new boolean[12][6];
			
			startX = nextStartX;
			startY = nextStartY;
		}
		System.out.println(combo);
	}
	
	static boolean bfs(int x, int y) {
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
			for(int[] pos : poss)
				field[pos[0]][pos[1]] = '.';
			return true;
		}
		return false;
	}
	
	static void down() {
		// 한 줄(열)씩 수행
		for(int j = 0; j < 6; j++) {
			ArrayList<Character> temp = new ArrayList<>();
			for(int i = 0; i < 12; i++) {
				if(field[i][j] != '.')
					temp.add(field[i][j]);
			}
			if(temp.size() == 0)
				continue;
			
			int blank = 12 - temp.size();
			for(int i = 0; i < blank; i++)
				field[i][j] = '.';
			for(int i = blank; i < 12; i++)
				field[i][j] = temp.remove(0);
		}
	}
}