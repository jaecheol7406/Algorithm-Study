import java.util.Scanner;
/* 17143_낚시왕
문제
낚시왕이 상어 낚시를 하는 곳은 크기가 R×C인 격자판으로 나타낼 수 있다. 격자판의 각 칸은 (r, c)로 나타낼 수 있다. r은 행, c는 열이고, (R, C)는 아래 그림에서 가장 오른쪽 아래에 있는 칸이다. 칸에는 상어가 최대 한 마리 들어있을 수 있다. 상어는 크기와 속도를 가지고 있다.



낚시왕은 처음에 1번 열의 한 칸 왼쪽에 있다. 다음은 1초 동안 일어나는 일이며, 아래 적힌 순서대로 일어난다. 낚시왕은 가장 오른쪽 열의 오른쪽 칸에 이동하면 이동을 멈춘다.

낚시왕이 오른쪽으로 한 칸 이동한다.
낚시왕이 있는 열에 있는 상어 중에서 땅과 제일 가까운 상어를 잡는다. 상어를 잡으면 격자판에서 잡은 상어가 사라진다.
상어가 이동한다.
상어는 입력으로 주어진 속도로 이동하고, 속도의 단위는 칸/초이다. 상어가 이동하려고 하는 칸이 격자판의 경계인 경우에는 방향을 반대로 바꿔서 속력을 유지한채로 이동한다.

왼쪽 그림의 상태에서 1초가 지나면 오른쪽 상태가 된다. 상어가 보고 있는 방향이 속도의 방향, 왼쪽 아래에 적힌 정수는 속력이다. 왼쪽 위에 상어를 구분하기 위해 문자를 적었다.



상어가 이동을 마친 후에 한 칸에 상어가 두 마리 이상 있을 수 있다. 이때는 크기가 가장 큰 상어가 나머지 상어를 모두 잡아먹는다.

낚시왕이 상어 낚시를 하는 격자판의 상태가 주어졌을 때, 낚시왕이 잡은 상어 크기의 합을 구해보자.

입력
첫째 줄에 격자판의 크기 R, C와 상어의 수 M이 주어진다. (2 ≤ R, C ≤ 100, 0 ≤ M ≤ R×C)

둘째 줄부터 M개의 줄에 상어의 정보가 주어진다. 상어의 정보는 다섯 정수 r, c, s, d, z (1 ≤ r ≤ R, 1 ≤ c ≤ C, 0 ≤ s ≤ 1000, 1 ≤ d ≤ 4, 1 ≤ z ≤ 10000) 로 이루어져 있다. (r, c)는 상어의 위치, s는 속력, d는 이동 방향, z는 크기이다. d가 1인 경우는 위, 2인 경우는 아래, 3인 경우는 오른쪽, 4인 경우는 왼쪽을 의미한다.

두 상어가 같은 크기를 갖는 경우는 없고, 하나의 칸에 둘 이상의 상어가 있는 경우는 없다.

출력
낚시왕이 잡은 상어 크기의 합을 출력한다.

예제 입력 1 
4 6 8
4 1 3 3 8
1 3 5 2 9
2 4 8 4 1
4 5 0 1 4
3 3 1 2 7
1 5 8 4 3
3 6 2 1 2
2 2 2 3 5
예제 출력 1 
22
*/
public class Main4 {
	
	public static final int[][] moveDir = new int[][]{{0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1}}; // 북 남 동 서

	static int R, C, sharkNum;
	static int[][][] map;
	static Shark[] sharks;
	static boolean[] dead;
	
	static int resultSize = 0;
	
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		
		R = sc.nextInt();
		C = sc.nextInt();
		sharkNum = sc.nextInt();
		map = new int[R + 1][C + 1][2]; // 0인덱스 값에는 상어가 이동 끝마친 후 상어, 1인덱스는 상어 이동할 때 최대값 비교하면서 상어 저장 용도
		sharks = new Shark[sharkNum + 1];
		dead = new boolean[sharkNum + 1];
		
