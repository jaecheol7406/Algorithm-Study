//21052 KB, 336 ms, 1736 B
import java.util.Scanner;

public class Main {
	static int N, M, ansMin=Integer.MAX_VALUE;
	static int[] chickenLen;
	static int[][] map;
	static P[] stores, houses;

	public static void main(String[] args) {
		int s=0, h=0; 
		Scanner sc = new Scanner(System.in);
		N=sc.nextInt(); M=sc.nextInt(); sc.nextLine();
		map=new int[N][N];
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) {
			map[i][j] = sc.nextInt();
			if(map[i][j] == 1) h++;
			if(map[i][j] == 2) s++;
		}
		houses = new P[h];
		stores = new P[s];
		chickenLen = new int[h];
		h=0; s=0;
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) {
			if(map[i][j] == 1) houses[h++] = new P(i,j);
			if(map[i][j] == 2) stores[s++] = new P(i,j);
			
		}
		sc.close();
		
		
		for(int k=1; k<=M; k++) {
			int[] bucket = new int[k];
			Combination(0, 0, s, bucket, k);
		}
		System.out.println(ansMin);
	}
	static void calcLength(int[] bucket) {
		for(int i=0; i<chickenLen.length; i++)
			chickenLen[i] = Integer.MAX_VALUE;
		for(int i=0; i<houses.length; i++) {
			int x1=houses[i].r, y1=houses[i].c;
			for(int b : bucket) {
				int x2 = stores[b].r, y2 = stores[b].c;
				int len = Math.abs(x2-x1) + Math.abs(y2-y1);
				if(chickenLen[i] > len)
					chickenLen[i] = len;
			}
		}
		int cityLen=0;
		for(int c : chickenLen)
			cityLen += c;
		if(ansMin > cityLen)
			ansMin = cityLen;
	}
	static void Combination(int idxN, int idxR, int s, int[] bucket, int k) {
		if(k==0) {
			calcLength(bucket);
			return;
		}
		for(int i=0; i<s; i++)
		{
			bucket[idxR] = i;
			if(idxN!=0 && bucket[idxN-1] >= bucket[idxN]) continue;
			Combination(idxN+1, idxR+1, s, bucket, k-1);
		}
		return;
	}
	static class P{
		int r,c;
		public P(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}
}