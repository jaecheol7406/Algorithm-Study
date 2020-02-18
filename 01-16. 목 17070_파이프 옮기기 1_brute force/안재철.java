import java.util.Scanner;
/* 
 * 17070_파이프 옮기기 1
 */
public class Main {
	public static final int HORIZONTAL = 0;
	public static final int VERTICAL = 1;
	public static final int DIAGONAL = 2;
	
	static int N;
	static int[][] map;
	static int firstx;
	static int firsty;
	static int secondx;
	static int secondy;
	
	static int caseNum;
	
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		map = new int[N + 1][N + 1];
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++)
				map[i][j] = sc.nextInt();
		}
		firstx = 1;
		firsty = 1;
		secondx = 1;
		secondy = 2;
		
		solve();
		
		System.out.println(caseNum);
		sc.close();
	}
	
	static void solve() {
		int shape = curShape();
		dfs(shape, secondx, secondy);
	}
	
	static void dfs(int shape, int secondx, int secondy) {
		// 끝에 다다르면 caseNum 증가시키고 return
		if(secondx == N && secondy == N) {
			caseNum++;
			return;
		}
		
		// 현재 모양이 수평일 때
		if(shape == HORIZONTAL) {
			// 오른쪽으로 갈 수 있으면 감
			if(canGoRight(secondx, secondy))
				dfs(shape, secondx, secondy + 1);
			
			// 대각선으로 돌 수 있으면 돔
			if(canTurn(secondx, secondy))
				dfs(DIAGONAL, secondx + 1, secondy + 1);
		
		// 현재 모양이 수직일 때
		} else if(shape == VERTICAL) {
			// 밑으로 갈 수 있으면 감
			if(canGoDown(secondx, secondy))
				dfs(shape, secondx + 1, secondy);
			
			// 대각선으로 돌 수 있으면 돔
			if(canTurn(secondx, secondy))
				dfs(DIAGONAL, secondx + 1, secondy + 1);
		
		// 현재 모양이 대각선일 때
		} else {
			// 오른쪽으로 돌 수 있으면 돔
			if(canGoRight(secondx, secondy))
				dfs(HORIZONTAL, secondx, secondy + 1);
			
			// 밑으로 돌 수 있으면 돔
			if(canGoDown(secondx, secondy))
				dfs(VERTICAL, secondx + 1, secondy);
			
			// 대각선으로 갈 수 있으면 감
			if(canTurn(secondx, secondy))
				dfs(DIAGONAL, secondx + 1, secondy + 1);
		}
	}
	
	static int curShape() {
		if(firstx == secondx && firsty + 1 == secondy)
			return HORIZONTAL;
		
		if(firstx + 1 == secondx && firsty == secondy)
			return VERTICAL;
		
		return DIAGONAL;
	}
	
	static boolean canTurn(int x, int y) {
		if(x == N || y == N)
			return false;
		
		if(map[x][y + 1] == 1 || map[x+1][y+1] == 1 || map[x + 1][y] == 1)
			return false;
		
		return true;
	}
	
	static boolean canGoRight(int x, int y) {
		if(y == N || map[x][y + 1] == 1)
			return false;
		
		return true;
	}
	
	static boolean canGoDown(int x, int y) {
		if(x == N || map[x + 1][y] == 1)
			return false;
		
		return true;
	}
}