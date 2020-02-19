import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;
/* 
 * 5658. [모의 SW 역량테스트] 보물상자 비밀번호
 */
public class Solution {
	static int T;
	static int N, K;
	static String nums;
	static int sideDigitNum;
	static int result;
	
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		
		T = sc.nextInt();
		
		for(int t = 1; t <= T; t++) {
			N = sc.nextInt();
			K = sc.nextInt();
			nums = sc.next();
			sideDigitNum = N / 4;
			solve();
			print(t);
		}
		
		sc.close();
	}
	
	static void solve() {
		ArrayList<String> list = new ArrayList<>();
		for(int i = 0; i < sideDigitNum; i++) {
			rotate();
			getNum(list);
		}
		
		Collections.sort(list, new Comparator<String>() {

			@Override
			public int compare(String o1, String o2) {
				if(Integer.valueOf(o1, 16) > Integer.valueOf(o2, 16))
					return -1;
				else if(Integer.valueOf(o1, 16) < Integer.valueOf(o2, 16))
					return 1;
				else
					return 0;
			}
		});
		
		result = Integer.valueOf(list.get(K - 1), 16);
	}
	
	static void rotate() {
		nums = nums.charAt(nums.length() - 1) + nums.substring(0, nums.length() - 1);
	}
	
	static void getNum(ArrayList<String> list) {
		for(int i = 0; i < nums.length(); i += sideDigitNum) {
			String num = nums.substring(i, i + sideDigitNum);
			if(!list.contains(num))
				list.add(num);
		}
	}
	
	static void print(int t) {
		System.out.println("#" + t + " " + result);
	}
}