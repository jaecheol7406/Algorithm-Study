package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
/*
 * 15685_드래곤 커브
 * 
 * main -> (draw -> opposite), square
 * 
 * 101 x 101 배열 만들어 놓고 main에서 드래곤커브 입력받으며 draw로 map에 모두 그림.
 * draw : 그린 방향의 반대방향을 opposite 함수로 구해서 리스트에 저장해놓음. 이후 다음 세대에서 리스트를 거꾸로 순회해 끝점 기준으로 90도 회전한 방향으로 그려나감.
 * 
 * 다 그린 후, square 함수로 사각형 개수 카운트 후 출력
 */
public class Main {
	static int[] dx = {0,-1,0,1}; //동북서남
	static int[] dy = {1,0,-1,0};
	
	static int N;
	static int[][] map = new int[101][101];
	static int count;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		for(int i = 0; i < N; i++) {
			String[] input = br.readLine().split(" ");
			int y = Integer.parseInt(input[0]);
			int x = Integer.parseInt(input[1]);
			int dir = Integer.parseInt(input[2]);
			int gen = Integer.parseInt(input[3]);
			
			draw(x, y, dir, gen);
		}
		
		for(int i = 0; i < 100; i++) {
			for(int j = 0; j < 100; j++) {
				if(map[i][j] == 1 && square(i, j))
					count++;
			}
		}
		
		System.out.println(count);
	}
	
	static void draw(int x, int y, int dir, int gen) {
		map[x][y] = 1;
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		map[nx][ny] = 1;
		
		int[] endPos = new int[] {nx, ny};

		List<Integer> dirs = new ArrayList<>();
		dirs.add(opposite(dir));
		
		for(int g = 0; g < gen; g++) {
			List<Integer> newDirs = new ArrayList<>();
			for(int i = dirs.size() - 1; i >= 0; i--) {
				int d = dirs.get(i);
				if(--d == -1)
					d = 3;
				
				endPos[0] += dx[d];
				endPos[1] += dy[d];
				map[endPos[0]][endPos[1]] = 1;
				
				newDirs.add(opposite(d));
			}
			dirs.addAll(newDirs);
		}
	}
	
	static int opposite(int dir) {
		if(dir == 0 || dir == 2)
			dir = 2 - dir;
		else
			dir = 4 - dir;
		
		return dir;
	}
	
	static boolean square(int x, int y) {
		int nx = x + dx[0];
		int ny = y + dy[0];
		if(map[nx][ny] == 0)
			return false;
		
		nx += dx[3];
		ny += dy[3];
		if(map[nx][ny] == 0)
			return false;
		
		nx += dx[2];
		ny += dy[2];
		if(map[nx][ny] == 0)
			return false;
		
		return true;
	}
}