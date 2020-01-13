import java.util.Scanner;
/* 1065_한수
 문제
어떤 양의 정수 X의 자리수가 등차수열을 이룬다면, 그 수를 한수라고 한다. 등차수열은 연속된 두 개의 수의 차이가 일정한 수열을 말한다. N이 주어졌을 때, 1보다 크거나 같고, N보다 작거나 같은 한수의 개수를 출력하는 프로그램을 작성하시오. 

입력
첫째 줄에 1,000보다 작거나 같은 자연수 N이 주어진다.

출력
첫째 줄에 1보다 크거나 같고, N보다 작거나 같은 한수의 개수를 출력한다.

예제 입력 1 
110
예제 출력 1 
99
예제 입력 2 
1
예제 출력 2 
1
예제 입력 3 
210
예제 출력 3 
105
예제 입력 4 
1000
예제 출력 4 
144
 */
public class Main {
	static int N;
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		System.out.println(calcHansuNum());
		sc.close();
	}
	
	static int calcHansuNum(){
		int hansuNum = 0;
//		if(N <= 99)
		for(int num = 1; num <= N; num++) {
			if(isHansu(num))
				hansuNum++;
		}
		return hansuNum;
	}
	
	static boolean isHansu(int num) {
		String s = String.valueOf(num);
		int[] arr = new int[s.length()];
		for(int i = 0; i < s.length(); i++)
			arr[i] = s.charAt(i);
		int first = arr[0];
		int prevdiff = 0;		
		for(int i = 1; i < s.length(); i++) {
			int nowdiff = arr[i] - arr[i - 1];
			if(i == 1) {
				prevdiff = nowdiff;
				continue;
			}
			if(prevdiff != nowdiff)
				return false;
			prevdiff = nowdiff;
		}
		return true;
	}
}