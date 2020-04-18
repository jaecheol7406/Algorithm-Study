package _2020_04;

import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 14499_주사위 굴리기
 * 
 * main -> move -> shiftRight, shiftLeft
 * 
 * 앞, 뒤, 왼, 오 4개를 leftRight, 앞, 뒤, 위, 아래 4개를 upDown에 0으로 초기화 해놓고, 방향에 따라 처리한다. 이 때 leftRight, upDown의 0 인덱스가 위, 3이 아래이다.
 * 방향이 0 (동쪽) 일 때는 1인덱스가 바닥에 닿기때문에 1 인덱스의 값으로 처리하고, leftRight의 숫자들이 1씩 밀려나가기 때문에 shiftRight 해준다.
 * 나머지 방향도 동일하게 한다.
 */
public class Main {
	static int[] dx = {0,0,-1,1};
	static int[] dy = {1,-1,0,0};
	
	static int N,M,x,y,k;
	static int[][] map;
	
	static int[] leftRight = new int[4];
	static int[] upDown = new int[4];
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		x = Integer.parseInt(input[2]);
		y = Integer.parseInt(input[3]);
		k = Integer.parseInt(input[4]);
		
		map = new int[N][M];
		for(int i = 0; i < N; i++) {
			input = br.readLine().split(" ");
			for(int j = 0; j < M; j++)
				map[i][j] = Integer.parseInt(input[j]);
		}
		
		input = br.readLine().split(" ");
		for(int i = 0; i < k; i++) {
			if(move(Integer.parseInt(input[i]) - 1))
				System.out.println(leftRight[0]);
		}
	}
	
	static boolean move(int dir) {
		int nextX = x + dx[dir];
		int nextY = y + dy[dir];
		
		if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < M))
			return false;
		
		x = nextX;
		y = nextY;
		
		if(dir == 0) {
			if(map[nextX][nextY] == 0)
				map[nextX][nextY] = leftRight[1];
			else {
				leftRight[1] = map[nextX][nextY];
				map[nextX][nextY] = 0;
			}
			
			shiftRight(leftRight);
			upDown[0] = leftRight[0];
			upDown[2] = leftRight[2];
			
		} else if(dir == 1) {
			if(map[nextX][nextY] == 0)
				map[nextX][nextY] = leftRight[3];
			else {
				leftRight[3] = map[nextX][nextY];
				map[nextX][nextY] = 0;
			}
			
			shiftLeft(leftRight);
			upDown[0] = leftRight[0];
			upDown[2] = leftRight[2];
			
		} else if(dir == 2) {
			if(map[nextX][nextY] == 0)
				map[nextX][nextY] = upDown[3];
			else {
				upDown[3] = map[nextX][nextY];
				map[nextX][nextY] = 0;
			}
			
			shiftLeft(upDown);
			leftRight[0] = upDown[0];
			leftRight[2] = upDown[2];
			
		} else {
			if(map[nextX][nextY] == 0)
				map[nextX][nextY] = upDown[1];
			else {
				upDown[1] = map[nextX][nextY];
				map[nextX][nextY] = 0;
			}
			
			shiftRight(upDown);
			leftRight[0] = upDown[0];
			leftRight[2] = upDown[2];
		}
		
		return true;
	}
	
	static void shiftRight(int[] arr) {
		int last = arr[arr.length - 1];
		for(int i = arr.length - 1; i >= 1; i--)
			arr[i] = arr[i - 1];
		arr[0] = last;
	}
	
	static void shiftLeft(int[] arr) {
		int first = arr[0];
		for(int i = 0; i < arr.length - 1; i++)
			arr[i] = arr[i + 1];
		arr[arr.length - 1] = first;
	}
}