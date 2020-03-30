/*	
  순서: main입력 -> sol재귀함수 ->출력
  함수 
  sol(입력값, 봉지, 메모) : 입력값N에서 -5, -3을 해가면서 0으로 딱 떨어지면 정확하게N키로가 배달된다 
  					   	이 때 봉지수 cnt를 반환한다. 그렇지않으면 최댓값인 2000 반환
  
  모든경우를 따져야해서 재귀함수를 이용했다 -> 테케:모두맞음 -> 채점:시간초과실패(1초)-> 메모이용해서 중복호출막음

 */
import java.util.Scanner;
//14428KB, 104ms, 548B - Scanner
//13128KB, 72ms, 775B - BufferedReader
public class 설탕배달_내풀이 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		sc.close();
		int ansMin = sol(N, 0, new int[5000]);//배달하는 봉지의 최소 개수
		System.out.println(ansMin !=2000 ? ansMin : -1);
	}
	static int sol(int n, int cnt, int[] memo) {
		if(n==0) 
			return cnt;
		if(memo[n-1] != 2000 && memo[n-1] != 0) return memo[n-1];
//		if(memo[n-1] != 0) return memo[n-1];
		
		int v1=2000, v2=2000;//봉지최대개수
		if(n-5>=0)
			v1= sol(n-5, cnt+1, memo);
		if(n-3>=0)
			v2= sol(n-3, cnt+1, memo);
		
		return memo[n-1] = v1<v2?v1:v2;//최소값을 구한다음 메모에 저장한 후 그 값을 반환
	}

}
