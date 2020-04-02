import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
/*
 * 17071_숨바꼭질 5 (푸는중ㅇㅇㅇㅇㅇㅇㅇ)
 * main() -> canGo();
 * 
 * t++ 하면서 동생의 모든 t에 대한 좌표 계산(K). 계산한 K에 대해 수빈이가 그 좌표로 갈 수 있는지 계산 후 갈 수 있으면 t 출력 후 끝냄.
 * K 가 500000 넘어갈 때 까지 갈 수 있는 경우가 없으면 -1 출력
 */
public class Main {
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		int N = Integer.parseInt(input[0]);
		int K = Integer.parseInt(input[1]);
		
		int t = 1;
		while(true) {
			K += t;
			if(K > 500000) {
				System.out.println(-1);
				System.exit(0);
			}
			
			System.out.println(K);
			if(canGo(N, K, t))
				break;
			
			t++;
		}
		System.out.println(t);
	}
	
	static boolean canGo(int start, int end, int t) {
		
	}
}