package _2020_04;

import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 14888_연산자 끼워넣기
 * 
 * main() -> solve() -> dfs() -> cal()
 * 
 * 1. opCount에 각 연산자의 개수 저장하고, op에 연산자 저장한다. 
 * 2. 이후, opCount를 이용해 순열로 모든 가짓 수를 dfs로 구해 각 가짓수마다 cal 함수로 연산한다.  
 * 3. 연산할 때마다 최소, 최대값 갱신한다.
 */
public class Main2 {
	static int N;
	static int[] nums;
	static int[] opCount = new int[4];
	static char[] op = {'+', '-', '*', '/'};
	
	static int min = Integer.MAX_VALUE;
	static int max = Integer.MIN_VALUE;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());

		nums = new int[N];
		String[] input = br.readLine().split(" ");
		for(int i = 0; i < N; i++)
			nums[i] = Integer.parseInt(input[i]);

		input = br.readLine().split(" ");
		for(int i = 0; i < 4; i++)
			opCount[i] = Integer.parseInt(input[i]);

		solve();
	}

	static void solve() {
		dfs(opCount.clone(), new int[N - 1], 0);
		System.out.println(max);
		System.out.println(min);
	}

	static void dfs(int[] opCount, int arr[], int idx) {
		if(idx == N - 1) {
			int value = nums[0];
			for(int i = 1; i < N; i++)
				value = cal(value, nums[i], op[arr[i - 1]]);
			
			if(value < min)
				min = value;
			if(value > max)
				max = value;
			
			return;
		}

		for(int i = 0; i < 4; i++) {
			if(opCount[i] > 0) {
				arr[idx] = i;
				opCount[i]--;
				dfs(opCount, arr, idx + 1);
				opCount[i]++;
			}
		}
	}

	static int cal(int a, int b, char op) {
		try {
			switch(op) {
				case '+':
					return a + b;
				case '-':
					return a - b;
				case '*':
					return a * b;
				case '/':
					if(a < 0)
						return -(Math.abs(a) / b);
					return a / b;
				default:
					throw new Exception("잘못");
			}
		} catch (Exception e) {
			System.out.println(e);
			return -1;
		}
	}
}