//https://www.acmicpc.net/problem/1065
import java.util.Scanner;

public class Main_1065_Sequence {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), result=0;
		sc.close();
		
		if(n<=99) result = n;
		else 
		{
			result = 99;
			if(n == 1000) n=999;
//			(1) n까지 while이용 - 메모리 14284KB, 시간 112ms, 코드길이 454B
			int num = 110;
			while(num <= n) {
				int a = num / 100;
				int b = num%100 / 10;
				int c = num%100 % 10;
				
				int d = a-b;
				if(b-c == d)
					result++;
				
				num++;
			}
			
//			(2) 자리수 분리해서 배열에 대입 - 나머지값을 배열에 하나씩 대입한다 
//			메모리 14288KB, 시간 104ms, 코드길이 699B
			int loopN = n;
			int[] D = new int[3];
			for(int i=0; i<D.length; i++){
				D[D.length -i -1] = loopN % 10;
				loopN /= 10;
			}
			
			int bb=9, cc=9;
			for(int a=1; a <= D[0]; a++) {
				bb = (a == D[0]) ? D[1] : 9; 
				for(int b=0; b <= bb; b++) 
				{
					int d = a - b;
					cc = (a == D[0] && b == D[1]) ? D[2] : 9;
					if(b-d >= 0 && b-d <= cc) //b-c=d -> c=b-d
						result++;
				}
			}
//			(3) 계산가능한 공차 0~4 - (2)에다가 공차범위를 위해 -4 : 4범위의 for문을 더 감싸야한다
		}//else끝
		System.out.println(result);
		}
	}


