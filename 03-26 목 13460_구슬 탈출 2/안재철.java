import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
/*
 * 13460_구슬 탈출 2  (틀렸습니다)
 * solve() -> copyOf()
 * 
 * solve() 에서 네 방향 모두 기울이는 것에 대해 bfs 진행. 큐에 구슬좌표, 맵 상태, 기울인 횟수(count)를 함께 저장함. 
 * count가 10 넘어가거나 벽에 막히면 큐에 넣지 않고, 가장 먼저 빨간색 구슬에 구멍에 들어가면 count 출력 후 종료 
 */
public class Main {
	static int[] dx = {0, 0, 1, -1};
	static int[] dy = {1, -1, 0, 0};
	
	static int N, M;
	static char[][] map;
	static int[] red, blue, hole;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String input[] = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		map = new char[N][M];
		for(int i = 0; i < N; i++) {
			String input2 = br.readLine();
			for(int j = 0; j < M; j++) {
				char c = input2.charAt(j);
				map[i][j] = c;
				if(c == 'R')
					red = new int[] {i, j};
				else if(c == 'B')
					blue = new int[] {i, j};
				else if(c == 'O')
					hole = new int[] {i, j};
			}
		}
		
		solve();
	}
	
	static void solve() {
		Queue<Node> q = new LinkedList<>();
		q.add(new Node(copyOf(map), red.clone(), blue.clone(), 1, -1));
		
		while(!q.isEmpty()) {
			Node node = q.poll();
			if(node.count == 11)
				continue;
			
			for(int i = 0; i < 4; i++) {
				char[][] map = copyOf(node.map);
				int[] red = node.red.clone();
				int[] blue = node.blue.clone();
				
				if(node.count != 1) {
					if(node.before == 0) {
						if(i == 0 || i == 1)
							continue;
					} else {
						if(i == 2 || i == 3)
							continue;
					}

				}
								
				boolean meet = false;
				while(true) {
					red[0] += dx[i];
					red[1] += dy[i];
					
					if(map[red[0]][red[1]] == 'B') {
						meet = true;
						continue;
					}
					
					if(map[red[0]][red[1]] == '#') {
						red[0] -= dx[i];
						red[1] -= dy[i];
						if(meet) {
							map[red[0]][red[1]] = 'B';
							blue[0] = red[0];
							blue[1] = red[1];
							
							red[0] -= dx[i];
							red[1] -= dy[i];
							map[red[0]][red[1]] = 'R';
						} else {
							map[red[0]][red[1]] = 'R';
							
							while(true) {
								blue[0] += dx[i];
								blue[1] += dy[i];
								
								if(map[blue[0]][blue[1]] == '#' || map[blue[0]][blue[1]] == 'R') {
									blue[0] -= dx[i];
									blue[1] -= dy[i];
									map[blue[0]][blue[1]] = 'B';
									break;
								} else if(map[blue[0]][blue[1]] == 'O'){
									System.out.println(-1);
									System.exit(0);
								}
							}
						}
						break;
					} else if(map[red[0]][red[1]] == 'O') {
						if(meet) {
							System.out.println(-1);
							System.exit(0);
						}
						
						while(true) {
							blue[0] += dx[i];
							blue[1] += dy[i];
							
							if(map[blue[0]][blue[1]] == '#' || map[blue[0]][blue[1]] == 'R') {
								blue[0] -= dx[i];
								blue[1] -= dy[i];
								map[blue[0]][blue[1]] = 'B';
								System.out.println(node.count);
								System.exit(0);
							} else if(map[blue[0]][blue[1]] == 'O'){
								System.out.println(-1);
								System.exit(0);
							}
						}
					}
				}
				
				if(!(node.red[0] == red[0] && node.red[1] == red[1]))
					map[node.red[0]][node.red[1]] = '.';
				if(!(node.blue[0] == blue[0] && node.blue[1] == blue[1]))
					map[node.blue[0]][node.blue[1]] = '.';
				
				int dir1 = 0, dir2 = 1;
				if(i <= 1) {
					dir1 = 2; 
					dir2 = 3;
				}
					
				if(map[red[0] + dx[dir1]][red[1] + dy[dir1]] == '.' || map[red[0] + dx[dir2]][red[1] + dy[dir2]] == '.')
					q.add(new Node(copyOf(map), red, blue, node.count + 1, 2 - dir1));
			}	
		}
		
		System.out.println(-1);
	}
	
	static char[][] copyOf(char[][] arr){
		char[][] temp = new char[arr.length][arr[0].length];
		for(int i = 0; i < arr.length; i++) {
			temp[i] = arr[i].clone();
		}
		return temp;
	}
} 

class Node{
	char[][] map;
	int[] red, blue;
	int count;
	int before;
	
	public Node(char[][] map, int[] red, int[] blue, int count, int before) {
		this.map = map;
		this.red = red;
		this.blue = blue;
		this.count = count;
		this.before = before;
	}
}