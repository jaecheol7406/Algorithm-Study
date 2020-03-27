import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
/*
 * 1924_2007년
 * main()에서 모두 해결.
 * 
 * data : 배열에 월마다 일수, 요일을 저장해놓음.
 * 알고리즘 : 
 * 1. 1월부터 시작하여  목표 달(x)의 전 달까지 배열에 저장해놓은 일수 더함.
 * 2. 마지막 달은 (목표 일수(y) - 1) 더함. (1일부터이기 때문에 1을 뺌)
 * 3. 7을 나눈 나머지로 요일 환산. 
 */
public class Main3 {
	static int[] dayNum = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	static String[] day = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int x = Integer.parseInt(st.nextToken());
		int y = Integer.parseInt(st.nextToken());
		
		int totalDay = 0;
		for(int month = 1; month < x; month++) {
			totalDay += dayNum[month];
		}
		
		totalDay +=	(y - 1);
		System.out.println(day[totalDay % 7]);
	}
}