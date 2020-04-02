/*
함수호출 : main - bfs(수빈위치,동생위치) - isRange(수빈위치, 동생위치)
알고리즘 : 수빈이 이동하는 경우의 수는 3가지, 동생은 1가지 총 3가지의 경우의 수가 나온다 
		이동할 좌표가 범위에 맞는지 확인(isRange)한 후 큐에 넣기

실패

*/
import java.awt.Point;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class 숨바꼭질5_내풀이 {
	static int ansSec=0;
	static boolean visited[] = new boolean[500001];
	static Queue<Point> Q = new LinkedList<>();
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int posS=sc.nextInt(), posD=sc.nextInt();
		sc.close();
		
		//배열로 입력?
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
