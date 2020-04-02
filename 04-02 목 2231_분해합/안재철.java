import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
/*
 * 2231_분해합
 * main()에서 모두 해결.
 * 자연수 N의 생성자는 N보다 최대 커봤자 9 * 6 적은수?? (6자리라고 했을 때 모두 9일 때가 최대값) 따라서 대략 70정도 뺀 수부터 N - 1 까지 검사하면 된다.
 * N - 1 까지인 이유는 ex) 101이라고 했을 때 생성자는 100이될 수 있다. 생성자는 N보다 크거나 같을 수 없음.
 */
public class Main2 {
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String s = br.readLine();
		int N = Integer.parseInt(s);
		int i = N - 70;
		if(i < 1)
			i = 1;
		for(; i < N; i++) {
			int cons = i;
			int sum = cons;
			while(true) {
				int d = cons % 10;
				sum += d;
				cons = cons / 10;
				if(cons == 0)
					break;
			}
			if(sum == N) {
				System.out.println(i);
				System.exit(0);
			}
		}
		System.out.println(0);
	}
}