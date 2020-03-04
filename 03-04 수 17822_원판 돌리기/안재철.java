import java.util.Scanner;
/*
 * 17822_원판 돌리기
 * 약속때매 내일 쓸게요
 */
public class Main3 {
	static int N, M, T;
	static int[][] board;

	public static void main(String[] args) {
		input();
		int sum = 0;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				if(board[i][j] != -1)
					sum += board[i][j];
			}
		}
		System.out.println(sum);
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		T = sc.nextInt();
		
		board = new int[N][M];
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				board[i][j] = sc.nextInt();
		
		for(int i = 0; i < T; i++) {
			int x = sc.nextInt();
			int d = sc.nextInt();
			int k = sc.nextInt();
			
			rotate(x, d, k);
		}
		
		sc.close();
	}
	
	static void rotate(int x, int d, int k) {
		for(int i = 0; i < N; i++) {
			if((i + 1) % x != 0)
				continue;
			
			int[] temp = new int[M];
			if(d == 0) {
				for(int j = 0; j < M; j++) {
					temp[(j + k) % M] = board[i][j];
				}
			} else {
				for(int j = M - 1; j >= 0; j--) {
					int newIdx = j - k;
					if(newIdx < 0)
						newIdx = M + newIdx;
					temp[newIdx] = board[i][j];
				}
			}
			board[i] = temp.clone();
		}
		findAdjoin();
	}
	
	static void findAdjoin() {
		boolean[][] deleted = new boolean[N][M];
		boolean adjoinAndSame = false;
		
		for(int i = 0; i < N; i++) {
			int before = board[i][M - 1];
			for(int j = 0; j < M; j++) {
				int now = board[i][j];
				if(now == -1 || before == -1) {
					before = now;
					continue;
				}
				
				if(now == before) {
					if(!adjoinAndSame)
						adjoinAndSame = true;
					
					deleted[i][j] = true;
					if(j == 0)
						deleted[i][M - 1] = true;
					else
						deleted[i][j - 1] = true;
				} else {
					before = now;
				}
			}
		}
		
		for(int j = 0; j < M; j++) {
			int before = board[0][j];
			for(int i = 1; i < N; i++) {
				int now = board[i][j];
				if(now == -1 || before == -1) {
					before = now;
					continue;
				}
				
				if(now == before) {
					if(!adjoinAndSame)
						adjoinAndSame = true;
					
					deleted[i][j] = true;
					deleted[i - 1][j] = true;
				} else
					before = now;
			}
		}
		
		if(adjoinAndSame) {
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < M; j++) {
					if(deleted[i][j])
						board[i][j] = -1;
				}
			}
		} else {
			int notDeleted = 0;
			double sum = 0;
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < M; j++) {
					if(board[i][j] != -1) {
						notDeleted++;
						sum += board[i][j];
					}
				}
			}
			
			double avg = sum / notDeleted;
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < M; j++) {
					if(board[i][j] < avg)
						board[i][j]++;
					else if(board[i][j] > avg)
						board[i][j]--;
				}
			}
		}
	}
}