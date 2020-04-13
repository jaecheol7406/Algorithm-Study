package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 14889_스타트와 링크
 * 
 * solve -> dfs
 * 
 * 있는 그대로 완탐 dfs로 구현.
 * 완탐으로  N의 절반만큼 팀 나누는 모든 경우의 수 구한 뒤 각 나눈 팀에 대해, 각 팀의 모든 선수끼리의 S(i,j)값 더해서 차이값 min에 갱신시켜 나간다.   
 */
public class Main2 {
	static int N;
	static int[][] s;
	static int min = Integer.MAX_VALUE;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		
		s = new int[N + 1][N + 1];
		for(int i = 1; i <= N; i++) {
			String[] input = br.readLine().split(" ");
			for(int j = 1; j <= N; j++)
				s[i][j] = Integer.parseInt(input[j - 1]);
		}
		
		solve();
	}
	
	static void solve() {
		dfs(new int[N / 2], 0, 0, new boolean[N]);
		System.out.println(min);
	}
	
	static void dfs(int[] arr, int idx, int start, boolean[] check) {
		if(idx == N / 2) {
			int[] arr2 = new int[N / 2];
			int arr2Idx = 0;
			for(int j = 0; j < N; j++) {
				if(!check[j]) {
					arr2[arr2Idx++] = j + 1;
				}
			}
			
			int v = 0;
			for(int j = 0; j < N / 2 - 1; j++) {
				for(int k = j + 1; k < N / 2; k++) {
					v += s[arr[j]][arr[k]];
					v += s[arr[k]][arr[j]];
					v -= s[arr2[j]][arr2[k]];
					v -= s[arr2[k]][arr2[j]];
				}
			}
			int diff = Math.abs(v);
			if(diff < min)
				min = diff;
			
			return;
		}
		
		for(int i = start; i < N; i++) {
			if(!check[0] && i == 1)
				return;
			
			if(!check[i]) {
				check[i] = true;
				arr[idx] = i + 1;
				dfs(arr, idx + 1, i + 1, check);
				check[i] = false;
			}
		}
	}
}