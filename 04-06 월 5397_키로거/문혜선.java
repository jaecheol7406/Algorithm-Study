/*
호출순서 : main
알고리즘  : 문자 1개씩 삽입, 삭제, 교체가 일어나므로 스택사용 스택안에는 오직 문자나 숫자만 들어간다 (부호x)
left : 최종 룰력될 곳으로 처리된 -,>,<가 아닌경우 이쪽에 바로 push한다.
		>가 입력되는 경우 왼쪽의 스택탑을 right으로 옮긴다
right : <가 입력되는경우 앞부분에 문자가 있으면 자리르 바꾸어야 해서 left의 스택탑을 right로 옮긴다

시간초과
*/
import java.util.Scanner;
import java.util.Stack;

public class 키로거_내풀이 {

	public static void main(String[] args) {
		Stack<Character> left, right;

		Scanner sc = new Scanner(System.in);
		int num = sc.nextInt();
		sc.nextLine();
		while (num-- > 0) {
			char[] arc = sc.nextLine().toCharArray();
			left = new Stack<>();
			right = new Stack<>();

			for (Character c : arc) 
			{
				switch (c) {
				case '-':
					if (!left.isEmpty())
						left.pop();
					break;
				case '>':
					if (!right.isEmpty())
						left.push(right.pop());
					break;
				case '<':
					if (!left.isEmpty())
						right.push(left.pop());
					break;
				default:
					left.push(c);//일반문자나 숫자가 들어오는 경우에는 결과스택인 left에 넣기
				}
			}
//				System.out.println(left.toString() + right.toString());
			for(Character ch : left)
				System.out.print(ch);
			System.out.println();
		}
		sc.close();

	}
}
