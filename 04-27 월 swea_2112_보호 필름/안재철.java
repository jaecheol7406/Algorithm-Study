package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 2112. [모의 SW 역량테스트] 보호 필름
 * 
 * main -> solve -> dfs1 -> dfs2 -> (putDrug -> copy, test)
 * 
 * main에서 입력받은 후 solve에서 약물 투입 안해도 test 통과하면 ans = 0 주고 끝낸다.
 * 
 * 전체 투입할 수 있는 D개의 줄에서 1개 바꾸는 경우 ~ 모두 바꾸는 경우에 대해 조합으로 선택해(dfs1) 각각의 경우에 대해 dfs2로 A, B 약물투입하는 모든 경우의 수에 대해 test한다.
 * 
 * 예를 들어 총 5개의 줄을 바꾼다고 했을 때, dfs1로 nC5 5개의 인덱스 조합 구하고, 구한 인덱스들 dIdxs에 저장해놓는다.
 * 이후, 5개 중  0개를 A로 -> 나머지 5개 B
 *			 1개를 A로 -> 나머지 4개 B
 *			 2개를 A로 -> 나머지 3개 B
 *	각각 dfs2로 조합 구한 후, putDrug로 바꿔본 후 test 통과하면 그 때의 바꾼 줄의 개수 ans에 주고 끝낸다.
 *  이 때 각각의 경우에서 A B 바꿔서 다시 해본다.
 */
public class Solution {
	static int T, D, W, K;
	static int[][] map;
	static int ans;
	
	static int[] dIdxs;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		for(int t = 1; t <= T; t++) {
			String[] input = br.readLine().split(" ");
			D = Integer.parseInt(input[0]);
			W = Integer.parseInt(input[1]);
			K = Integer.parseInt(input[2]);
			
			map = new int[D][W];
			for(int i = 0; i < D; i++) {
				input = br.readLine().split(" ");
				for(int j = 0; j < W; j++) {
					map[i][j] = Integer.parseInt(input[j]);
				}
			}
			
			solve();
			
			System.out.println("#" + t + " " + ans);
		}
	}
	
	static void solve() {
		if(K == 1 || test(map)) {
			ans = 0;
			return;
		}
			
		for(int drug = 1; drug <= D; drug++) {			
			if(dfs1(new int[drug], 0, new boolean[D], 0))
				return;
		}
	}
	
	static boolean dfs1(int[] arr, int idx, boolean[] check, int start) {
		if(idx == arr.length) {
			dIdxs = arr;
			for(int r = 0; r <= arr.length / 2; r++) {
				if(dfs2(new int[r], 0, new boolean[arr.length], 0))
					return true;
			}
			
			return false;
		}
		
		for(int i = start; i < D; i++) {
			if(!check[i]) {
				check[i] = true;
				arr[idx] = i;
				if(dfs1(arr, idx + 1, check, i + 1))
					return true;
				
				check[i] = false;
			}
		}
		
		return false;
	}
	
	static boolean dfs2(int[] arr, int idx, boolean[] check, int start) {
		if(idx == arr.length) {
			int[] arr2 = new int[check.length - arr.length];
			int arr2Idx = 0;
			for(int i = 0; i < check.length; i++) {
				if(!check[i])
					arr2[arr2Idx++] = dIdxs[i];
			}
			
			int[][] map1 = putDrug(arr, arr2);
			if(test(map1)) {
				ans = check.length;
				return true;
			}
			
			int[][] map2 = putDrug(arr2, arr);
			if(test(map2)) {
				ans = check.length;
				return true;
			}
			
			return false;
		}
		
		for(int i = start; i < check.length; i++) {
			if(!check[i]) {
				check[i] = true;
				arr[idx] = dIdxs[i];
				if(dfs2(arr, idx + 1, check, i + 1))
					return true;
				
				check[i] = false;
			}
		}
		
		return false;
	}
	
	static int[][] putDrug(int[] A, int[] B) {
		int[][] temp = copy(map);
		for(int d : A) {
			for(int j = 0; j < W; j++)
				temp[d][j] = 0;
		}
		
		for(int d : B) {
			for(int j = 0; j < W; j++)
				temp[d][j] = 1;
		}
		
		return temp;
	}
	
	static int[][] copy(int[][] map){
		int[][] temp = new int[map.length][map[0].length];
		for(int i = 0; i < map.length; i++) {
			temp[i] = map[i].clone();
		}
		return temp;
	}
	
	static boolean test(int[][] map) {
		for(int j = 0; j < W; j++) {
			int count = 1;
			int std = map[0][j];
			boolean ok = false;
			for(int i = 1; i < D; i++) {
				int now = map[i][j];
				if(now != std) {
					std = now;
					count = 1;
					continue;
				}
					
				count++;
				if(count == K) {
					ok = true;
					break;
				}
			}
			if(!ok)
				return false;
		}
		
		return true;
	}
}
