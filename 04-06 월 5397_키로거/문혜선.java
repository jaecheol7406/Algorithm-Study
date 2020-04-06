/*
ȣ����� : main
�˰���  : ���� 1���� ����, ����, ��ü�� �Ͼ�Ƿ� ���û�� ���þȿ��� ���� ���ڳ� ���ڸ� ���� (��ȣx)
left : ���� ��µ� ������ ó���� -,>,<�� �ƴѰ�� ���ʿ� �ٷ� push�Ѵ�.
		>�� �ԷµǴ� ��� ������ ����ž�� right���� �ű��
right : <�� �ԷµǴ°�� �պκп� ���ڰ� ������ �ڸ��� �ٲپ�� �ؼ� left�� ����ž�� right�� �ű��

�ð��ʰ�
*/
import java.util.Scanner;
import java.util.Stack;

public class Ű�ΰ�_��Ǯ�� {

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
					left.push(c);//�Ϲݹ��ڳ� ���ڰ� ������ ��쿡�� ��������� left�� �ֱ�
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
