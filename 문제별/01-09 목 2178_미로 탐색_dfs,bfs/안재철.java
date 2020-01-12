import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

/* 2178_미로 
문제
N×M크기의 배열로 표현되는 미로가 있다.

1	0	1	1	1	1
1	0	1	0	1	0
1	0	1	0	1	1
1	1	1	0	1	1
미로에서 1은 이동할 수 있는 칸을 나타내고, 0은 이동할 수 없는 칸을 나타낸다. 이러한 미로가 주어졌을 때, (1, 1)에서 출발하여 (N, M)의 위치로 이동할 때 지나야 하는 최소의 칸 수를 구하는 프로그램을 작성하시오. 한 칸에서 다른 칸으로 이동할 때, 서로 인접한 칸으로만 이동할 수 있다.

위의 예에서는 15칸을 지나야 (N, M)의 위치로 이동할 수 있다. 칸을 셀 때에는 시작 위치와 도착 위치도 포함한다.

입력
첫째 줄에 두 정수 N, M(2 ≤ N, M ≤ 100)이 주어진다. 다음 N개의 줄에는 M개의 정수로 미로가 주어진다. 각각의 수들은 붙어서 입력으로 주어진다.

출력
첫째 줄에 지나야 하는 최소의 칸 수를 출력한다. 항상 도착위치로 이동할 수 있는 경우만 입력으로 주어진다.

예제 입력 1 
4 6
101111
101010
101011
111011
예제 출력 1 
15
예제 입력 2 
4 6
110110
110110
111111
111101
예제 출력 2 
9
예제 입력 3 
2 25
1011101110111011101110111
1110111011101110111011101
예제 출력 3 
38
예제 입력 4 
7 7
1011111
1110001
1000001
1000001
1000001
1000001
1111111
예제 출력 4 
13
*/

public class Main {
	public static final int[][] moveDir = new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // 동 서 남 북

	static int N, M;
	static int[][] miro;
	static boolean[][] visit;
	
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		miro = new int[N + 1][M + 1];
		visit = new boolean[N + 1][M + 1];
		for(int i = 1; i <= N; i++) {
			String s = br.readLine();
			for(int j = 1; j <= M; j++)
				miro[i][j] = Integer.parseInt(String.valueOf(s.charAt(j - 1)));
		}
		System.out.println(bfs());
	}
	
	static int bfs() {
		Queue<int[]> q = new LinkedList<>();
		
		q.add(new int[] {1, 1, 1}); // 좌표, 지나는 칸 수
		while(!q.isEmpty()) {
			int[] pos = q.poll();
			int x = pos[0];
			int y = pos[1];
			
			if(x == N && y == M)
				return pos[2];
			
			visit[x][y] = true;
			
			for(int i = 0; i < 4; i++) {
				int movex = x + moveDir[i][0];
				int movey = y + moveDir[i][1];
				
				if(!(1 <= movex && movex <= N && 1 <= movey && movey <= M))
					continue;
				
				if(visit[movex][movey] || miro[movex][movey] == 0)
					continue;
				
				visit[movex][movey] = true;
				
				q.add(new int[] {movex, movey, pos[2] + 1});
			}
		}
		return -1;
	}
}
