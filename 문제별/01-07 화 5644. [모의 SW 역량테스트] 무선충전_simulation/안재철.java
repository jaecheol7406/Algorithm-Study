import java.io.IOException;
import java.util.Scanner;

// 5644.무선충전

// bc 표현 클래스
class BC{
	int[] loc;
	int cover;
	int perf;
	
	public BC(int[] loc, int cover, int perf) {
		super();
		this.loc = loc;
		this.cover = cover;
		this.perf = perf;
	}
}

public class Main {
	
	public static final int[][] moveDir = new int[][]{{0, 0}, {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

	static int[][] map;

	static int T;
	static int M, BCCount;
	static int[] A, B;
	static int ax = 1, ay = 1, bx = 10, by = 10;
	static BC[] bcs;
	
	public static void main(String[] args) throws IOException{
		map = new int[11][11];
		Scanner sc = new Scanner(System.in);
		T = sc.nextInt();
		
		for(int t = 1; t <= T; t++) {
			M = sc.nextInt();
			BCCount = sc.nextInt();
			bcs = new BC[BCCount];
			
			A = new int[M];
			B = new int[M];
			for(int i = 0; i < M; i++){
				A[i] = sc.nextInt();
			}
			for(int i = 0; i < M; i++)
				B[i] = sc.nextInt();
			
			for(int i = 0; i < BCCount; i++) {
				int[] p = new int[2];
				p[1] = sc.nextInt();
				p[0] = sc.nextInt();
				bcs[i] = new BC(p, sc.nextInt(), sc.nextInt());
			}
			
			System.out.print("#" + t+ " ");
			System.out.println(result());
			
			ax = 1;
			ay = 1; 
			bx = 10; 
			by = 10;
		}
		sc.close();
	}
	
	static int result() {
		int re = 0;
		
		for(int move = 0; move <= M; move++)
			re += calcMax(move);
		
		return re;
	}
	
	static int calcMax(int move) {		
		int maxa = 0, maxb = 0;
		for(int i = 0; i < BCCount; i++) {
			BC bc = bcs[i];
			if(isContain(bc, ax, ay))
				maxa = Integer.max(maxa, bc.perf);
			if(isContain(bc, bx, by))
				maxb = Integer.max(maxb, bc.perf);
		}
		
		// a, b 둘다 기지국 범위에 없는 경우
		if(maxa == 0 && maxb == 0) {
			if(move != M)
				changePos(move);
			return 0;
		}
		
		// a만 기지국 범위에 있는 경우
		if(maxa != 0 && maxb == 0) {
			if(move != M)
				changePos(move);
			return maxa;
		}
		
		// b만 기지국 범위에 있는 경우
		if(maxa == 0 && maxb != 0) {
			if(move != M)
				changePos(move);
			return maxb;
		}
		
		// a, b 모두 기지국 범위에 있는 경우, 모든 경우의 수 중 최대값 return
		
		int max = 0;
		for(int i = 0; i < BCCount; i++) {
			BC std = bcs[i];
			if(!isContain(std, ax, ay))
				continue;
			
			for(int j = 0; j < BCCount; j++) {
				BC another = bcs[j];
				if(!isContain(another, bx, by))
					continue;
				
				if(i == j)
					max = Integer.max(max, std.perf);
				else
					max = Integer.max(max, std.perf + another.perf);
			}
		}
		
		if(move != M) 
			changePos(move);
				
		return max;
	}
	
	static boolean isContain(BC bc, int x, int y) {
		if((Math.abs(x - bc.loc[0]) + Math.abs(y - bc.loc[1])) <= bc.cover)
			return true;
		else
			return false;
	}
	
	static void changePos(int move) {
		ax = ax + moveDir[A[move]][0];
		ay = ay + moveDir[A[move]][1];

		bx = bx + moveDir[B[move]][0];
		by = by + moveDir[B[move]][1];
	}
}