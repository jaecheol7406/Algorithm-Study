/*
	���� : main - dfs
	�˰��� :�ִ��� ��� ���ؼ��� ����츦 ����ؾ��ϹǷ� dfs�̿�, ������� �Ű������� �����Ͽ� ������̵Ǿ����� ���簪�� �������� ���Ѵ�
*/
import java.util.Scanner;

public class ���_��Ǯ�� {
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
