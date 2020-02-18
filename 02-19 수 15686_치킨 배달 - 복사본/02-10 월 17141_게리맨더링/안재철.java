import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
/*
17141_게리맨더링
*/
public class Main {
	static int N, M;
	static int min = Integer.MAX_VALUE;
	
	static class Section {
		int pNum;
		int[] adjoin;
		
		public Section(int pNum) {
			this.pNum = pNum;
		}
	}
	
	static Section[] sections;
	
	public static void main(String[] args) {
		input();
		solve();
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		sections = new Section[N + 1];
		
		for(int i = 1; i <= N; i++) {
			sections[i] = new Section(sc.nextInt());
		}
		
		for(int i = 1; i <= N; i++) {
			int[] adj = new int[sc.nextInt()];
			for(int j = 0; j < adj.length; j++)
				adj[j] = sc.nextInt();
			sections[i].adjoin = adj;
		}
		
		sc.close();
	}
	
	static void solve() {
		for(int m = 1; m <= N / 2; m++) {
			M = m;
			comb(new boolean[N], 0, new int[M], 0); // N M 조합
		}
		
		if(min == Integer.MAX_VALUE)
			min = -1;
		
		System.out.println(min);
	}
	
	static void comb(boolean[] check, int start, int[] arr, int idx) {
		if(idx == M) {
			int[] another = new int[N - M];
			int anoidx = 0;
			for(int i = 0; i < N; i++) {
				if(!check[i])
					another[anoidx++] = i + 1;
			}
			
			if(isConnected(arr) && isConnected(another)) {
				min = Integer.min(min, Math.abs(getPNum(arr) - getPNum(another)));
			}
			
			return;
		}
		
		for(int i = start; i < N; i++) {
			check[i] = true;
			arr[idx] = i + 1;
			comb(check, i + 1, arr, idx + 1);
			check[i] = false;
		}
	}
	
	static boolean isConnected(int[] arr) {
		boolean[] visit = new boolean[arr.length];
		Queue<Integer> q = new LinkedList<>();
		q.add(0);
		while(!q.isEmpty()) {
			int idx = q.poll();
			visit[idx] = true;
			Section section = sections[arr[idx]];
			for(int i = 0; i < section.adjoin.length; i++) {
				int adj = section.adjoin[i];
				for(int j = 0; j < arr.length; j++) {
					if(!visit[j] && adj == arr[j])
						q.add(j);
				}
			}
		}
		for(int i = 0; i < visit.length; i++) {
			if(!visit[i])
				return false;
		}
		return true;
	}
	
	static int getPNum(int[] arr) {
		int pNum = 0;
		for(int i = 0; i < arr.length; i++)
			pNum += sections[arr[i]].pNum;
		return pNum;
	}
}