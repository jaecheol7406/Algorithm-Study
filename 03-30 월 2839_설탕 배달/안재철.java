import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 2839_설탕 배달
 * main()에서 모두 해결.
 * 
 * 3의 개수(threeNum)을 기준으로, 3의 개수에 따라 채워야하는 남은 킬로그램에 대해 5로 채울 수 있는지 확인 후 채울 수 있으면 총 개수 계산. 
 * ※ 3의 개수 = 0부터 시작해서 3으로만 채웠을 때 남는 개수가 음수가 될때 까지 반복함.
 */
public class Main {
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		int threeNum = 0;
		int count = N / 3 + 2; // 최대 이만큼 이상은 넘어가지 않을 것임.
		while(true) {
			int remain = N - threeNum * 3;
			
			if(remain < 0)
				break;
			
			if(remain % 5 == 0)
				count = Integer.min(count, threeNum + remain / 5);
			
			threeNum++;
		}
		if(count == N / 3 + 2)
			System.out.println(-1);
		else
			System.out.println(count);
	}
}