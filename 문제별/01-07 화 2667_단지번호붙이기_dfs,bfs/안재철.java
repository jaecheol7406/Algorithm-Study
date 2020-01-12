import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/* 2667번 단지번호 붙이기
문제
<그림 1>과 같이 정사각형 모양의 지도가 있다. 1은 집이 있는 곳을, 0은 집이 없는 곳을 나타낸다. 철수는 이 지도를 가지고 연결된 집들의 모임인 단지를 정의하고, 단지에 번호를 붙이려 한다. 여기서 연결되었다는 것은 어떤 집이 좌우, 혹은 아래위로 다른 집이 있는 경우를 말한다. 대각선상에 집이 있는 경우는 연결된 것이 아니다. <그림 2>는 <그림 1>을 단지별로 번호를 붙인 것이다. 지도를 입력하여 단지수를 출력하고, 각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하는 프로그램을 작성하시오.



입력
첫 번째 줄에는 지도의 크기 N(정사각형이므로 가로와 세로의 크기는 같으며 5≤N≤25)이 입력되고, 그 다음 N줄에는 각각 N개의 자료(0혹은 1)가 입력된다.

출력
첫 번째 줄에는 총 단지수를 출력하시오. 그리고 각 단지내 집의 수를 오름차순으로 정렬하여 한 줄에 하나씩 출력하시오.
*/

public class Main {
	
	public static final int[][] moveDir = new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	static int N;
	static int[][] map;
	static boolean[][] visit;
	
	static List<Integer> estates = new ArrayList<>();
	
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		map = new int[N][N];
		visit = new boolean[N][N];
		
		for(int i = 0; i < N; i++) {
			String input = br.readLine();
			for(int j = 0; j < N; j++) {
				map[i][j] = Integer.parseInt(String.valueOf(input.charAt(j)));
			}
		}
		
		printResult();
	}
	
	static void printResult() {
		bfs();
		Collections.sort(estates);
		System.out.println(estates.size());
		for(int houseNum : estates)
			System.out.println(houseNum);
	}
	
	static void bfs() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				// 방문 했거나 집이 없으면 continue
				if(visit[i][j] || map[i][j] == 0)
					continue;
				
				// 방문 안했고 집이 있으면 그 집을 시작으로 한 단지 구성
				oneEstate(i, j);
			}
		}
	}
	
	// 시작 집(i, j)에 대해 bfs로 단지 구성
	static void oneEstate(int i, int j) {
		Queue<int[]> queue = new LinkedList<>();
		int houseNum = 0;
		
		queue.offer(new int[] {i, j});
		visit[i][j] = true;
		houseNum++;
		
		while(!queue.isEmpty()) {
			int[] coord = queue.poll();
			int x = coord[0];
			int y = coord[1];
			
			for(int k = 0; k < 4; k++) {
				int moveX = x + moveDir[k][0];
				int moveY = y + moveDir[k][1];
				
				if(!(0 <= moveX && moveX < N && 0 <= moveY && moveY < N))
					continue;
				
				if(!visit[moveX][moveY] && map[moveX][moveY] == 1) {
					queue.offer(new int[] {moveX, moveY});
					visit[moveX][moveY] = true;
					houseNum++;
				}
			}
		}
		
		estates.add(houseNum);
	}
}
