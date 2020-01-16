
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Main_5653swea_StemCell_mhs {
	static int T, N, M, K;
	static int map[][];
	static int temp[][];
	static Queue<Cell> Q1, Q2;
	static int dr[] = { 0, 0, -1, +1 };
	static int dc[] = { -1, +1, 0, 0 };
	static int cellCnt;
	

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		T = sc.nextInt();

		for (int tc = 1; tc <= T; tc++) {
			N = sc.nextInt();
			M = sc.nextInt();
			K = sc.nextInt();

			map = new int[1200][1200];
			Q1 = new LinkedList<Cell>();

			for (int r = 1; r <= N; r++) {
				for (int c = 1; c <= M; c++) {
					map[r + 300][c + 300] = sc.nextInt();
					if (map[r + 300][c + 300] > 0) {
						Q1.offer(new Cell(r + 300, c + 300, map[r + 300][c + 300], 0, 0));
					}
				}
			}

			cellCnt = Q1.size();

			for (int time = 1; time <= K; time++) {
				makeCell();
			}

			System.out.println("#" + tc + " " + cellCnt);
		}
		sc.close();
	}

	public static void makeCell() {

		Q2 = new LinkedList<Cell>();
		temp = new int[N + 610][M + 610];

		for (int i = 1; i <= cellCnt; i++) {
			Cell c = Q1.poll();

			if (c.stat == 1 && c.statTime == 0) {

				for (int j = 0; j < 4; j++) {
					Cell child = new Cell(c.r + dr[j], c.c + dc[j], c.power, 0, 0);
					if (child.c < 1 || child.c >= M + 610 || child.r < 1 || child.r > N + 610) {
						continue;
					}

					if (map[child.r][child.c] > 0) {
						continue;
					}

					if (child.power > temp[child.r][child.c]) {
						temp[child.r][child.c] = child.power;
						Q2.offer(child);
					}
				}

			}
			c.statTime++;

			if (c.statTime == c.power) {// 상태 변환
				c.stat++;
				c.statTime = 0;
			}
			if (c.stat < 2) {
				Q1.offer(c);
			}
		}

		while (!Q2.isEmpty()) {
			Cell child = Q2.poll();
			if (temp[child.r][child.c] == child.power) {
				map[child.r][child.c] = child.power;
				Q1.offer(child);
			}
		}

		cellCnt = Q1.size();
	}

	static class Cell {
		int r;
		int c;
		int power;
		int stat;
		int statTime;

		public Cell(int r, int c, int power, int stat, int statTime) {
			this.r = r;
			this.c = c;
			this.power = power;
			this.stat = stat;
			this.statTime = statTime;
		}
	}
}
