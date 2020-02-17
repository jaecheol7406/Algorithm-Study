//14248 KB, 120 ms, 435 B
import java.util.Scanner;

public class 분해합_내풀이 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int num = sc.nextInt();
		sc.close();
		
		int subNum = 1;
		while (subNum <= num) {
			int n = subNum, sum = subNum;
			while (n > 0) {
				sum += (n % 10);
				n /= 10;
			}
			if (sum == num) {
				System.out.println(subNum);
				break;
			}
			subNum++;
		}
		if(subNum>num) System.out.println(0);
	}
}

//216 -> 198
//10 -> 5
