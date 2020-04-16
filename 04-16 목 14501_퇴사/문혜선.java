/*
	순서 : main - dfs
	알고리즘 :최댓값을 얻기 위해서는 모든경우를 고려해야하므로 dfs이용, 결과값을 매개변수에 저장하여 퇴사일이되었을때 현재값과 기존값을 비교한다
*/
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
