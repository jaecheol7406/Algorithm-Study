import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 17071_숨바꼭질 5 (틀렸습니다)
 * main() -> catching() -> dfs()
 * 
 * T++ 하면서 동생의 모든 T에 대한 좌표 계산(K). 계산한 K에 대해 수빈이가 그 좌표로 갈 수 있는지 계산 후 갈 수 있으면 T 출력 후 끝냄.
 * K 가 500000 넘어갈 때 까지 갈 수 있는 경우가 없으면 -1 출력
 */
public class Main {	
	static int T = 1;
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		int N = Integer.parseInt(input[0]);
		int K = Integer.parseInt(input[1]);
		
		while(true) {
			K += T;
			if(K > 500000)
				break;
			
			catching(N, K);
			
			T++;
		}
		System.out.println(-1);
	}
	
	static void catching(int start, int target) {
		dfs(start, target, 0);
	}
	
	static void dfs(int now, int target, int t) {
		if(t == T) {
			if(now == target) {
				System.out.println(t);
				System.exit(0);
			}
			return;
		}
		
		if(now < target) {
			dfs(now + 1, target, t + 1);
			dfs(now * 2, target, t + 1);
		} else {
			dfs(now - 1, target, t + 1);
		}
	}
}