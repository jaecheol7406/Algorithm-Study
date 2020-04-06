/*
 	1에서부터 시작해서 분해합이 되는 수를 찾으면 바로 while을 탈출한다 : 최소값
 	while()내부 : 1부터 시작하는 값을 자리수별로 분해하여 m에 누적합을 구하고 같지 않으면 값을 1씩 늘리면서  반복한다
*/
import java.util.Scanner;

public class 분해합_내풀이 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt(); sc.close();
		
		int num=1;
		while(num<N) {
			int dv=num, m=num;
			while(dv>0) {
				m += dv%10;
				dv /= 10;
			}
			if(m == N) {
				System.out.println(num);
				break;
			}
			num++;
		}
		if(num == N) System.out.println(0);
	}
}