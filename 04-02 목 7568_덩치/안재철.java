import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 7568_덩치
 * main()
 * 모두 비교해가면서 자기보다 큰 사람의 수 + 1 출력한다.
 */
public class Main2 {
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		int[][] arr = new int[N][2];
		for(int i = 0; i < N; i++) {
			String[] input = br.readLine().split(" ");
			arr[i][0] = Integer.parseInt(input[0]);
			arr[i][1] = Integer.parseInt(input[1]);
		}
		
		for(int i = 0; i < N; i++) {
			int rank = 1;
			for(int j = 0; j < N; j++) {
				if(j == i)
					continue;
				
				if(arr[j][0] > arr[i][0] && arr[j][1] > arr[i][1])
					rank++;
			}
			System.out.print(rank + " ");
		}
	}
}