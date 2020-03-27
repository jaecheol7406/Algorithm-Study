import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 10871_X보다 작은 수
 * main()
 * 그대로 구현
 */
public class Main {
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		int N = Integer.parseInt(input[0]);
		int X = Integer.parseInt(input[1]);
		
		input = br.readLine().split(" ");
		for(int i = 0; i < N; i++) {
			int n = Integer.parseInt(input[i]);
			if(n < X)
				System.out.print(n + " ");
		}
	}
}