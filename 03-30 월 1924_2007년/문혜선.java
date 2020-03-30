/*
 * �˰��� : Calendar�� �̿��Ͽ� ����ð����� ��ü����(getInstance)�� ������ 2007������ ���� ����
 * 			-> ������ ���ڿ��迭�� ���� �ش��ϴ°����� ����Ѵ�
 * �帧 : �Է�, Calendar��ü����  - ��¥���� - �������
 * ������ : Calendar.MONTH�� ���� 0~11�̱� ������ ���� �Է¹����� 1�� ���ش�
 */
import java.util.Calendar;
import java.util.Scanner;
// 15244KB, 124ms, 430B
public class ��Ǯ��_2007��_Calendar {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int x=sc.nextInt(), y=sc.nextInt(); sc.nextLine();//x�� y��
		sc.close();
		
		Calendar cal = Calendar.getInstance();
		cal.set(2007, x -1, y);//month(0~11)�̹Ƿ� 1�� ���ش�** 
		
		//����(1~7)�̹Ƿ� 0���ε������� ��ĭ���� �����
		String dow[] = {"","SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"}; 
		System.out.println(dow[cal.get(Calendar.DAY_OF_WEEK)]);
	}
}