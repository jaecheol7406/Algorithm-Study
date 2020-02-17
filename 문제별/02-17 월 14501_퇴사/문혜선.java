//14364 KB, 108 ms, 651 B
import java.util.Scanner;

public class 퇴사_내풀이 {
	static int N, maxProfit=-1;
	static int[] T, P;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt(); sc.nextLine();
		T = new int[N+1]; 
		P = new int[N+1];
		for(int i=1; i<N+1; i++) {
			T[i] = sc.nextInt(); P[i] = sc.nextInt(); sc.nextLine();
		}
		sc.close();
		dfs(1, 0);
		System.out.println(maxProfit);
	}
	static void dfs(int i, int sum) {
		if (i > N) {
			if (maxProfit < sum)
				maxProfit = sum;
			return;
		}

		dfs(i+1, sum);
		if (i + T[i] <=N+1)
			dfs(i + T[i], sum + P[i]);
		return;
	}

}
