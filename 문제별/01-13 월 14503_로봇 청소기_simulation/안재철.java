import java.util.Scanner;


/*

*/

public class Main4 {
	public static final int[][] moveDir = new int[][]{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // ��, ��, ��, �� (�ð����)
	
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
			if(visit[x][y] == 0) {
				visit[x][y] = 1;
				cleanSize++;
			}
			boolean canGo = false;
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
			
			if(canGo)
				continue;
			
			int backX = x, backY = y;
			
			if(dir % 2 == 1) {
				if(dir == 1)
					backY += moveDir[3][1];
				else
					backY += moveDir[1][1];
			} else {
				if(dir == 0)
					backX += moveDir[2][0];
				else
					backX += moveDir[0][0];
			}
			
			if(!(0 < backX && backX < N - 1 && 0 < backY && backY < M - 1) || map[backX][backY] == 1)
				return;
			
			x = backX;
			y = backY;
		}
	}
}
