import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

/* 1726_로봇
문제
많은 공장에서 로봇이 이용되고 있다. 우리 월드 공장의 로봇은 바라보는 방향으로 궤도를 따라 움직이며, 움직이는 방향은 동, 서, 남, 북 가운데 하나이다. 로봇의 이동을 제어하는 명령어는 다음과 같이 두 가지이다.

명령 1. Go k
  - k는 1, 2 또는 3일 수 있다. 현재 향하고 있는 방향으로 k칸 만큼 움직인다.

명령 2. Turn dir
  - dir은 left 또는 right 이며, 각각 왼쪽 또는 오른쪽으로 90° 회전한다.

공장 내 궤도가 설치되어 있는 상태가 아래와 같이 0과 1로 이루어진 직사각형 모양으로 로봇에게 입력된다. 0은 궤도가 깔려 있어 로봇이 갈 수 있는 지점이고, 1은 궤도가 없어 로봇이 갈 수 없는 지점이다. 로봇이 (4, 2) 지점에서 남쪽을 향하고 있을 때,  이 로봇을 (2, 4) 지점에서 동쪽으로 향하도록 이동시키는 것은 아래와 같이 9번의 명령으로 가능하다.



로봇의 현재 위치와 바라보는 방향이 주어졌을 때, 로봇을 원하는 위치로 이동시키고, 원하는 방향으로 바라보도록 하는데 최소 몇 번의 명령이 필요한지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 공장 내 궤도 설치 상태를 나타내는 직사각형의 세로 길이 M과 가로 길이 N이 빈칸을 사이에 두고 주어진다. 이때 M과 N은 둘 다 100이하의 자연수이다. 이어 M줄에 걸쳐 한 줄에 N개씩 각 지점의 궤도 설치 상태를 나타내는 숫자 0 또는 1이 빈칸을 사이에 두고 주어진다. 다음 줄에는 로봇의 출발 지점의 위치 (행과 열의 번호)와 바라보는 방향이 빈칸을 사이에 두고 주어진다. 마지막 줄에는 로봇의 도착 지점의 위치 (행과 열의 번호)와 바라보는 방향이 빈칸을 사이에 두고 주어진다. 방향은 동쪽이 1, 서쪽이 2, 남쪽이 3, 북쪽이 4로 주어진다. 출발지점에서 도착지점까지는 항상 이동이 가능하다.

출력
첫째 줄에 로봇을 도착 지점에 원하는 방향으로 이동시키는데 필요한 최소 명령 횟수를 출력한다.

예제 입력 1 
5 6
0 0 0 0 0 0
0 1 1 0 1 0
0 1 0 0 0 0
0 0 1 1 1 0
1 0 0 0 0 0
4 2 3
2 4 1
예제 출력 1 
9
*/

class MoveInfo{
	int x;
	int y;
	int dir;
	int commandNum;

	public MoveInfo(int x, int y, int dir, int commandNum) {
		this.x = x;
		this.y = y;
		this.dir = dir;
		this.commandNum = commandNum;
	}
}

public class Main {
	public static final int[][] moveDir = new int[][]{{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // 0 : ���� �ε���

	static int M, N;
	static int[][] map;
	static boolean[][][] visit;

	static int startX, startY, endX, endY;
	static int startDir, endDir;

	static int minCommand = Integer.MAX_VALUE;

	public static void main(String[] args) throws IOException{
		Scanner sc = new Scanner(System.in);

		M = sc.nextInt();
		N = sc.nextInt();

		map = new int[M + 1][N + 1];
		visit = new boolean[M + 1][N + 1][5];

		for(int i = 1; i <= M; i++) {
			for(int j = 1; j <= N; j++) {
				map[i][j] = sc.nextInt();
			}
		}

		startX = sc.nextInt();
		startY = sc.nextInt();
		startDir = sc.nextInt();
		endX = sc.nextInt();
		endY = sc.nextInt();
		endDir = sc.nextInt();

//		dfs(startX, startY, startDir, 0);
		bfs();

		System.out.println(minCommand);

		sc.close();
	}	
	
	// bfs : 성공
	static void bfs() {
		Queue<MoveInfo> queue = new LinkedList<>();

		int commandNum = 0;

		queue.add(new MoveInfo(startX, startY, startDir, commandNum));

		while(!queue.isEmpty()) {
			MoveInfo mi = queue.poll();
			visit[mi.x][mi.y][mi.dir] = true;

			if(mi.x == endX && mi.y == endY) {
				int newCommandNum = turn(mi.dir, endDir, mi.commandNum);

				minCommand = Integer.min(minCommand, newCommandNum);
				visit[endX][endY][endDir] = false;
				continue;
			}

			for(int goDir = 1; goDir <= 4; goDir++) {
				if(mi.commandNum != 0 && turn(mi.dir, goDir, mi.commandNum) == mi.commandNum + 2)
					continue;

				int moveX = 0, moveY = 0, step;

				// 작은 step부터 확인, 갈 수 없으면 break, 갈 수 있으면 queue에 add
				for(step = 1; step <= 3; step++) {
					moveX = mi.x + moveDir[goDir][0] * step;
					moveY = mi.y + moveDir[goDir][1] * step;

					if(!(1 <= moveX && moveX <= M && 1 <= moveY && moveY <= N && !visit[moveX][moveY][goDir] && map[moveX][moveY] == 0))
						break;

					int newCommandNum = turn(mi.dir, goDir, mi.commandNum);

					queue.add(new MoveInfo(moveX, moveY, goDir, ++newCommandNum));
				}			
			}
		}
	}
	
	// 재귀 : 메모리 초과
	static void dfs(int x, int y, int dir, int commandNum) {
		visit[x][y][dir] = true;

		if(x == endX && y == endY) {
			int newCommandNum = turn(dir, endDir, commandNum);
			minCommand = Integer.min(minCommand, newCommandNum);
			return;
		}

		for(int goDir = 1; goDir <= 4; goDir++) {
			for(int step = 1; step <= 3; step++) {
				int moveX = x + moveDir[goDir][0] * step;
				int moveY = y + moveDir[goDir][1] * step;
				
				if(!(1 <= moveX && moveX <= M && 1 <= moveY && moveY <= N && !visit[moveX][moveY][goDir] && map[moveX][moveY] == 0))
					break;
				
				int newCommandNum = turn(dir, goDir, commandNum);
				dfs(moveX, moveY, goDir, ++newCommandNum);
			}	
		}
		
		visit[x][y][dir] = false;
	}
	
	// 회전에 따른 증가된 명령 횟수 리턴
	static int turn(int nowDir, int goDir, int commandNum) {
		if(nowDir == 1 || nowDir == 2) { // 현재 방향 동, 서일 때
			if(goDir == 3 || goDir == 4) // 가려는 방향이 남, 북이면
				commandNum += 1; // 한번 회전
			else if(goDir != nowDir) // 가려는 방향이 동, 서이고 반대방향이면 두번 회전, 같은방향이면 회전 x
				commandNum += 2;
		} else { // 현재 방향 남, 북일 때
			if(goDir == 1 || goDir == 2) // 가려는 방향이 동, 서이면
				commandNum += 1; // 한번 회전
			else if(goDir != nowDir) // 가려는 방향이 남, 북이고 반대방향이면 두번 회전, 같은방향이면 회전 x
				commandNum += 2; // 두번 회전
		}

		return commandNum; 
	}
}