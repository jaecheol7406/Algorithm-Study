package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
/*
 * 17837_새로운 게임2
 * 
 * main -> solve -> move
 * 
 * ※입력
 * map에 색깔정보 저장하고, k에는 말의 정보를 저장한다. k의 인덱스는 1 ~ K로 말의 번호를 나타내고, 각 말의 0, 1 인덱스는 좌표, 2는 방향을 나타냄.
 * horse는 N * N 크기의 리스트 배열로 말들의 번호 (1 ~ K)가 리스트로 저장됨.
 * 
 * solve에서 move를 반복호출시키는데 move 안에선 종료조건 만족시 t 출력 후 종료한다. t가 1000일 때도 종료 안되면 -1 출력 후 종료한다.
 * move에서는 1 ~ K 순으로 말을 이동시키는데, k를 참조해서 다음 좌표 구하고, 다음 좌표가 벗어나거나 파란색이면 방향 바꾸고 다시 다음 좌표 구한다.
 * 구한 다음좌표가 또 벗어나거나 파란색이면 그대로 둔다.
 * 하얀색 또는 빨간색이면 해당 말이 있는 인덱스 ~ 마지막까지 뽑아내 moveList에 저장하고 다음 좌표의 리스트 another에 저장한다.
 * 이후, 하얀색이면 그대로 another에 합치고 빨간색이면 거꾸로 합친다. 이 때 k에 좌표 갱신한다.
 * 합쳤을 때 another 크기가 4 이상이면 t 출력 후 종료한다.
 */
public class Main2 {
	static int[] dx = {0, 0, -1, 1};
	static int[] dy = {1, -1, 0, 0};
	
	static int N, K;
	static int[][] map;
	static int[][] k;
	
	static List<Integer>[][] horse;
	
	static int t;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		K = Integer.parseInt(input[1]);
		
		map = new int[N][N];
		horse = new ArrayList[N][N];
		for(int i = 0; i < N; i++) {
			input = br.readLine().split(" ");
			for(int j = 0; j < N; j++) {
				map[i][j] = Integer.parseInt(input[j]);
				horse[i][j] = new ArrayList<>();
			}
		}
		
		
		k = new int[K + 1][3];
		for(int i = 1; i <= K; i++) {
			input = br.readLine().split(" ");
			k[i][0] = Integer.parseInt(input[0]) - 1;
			k[i][1] = Integer.parseInt(input[1]) - 1;
			k[i][2] = Integer.parseInt(input[2]) - 1;
			
			horse[k[i][0]][k[i][1]].add(i);
		}
		
		solve();
	}
	
	static void solve() {
		while(true) {
			t++;
			
			move();
			
			if(t == 1000)
				break;
		}
		System.out.println(-1);
	}
	
	static void move() {
		for(int i = 1; i <= K; i++) {
			int x = k[i][0];
			int y = k[i][1];
			int dir = k[i][2];
			
			int nextX = x + dx[dir];
			int nextY = y + dy[dir];
			
			if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < N) || map[nextX][nextY] == 2) {
				if(dir == 0 || dir == 1)
					dir = 1 - dir;
				else
					dir = 5 - dir;
				
				nextX = x + dx[dir];
				nextY = y + dy[dir];
				
				k[i][2] = dir;
			}
			
			if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < N) || map[nextX][nextY] == 2)
				continue;

			List<Integer> another = horse[nextX][nextY];
			List<Integer> list = horse[x][y];
			int idx = list.indexOf(i);
			List<Integer> movedList = list.subList(idx, list.size());

			if(map[nextX][nextY] == 0) {
				for(int j : movedList) {
					k[j][0] += dx[dir];
					k[j][1] += dy[dir];
				}
				
				another.addAll(movedList);
				
			} else if(map[nextX][nextY] == 1) {
				List<Integer> reverse = new ArrayList<>();
				
				for(int j = movedList.size() - 1; j >= 0; j--) {
					int h = movedList.get(j);
					k[h][0] += dx[dir];
					k[h][1] += dy[dir];
					reverse.add(h);
				}
				
				another.addAll(reverse);
			}
			
			list.subList(idx, list.size()).clear();

			if(another.size() >= 4) {
				System.out.println(t);
				System.exit(0);
			}
		}
	}
}