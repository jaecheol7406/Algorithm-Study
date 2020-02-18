import java.util.Scanner;


/* 14503_로봇 청소기
문제
로봇 청소기가 주어졌을 때, 청소하는 영역의 개수를 구하는 프로그램을 작성하시오.

로봇 청소기가 있는 장소는 N×M 크기의 직사각형으로 나타낼 수 있으며, 1×1크기의 정사각형 칸으로 나누어져 있다. 각각의 칸은 벽 또는 빈 칸이다. 청소기는 바라보는 방향이 있으며, 이 방향은 동, 서, 남, 북중 하나이다. 지도의 각 칸은 (r, c)로 나타낼 수 있고, r은 북쪽으로부터 떨어진 칸의 개수, c는 서쪽으로 부터 떨어진 칸의 개수이다.

로봇 청소기는 다음과 같이 작동한다.

현재 위치를 청소한다.
현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다.
왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
로봇 청소기는 이미 청소되어있는 칸을 또 청소하지 않으며, 벽을 통과할 수 없다.

입력
첫째 줄에 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 50)

둘째 줄에 로봇 청소기가 있는 칸의 좌표 (r, c)와 바라보는 방향 d가 주어진다. d가 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을, 3인 경우에는 서쪽을 바라보고 있는 것이다.

셋째 줄부터 N개의 줄에 장소의 상태가 북쪽부터 남쪽 순서대로, 각 줄은 서쪽부터 동쪽 순서대로 주어진다. 빈 칸은 0, 벽은 1로 주어진다. 장소의 모든 외곽은 벽이다.

로봇 청소기가 있는 칸의 상태는 항상 빈 칸이다.

출력
로봇 청소기가 청소하는 칸의 개수를 출력한다.
*/

public class Main {
	public static final int[][] moveDir = new int[][]{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // 북 동 남 서 (시계방향)
	
	static int N, M;
	static int map[][];
	static int visit[][];
	static int x;
	static int y;
	static int dir;
	
	static int cleanSize;
	
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		map = new int[N][M];
		visit = new int[N][M];
		x = sc.nextInt();
		y = sc.nextInt();
		dir = sc.nextInt();
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++)
				map[i][j] = sc.nextInt();
		}
		
		clean();
		System.out.println(cleanSize);
		sc.close();
	}
	
	static void clean() {
		while(true) {
			// 청소 표시
			if(visit[x][y] == 0) {
				visit[x][y] = 1;
				cleanSize++;
			}
			boolean canGo = false;

			// 반시계방향으로 4번 회전해본다. (현재 방향의 서쪽부터)
			int turnTime = 4;
			while(turnTime-- > 0) {
				dir--;
				if(dir == -1)
					dir = 3;
				
				int nextX = x + moveDir[dir][0];
				int nextY = y + moveDir[dir][1];
				
				if(!(0 < nextX && nextX < N - 1 && 0 < nextY && nextY < M - 1))
					continue;
				
				if(map[nextX][nextY] == 1 || visit[nextX][nextY] == 1)
					continue;
				
				canGo = true;
				
				x = nextX;
				y = nextY;
				break;
			}
			
			// 청소 가능하면 이동
			if(canGo)
				continue;
			
			// 청소 불가능하면 후진
			int backX = x, backY = y;
			
			// 현재 방향의 반대방향으로 후진
			if(dir % 2 == 1) { // 현재 방향이 동, 서쪽일 경우
				if(dir == 1) // 동쪽일 경우
					backY += moveDir[3][1]; // 서쪽으로 후진
				else // 서쪽일 경우
					backY += moveDir[1][1]; // 동쪽으로 후진
			} else { // 현재 방향이 남, 북쪽일 경우
				if(dir == 0) // 북쪽일 경우
					backX += moveDir[2][0]; // 남쪽으로 후진
				else // 남쪽일 경우
					backX += moveDir[0][0]; // 북쪽으로 후진
			}
			
			if(!(0 < backX && backX < N - 1 && 0 < backY && backY < M - 1) || map[backX][backY] == 1)
				return;
			
			x = backX;
			y = backY;
		}
	}
}
