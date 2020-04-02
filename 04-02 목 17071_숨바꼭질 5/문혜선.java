/*
�Լ�ȣ�� : main - bfs(������ġ,������ġ) - isRange(������ġ, ������ġ)
�˰��� : ������ �̵��ϴ� ����� ���� 3����, ������ 1���� �� 3������ ����� ���� ���´� 
		�̵��� ��ǥ�� ������ �´��� Ȯ��(isRange)�� �� ť�� �ֱ�

����

*/
import java.awt.Point;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class ���ٲ���5_��Ǯ�� {
	static int ansSec=0;
	static boolean visited[] = new boolean[500001];
	static Queue<Point> Q = new LinkedList<>();
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int posS=sc.nextInt(), posD=sc.nextInt();
		sc.close();
		
		//�迭�� �Է�?
		bfs(posS, posD);
		
		System.out.println(ansSec > 1499900 ? -1 : ansSec);
	}
	static void bfs(int ps, int pd) {
		if(! isRange(ps,pd))
			return;
		if(ps == pd)
			return;

		Q.add(new Point(ps, pd));
		
		while(! Q.isEmpty()) {
			
			int s=Q.peek().x, d=Q.poll().y;
			
			if(pd > 500000) break;
			if(s==d) return;
			
			++ansSec;
			if(isRange(ps*2, pd+ansSec))
				Q.add(new Point(ps * 2, pd+ansSec));
			if(isRange(ps+1, pd+ansSec))
				Q.add(new Point(ps + 1, pd+ansSec));
			if(isRange(ps-1, pd+ansSec))
				Q.add(new Point(ps - 1, pd+ansSec));
			
		}
		
		
		
	}
	static boolean isRange(int ps, int pd) {
		if(ps<0 || pd<0 || ps>500000 || pd>500000)
			return false;
		return true;
	}

}
