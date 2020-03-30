/*	
  ����: main�Է� -> sol����Լ� ->���
  �Լ� 
  sol(�Է°�, ����, �޸�) : �Է°�N���� -5, -3�� �ذ��鼭 0���� �� �������� ��Ȯ�ϰ�NŰ�ΰ� ��޵ȴ� 
  					   	�� �� ������ cnt�� ��ȯ�Ѵ�. �׷��������� �ִ��� 2000 ��ȯ
  
  ����츦 �������ؼ� ����Լ��� �̿��ߴ� -> ����:��θ��� -> ä��:�ð��ʰ�����(1��)-> �޸��̿��ؼ� �ߺ�ȣ�⸷��

 */
import java.util.Scanner;
//14428KB, 104ms, 548B - Scanner
//13128KB, 72ms, 775B - BufferedReader
public class �������_��Ǯ�� {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		sc.close();
		int ansMin = sol(N, 0, new int[5000]);//����ϴ� ������ �ּ� ����
		System.out.println(ansMin !=2000 ? ansMin : -1);
	}
	static int sol(int n, int cnt, int[] memo) {
		if(n==0) 
			return cnt;
		if(memo[n-1] != 2000 && memo[n-1] != 0) return memo[n-1];
//		if(memo[n-1] != 0) return memo[n-1];
		
		int v1=2000, v2=2000;//�����ִ밳��
		if(n-5>=0)
			v1= sol(n-5, cnt+1, memo);
		if(n-3>=0)
			v2= sol(n-3, cnt+1, memo);
		
		return memo[n-1] = v1<v2?v1:v2;//�ּҰ��� ���Ѵ��� �޸� ������ �� �� ���� ��ȯ
	}

}
