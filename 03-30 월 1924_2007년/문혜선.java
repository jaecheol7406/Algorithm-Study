/*
 * 알고리즘 : Calendar을 이용하여 현재시간으로 객체생성(getInstance)한 다음에 2007년으로 값을 세팅
 * 			-> 요일을 문자열배열로 만들어서 해당하는값으로 출력한다
 * 흐름 : 입력, Calendar객체생성  - 날짜설정 - 요일출력
 * 주의점 : Calendar.MONTH는 값이 0~11이기 때문에 값을 입력받을때 1을 빼준다
 */
import java.util.Calendar;
import java.util.Scanner;
// 15244KB, 124ms, 430B
public class 내풀이_2007년_Calendar {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int x=sc.nextInt(), y=sc.nextInt(); sc.nextLine();//x월 y일
		sc.close();
		
		Calendar cal = Calendar.getInstance();
		cal.set(2007, x -1, y);//month(0~11)이므로 1을 빼준다** 
		
		//요일(1~7)이므로 0번인덱스에는 빈칸으로 남긴다
		String dow[] = {"","SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"}; 
		System.out.println(dow[cal.get(Calendar.DAY_OF_WEEK)]);
	}
}