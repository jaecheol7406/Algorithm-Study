/*
 	1�������� �����ؼ� �������� �Ǵ� ���� ã���� �ٷ� while�� Ż���Ѵ� : �ּҰ�
 	while()���� : 1���� �����ϴ� ���� �ڸ������� �����Ͽ� m�� �������� ���ϰ� ���� ������ ���� 1�� �ø��鼭  �ݺ��Ѵ�
*/
import java.util.Scanner;

public class ������_��Ǯ�� {

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