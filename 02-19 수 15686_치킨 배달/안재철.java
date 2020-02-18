import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;
/*
 * 15686_치킨 배달
 */
public class Main {
	static int N, M;
	static int[][] map;
	static ArrayList<Pos> homePosList = new ArrayList<>();
	static ArrayList<Pos> chickenPosList = new ArrayList<>();
	static int min = Integer.MAX_VALUE;
	
	public static void main(String[] args) {
		input();
		solve();
		System.out.println(min);
	}

	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		map = new int[N][N];
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				int info = sc.nextInt();
				map[i][j] = info;
				if(info == 1)
					homePosList.add(new Pos(i, j));
				else if(info == 2)
					chickenPosList.add(new Pos(i, j));
			}
		}
		sc.close();
	}

	static void solve() {
		comb(new boolean[chickenPosList.size()], new int[M], 0, 0);
	}

	static void comb(boolean[] check, int[] re, int start, int idx) {
		if(idx == M) {
			calcTotal(re);
			return;
		}

		for(int i = start; i < check.length; i++) {
			if(!check[i]) {
				check[i] = true;
				re[idx] = i;
				comb(check, re, i + 1, idx + 1);
				check[i] = false;
			}
		}
	}

	static void calcTotal(int[] chickenIdxs) {
		int total = 0;
		for(Pos hPos : homePosList) {
			int minDis = Integer.MAX_VALUE;
			for(int i = 0; i < chickenIdxs.length; i++) {
				Pos chPos = chickenPosList.get(chickenIdxs[i]);
				int distance = Math.abs(hPos.x - chPos.x) + Math.abs(hPos.y - chPos.y);
				if(distance < minDis)
					minDis = distance;
			}
			total += minDis;
		}
		min = Integer.min(min, total);
	}
}

class Pos{
	int x;
	int y;

	public Pos(int x, int y) {
		this.x = x;
		this.y = y;
	}

	@Override
	public boolean equals(Object o) {
		Pos ano = (Pos)o;
		if(this.x == ano.x && this.y == ano.y)
			return true;
		else
			return false;
	}

	@Override
	public int hashCode() {
		return Objects.hash(x, y);
	}
}