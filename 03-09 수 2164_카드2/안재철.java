import java.util.Deque;
import java.util.LinkedList;
import java.util.Scanner;
/*
 * 2164_카드2
 * 
 * deque로 1~N 숫자 넣어놓고 while문으로 크기가 1일때 까지 앞뒤에서 삭제, 삽입함
 */
public class Main {
	static int N;
	
	public static void main(String[] args) {
		input();
		solve();
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		sc.close();
	}
	
	static void solve() {
		Deque<Integer> dq = new LinkedList<>();
		for(int i = 1; i <= N; i++)
			dq.add(i);
		
		while(dq.size() != 1) {
			dq.removeFirst();
			if(dq.size() == 1)
				break;
			dq.addLast(dq.removeFirst());
		}
		
		System.out.println(dq.getFirst());
	}
}