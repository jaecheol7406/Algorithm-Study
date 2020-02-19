import java.util.ArrayList;
import java.util.Scanner;
/*
 * 1107_리모컨
 */
public class Main {
	static int N, M;
	static int channel = 100;
	static boolean[] unusables = new boolean[10];
	static ArrayList<Integer> usables = new ArrayList<>(); // 사용 가능한 숫자
	static int result;
	
	public static void main(String[] args) {
		input();
		solve();
		System.out.println(result);
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		for(int i = 0; i < M; i++)
			unusables[sc.nextInt()] = true;
		for(int i = 0; i < 10; i++) {
			if(!unusables[i])
				usables.add(i);
		}
		
		sc.close();
	}
	
	static void solve() {
		int distance = Math.abs(channel - N);
		result = distance; // 현재 채널(100)에서  + or - 만 눌러서 가는 경우가 제일 빠를 수 있음
		
		// 무조건 +, -로 가는게 최소인 경우 (98 ~ 103 사이거나 버튼이 모두 고장) : distance가 최소
		if(98 <= N && N <= 103 || usables.isEmpty())
			return;
				
		// 목표 채널의 자리수
		int digit = String.valueOf(N).length();
		
		comb(new int[digit], 0, digit); // 누를 수 있는 버튼으로 목표채널 자리수만큼 중복조합
		comb(new int[digit + 1], 0, digit + 1); // 목표채널의 자리수 + 1의 모든 숫자에 대해 검사 ex) 99일 때는 2자리 수보다 3자리 수가 더 가까울 수 있음
		if(digit != 1) // 1자리 제외 목표채널의 자릿수 - 1의 모든 숫자 검사
			comb(new int[digit + 1], 0, digit - 1);
	}
	
	static void comb(int[] re, int idx, int r) {
		if(idx == r) {
			String num = "";
			for(int i = 0; i < r; i++) {
				num += usables.get(re[i]);
			}
			int n = Integer.parseInt(num);
			int clickCount = r + Math.abs(N - n); // 목표 채널로 가기 위한 버튼 클릭수 (r의 자릿수 + +or- 횟수)
			result = Integer.min(result, clickCount); // 최솟값
			
			return;
		}
		
		for(int i = 0; i < usables.size(); i++) {
			if(r != 1 && idx == 0 && usables.get(i) == 0) // 1자리수가 아닌 숫자 중 첫 숫자이고 그 숫자가 0이면 숫자 만들 수 없음 ex) 01, 044
				continue;
			
			re[idx] = i;
			comb(re, idx + 1, r);
		}
	}
}