		for(int sh = 1; sh <= sharkNum; sh++) {
			int x = sc.nextInt();
			int y = sc.nextInt();
			int speed = sc.nextInt();
			int dir = sc.nextInt();
			int size = sc.nextInt();
			
			// 격자판에서 물고기가 이동할 때 원점으로 여러번 돌아온 것 무시하고 나서의 나머지 이동만 따짐. (시간 줄이기)
			// 방향이 동, 서일 때 (격자판의 가로 길이 C - 1) * 2 (원점으로 돌아오는 이동 거리)로 나눠줌. 남, 북일 때는 세로길이(R)로 계산
			if(dir == 3 || dir == 4)
				speed = speed % ((C - 1) * 2);
			else
				speed = speed % ((R - 1) * 2);
			
			map[x][y][0] = sh;
			sharks[sh] = new Shark(x, y, speed, dir, size);
		}
		
		calcSize();
		
		System.out.println(resultSize);
		
		sc.close();
	}
	
	static void calcSize() {
		for(int y = 1; y <= C; y++) { // 1초마다 1열씩 사람 이동
			for(int x = 1; x <= R; x++) { // 바닥(1인덱스)부터 상어 탐색
				if(map[x][y][0] != 0) {
					int sharkIdx = map[x][y][0];
					Shark shark = sharks[sharkIdx];
					dead[sharkIdx] = true; // 죽음
					map[x][y][0] = 0; // 0은 상어 없다는 뜻
					resultSize += shark.size;
					break;
				}
			}
			fishMove();
		}
	}
	
	static void fishMove() {
		for(int sharkIdx = 1; sharkIdx <= sharkNum; sharkIdx++) {
			// 살아있는 상어만
			if(dead[sharkIdx])
				continue;
			
			Shark shark = sharks[sharkIdx];
			
			map[shark.x][shark.y][0] = 0; // 상어 이동하기 전 있던 칸 비움
			
			int movex = shark.x;
			int movey = shark.y;
			int dir = shark.dir;
			int speed = shark.speed;
			
			if(dir == 3 || dir == 4) { // 동, 서일 때
				while(speed-- > 0) {
					if(movey == 1) { // 서쪽 경계이면
						movey += 1; // 동쪽 이동,
						dir = 3; // 방향 동쪽
					} else if(movey == C){ // 동쪽 경계이면
						movey -= 1; // 서쪽 이동,
						dir = 4; // 방향 서쪽
					} else { // 경계 아니고
						if(dir == 3)  // 방향 동쪽이면
							movey += 1; // 동쪽으로 이동
						else // 서쪽이면
							movey -= 1; // 서쪽으로 이동
					}
				}
			} else { // 남, 북일 때
				while(speed-- > 0) {
					if(movex == 1) { // 북쪽 경계이면
						movex += 1; // 남쪽 이동
						dir = 2; // 방향 남쪽
					} else if(movex == R) { // 남쪽 경계이면
						movex -= 1; // 북쪽 이동
						dir = 1; // 방향 북쪽
					} else { // 경계 아니고
						if(dir == 1) // 방향 북쪽이면
							movex -= 1; // 북쪽 이동
						else // 남쪽이면
							movex += 1; //남쪽 이동
					}
				}
			}
			
			sharks[sharkIdx].x = movex;
			sharks[sharkIdx].y = movey;
			sharks[sharkIdx].dir = dir;
			
			// 상어 이동은 1인덱스로, 0인덱스로 하면 이동 전 상어와 비교 못피함
			if(map[movex][movey][1] == 0) // 상어 없으면
				map[movex][movey][1] = sharkIdx; // 상어 저장
			else { // 상어 있으면
				Shark origin = sharks[map[movex][movey][1]]; // 원래 있던 상어와
				if(origin.size < shark.size) { // 크기 비교해서 원래 상어가 작으면
					dead[map[movex][movey][1]] = true; // 원래있던 상어 죽고
					map[movex][movey][1] = sharkIdx; // 새로운 상어 저장
				} else // 원래 상어가 더 크면
					dead[sharkIdx] = true; // 새로운 상어 죽음
			}
		}
		
		// 1인덱스에 저장한 이동한 상어들 0인덱스로 옮김
		for(int sharkIdx = 1; sharkIdx <= sharkNum; sharkIdx++) {
			Shark shark = sharks[sharkIdx];
			if(map[shark.x][shark.y][1] != 0) {
				map[shark.x][shark.y][0] = map[shark.x][shark.y][1];
				map[shark.x][shark.y][1] = 0;
			}
		}
	}
}

//상어
class Shark{
	int x; 
	int y;
	int speed;
	int dir;
	int size;
	
	public Shark(int x, int y, int speed, int dir, int size) {
		super();
		this.x = x;
		this.y = y;
		this.speed = speed;
		this.dir = dir;
		this.size = size;
	}
}