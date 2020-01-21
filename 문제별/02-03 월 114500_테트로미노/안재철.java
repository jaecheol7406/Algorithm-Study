import java.util.Scanner;
/*
 * 14500_테트로미노
 */
public class Main {
	static int N, M;
	static int[][] map;
	static int max = -1;
	public static void main(String[] args) {
		input();
		solve();
		print();
	}

	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		map = new int[N][M];
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				map[i][j] = sc.nextInt();
		sc.close();
	}

	static void solve() {
		one(); // 1번째 도형 1번회전
		two(); // 2번째 도형 0번 회전
		threeAndFour(); // 3, 4번째 도형 4번 회전, 좌우로 뒤집어서 4번 회전
		five(); // 5번째 도형 4번 회전
	}

	static void one() {
		// 1번만 회전해봐도 된다. 그 이후는 모양 중복
		for(int rota = 0; rota < 2; rota++) {
			int sum = 0;

			// 탐색
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < M - 3; j++) {
					sum += map[i][j];
					sum += map[i][j + 1];
					sum += map[i][j + 2];
					sum += map[i][j + 3];

					max = Integer.max(max, sum);
					sum = 0;
				}
			}	

			map = rotation(map);
			int temp = N;
			N = M;
			M = temp;
		}
	}

	static void two() {
		int sum = 0;

		// 2번째 도형 원래모양 탐색
		for(int i = 0; i < N - 1; i++) {
			for(int j = 0; j < M - 1; j++) {
				sum += map[i][j];
				sum += map[i][j + 1];
				sum += map[i + 1][j];
				sum += map[i + 1][j + 1];

				max = Integer.max(max, sum);
				sum = 0;
			}
		}
	}

	static void threeAndFour() {
		for(int rota = 0; rota < 4; rota++) {
			int sum = 0;

			// 3번째 도형 원래모양 탐색
			for(int i = 0; i < N - 2; i++) {
				for(int j = 0; j < M - 1; j++) {
					sum += map[i][j];
					sum += map[i + 1][j];
					sum += map[i + 2][j];
					sum += map[i + 2][j + 1];

					max = Integer.max(max, sum);
					sum = 0;					
				}
			}

			// 3번째 도형 옆으로 뒤집어서 탐색
			for(int i = 0; i < N - 2; i++) {
				for(int j = 1; j < M; j++) {
					sum += map[i][j];
					sum += map[i + 1][j];
					sum += map[i + 2][j];
					sum += map[i + 2][j - 1];

					max = Integer.max(max, sum);
					sum = 0;					
				}
			}

			// 4번째 도형 원래모양 탐색
			for(int i = 0; i < N - 2; i++) {
				for(int j = 0; j < M - 1; j++) {
					sum += map[i][j];
					sum += map[i + 1][j];
					sum += map[i + 1][j + 1];
					sum += map[i + 2][j + 1];

					max = Integer.max(max, sum);
					sum = 0;					
				}
			}

			// 4번째 도형 옆으로 뒤집어서 탐색
			for(int i = 0; i < N - 2; i++) {
				for(int j = 1; j < M; j++) {
					sum += map[i][j];
					sum += map[i + 1][j];
					sum += map[i + 1][j - 1];
					sum += map[i + 2][j - 1];

					max = Integer.max(max, sum);
					sum = 0;					
				}
			}

			// 회전
			map = rotation(map);
			int temp = N;
			N = M;
			M = temp;
		}
	}
	static void five() {
		for(int rota = 0; rota < 4; rota++) {
			int sum = 0;

			// 5번째 도형 원래모양 탐색
			for(int i = 0; i < N - 1; i++) {
				for(int j = 0; j < M - 2; j++) {
					sum += map[i][j];
					sum += map[i][j + 1];
					sum += map[i][j + 2];
					sum += map[i + 1][j + 1];

					max = Integer.max(max, sum);
					sum = 0;	
				}
			}

			map = rotation(map);
			int temp = N;
			N = M;
			M = temp;
		}
	}

	// 직사각형 2차원 배열 우로 90도 회전
	static int[][] rotation(int[][] arr) {
		int n = arr.length;
		int m = arr[0].length;
		int[][] temp = new int[m][n];
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				temp[i][j] = arr[n - 1 - j][i];
			}
		}
		return temp;
	}

	static void print() {
		System.out.println(max);
	}
}