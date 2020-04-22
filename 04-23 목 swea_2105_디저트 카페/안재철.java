package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
/*
 * 2105. [모의 SW 역량테스트] 디저트 카페
 * 
 * main -> solve -> bfs
 * 
 * 기준 좌표에 대해 오른쪽아래, 왼쪽아래, 왼쪽위, 오른쪽위 대각선 순으로 사각형을 그린다.
 * 기준좌표의 범위는 최소 크기의 사각형을 그릴 수 있도록 x : 0 ~ 끝에서 2번째, y : 1 ~ 끝에서 첫번째로 한다.
 * 기준 좌표를 bfs로 넘겨 큐에 첫 Node로 넣어 시작한다.
 * 
 * Node의 x, y는 현재 좌표, stage는 단계 (위 사각형 그리는 순서대로 1,2,3 이다. 2까지 왔으면 왼쪽위, 오른쪽위는 고정되어있으므로 stage 3으로 통일한다.)이고
 * dst는 현재까지의 디저트 숫자들이다. (ArrayList)
 * 
 * 처음 기준좌표는 무조건 stage 1으로 넣고, x++, y++ 해서 못그리는 좌표 제외 모두 stage 2로 큐에 넣는다.
 * stage2에서는 x++, y-- 해서 왼쪽아래로 가면서 불가능 제외 stage3으로 큐에 넣는다.
 * stage3에서는 x--, y--해서 꺾일때 까지 그리고 꺾이는데서는 처음 기준좌표와 같아질 떄 까지 그린다.
 * 모두 그릴 수 있으면 max에 dst의 크기를 갱신시킨다.
 * 
 * 위의 그리는 과정에서, dst에 넣어가며 그리는데 dst에 같은 숫자가 있으면 못그리니까 큐에 안넣는다.
 */
public class Solution {
	static int N, T;
	static int[][] map;
	static int max;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		for(int t = 1; t <= T; t++) {
			N = Integer.parseInt(br.readLine());
			map = new int[N][N];
			for(int i = 0; i < N; i++) {
				String[] input = br.readLine().split(" ");
				for(int j = 0; j < N; j++)
					map[i][j] = Integer.parseInt(input[j]);
			}
			
			max = -1;
			solve();
			System.out.println("#" + t + " " + max);
		}
	}
	
	static void solve() {
		for(int i = 0; i < N - 2; i++) {
			for(int j = 1; j < N - 1; j++) {
				bfs(i, j);
			}
		}
	}
	
	static void bfs(int startx, int starty) {
		Queue<Node> q = new LinkedList<>();
		
		q.add(new Node(startx, starty, 1, new ArrayList<>(Arrays.asList(map[startx][starty]))));
		
		while(!q.isEmpty()) {
			Node n = q.poll();
			int x = n.x;
			int y = n.y;
			int stage = n.stage;
			List<Integer> dst = n.dst;
			
			if(stage == 1) {
				
				while(true) {
					x += 1;
					y += 1;
					
					if(x == N - 1 || y == N || dst.contains(map[x][y]))
						break;
					
					dst.add(map[x][y]);
					
					q.add(new Node(x, y, 2, new ArrayList<>(dst)));
				}
				
			} else if(stage == 2) {
				
				while(true) {
					x += 1;
					y -= 1;
					
					if(x == N || y == 0 || dst.contains(map[x][y]))
						break;
					
					dst.add(map[x][y]);
					
					q.add(new Node(x, y, 3, new ArrayList<>(dst)));
				}
				
			} else if(stage == 3) {
				boolean flag = false;
				
				while(true) {
					x -= 1;
					y -= 1;
					
					if(y == -1 || dst.contains(map[x][y])) {
						flag = true;
						break;
					}
					
					dst.add(map[x][y]);
					
					if(x - startx == starty - y)
						break;
				}
				
				if(flag)
					continue;
				
				while(true) {
					x -= 1;
					y += 1;
					
					if(x == startx && y == starty) {
						max = Integer.max(max, dst.size());
						break;
					}

					if(dst.contains(map[x][y]))
						break;
					
					dst.add(map[x][y]);
				}
			}
		}
	}
}

class Node {
	int x;
	int y;
	int stage;
	List<Integer> dst;
	
	public Node(int x, int y, int stage, List<Integer> dst) {
		super();
		this.x = x;
		this.y = y;
		this.stage = stage;
		this.dst = dst;
	}
}