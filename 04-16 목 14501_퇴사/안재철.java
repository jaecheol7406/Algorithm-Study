package _2020_04;

import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 14501_퇴사
 * 
 * main -> solve -> dfs
 * 
 * info 2차원배열에 N개 정보 저장. 0 인덱스는 T, 1은 P임.
 * 
 * dfs에 상담 가능한 현재 날과 지금까지 더한 금액 p에 넣어서 dfs로 탐색해나감.
 * 모든 날에 대해 상담이 가능한지에 대해 검사 하며 불가능하면 지금까지의 p값 max에 갱신하며 끝낸다.(i + info[i][0] > N + 1, 즉 현재 일과 걸리는 시간이 전체 일수 넘어가면)
 * 가능하면 다음 상담할 수 있늘 날 start에 넣고 dfs ㄱㄱ
 */
public class Main3 {
	static int N;
	static int[][] info;
	static int max = 0;

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());

		info = new int[N + 1][2];
		for(int i = 1; i <= N; i++) {
			String[] input = br.readLine().split(" ");
			info[i][0] = Integer.parseInt(input[0]);
			info[i][1] = Integer.parseInt(input[1]);
		}

		solve();
	}

	static void solve() {
		dfs(1, 0);
		System.out.println(max);
	}

	static void dfs(int start, int p) {
		// 끝까지 한번에 가는 경우 갱신
		if(start == N + 1) {
			if(max < p)
				max = p;
			return;
		}
		
		for(int i = start; i <= N; i++) {
			if(i + info[i][0] <= N + 1)
				dfs(i + info[i][0], p + info[i][1]);
			else {
				if(max < p)
					max = p;
			}
		}
	}
}