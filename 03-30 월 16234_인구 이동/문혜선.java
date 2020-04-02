/*
함수호출 : main입력 - sol(r,c) - 크기2개이상이면 인구수 조정,2중for문으로 다시 배열A순환
sol(r,c) : DFS를 이용해 방문화는 좌표값을 리스트에 담고 연합국 인구를 누적

알고리즘 : dfs를 이용해 조건만족하는 2개이상 인접행렬들을 이용해 연합국으로 만들고 인구를 갱신 
	 -> 전체순환 한 후에 인구이동일어났으면 결과값+1, 재순환
	
주의점 1 : visited메모초기화는 2중for문  내부X 외부O
		내부 초기화 - 배열A 순회를 끝내기 전에 계속 갱신되므로 최악의경우는 무한루프
		외부 초기화 - A순회가 끝나기 전까지 지나갔던곳은 제외한다
주의점2 : 인구이동 기준
		dfs로 묶이는 그룹마다 인구이동이 일어나는게아니라 A를 모두 순환하고난 뒤 에 그룹묶인게 존재하면 인구이동+1
주의점3 : 2차원배열 순환 2바퀴넘게돌려야한다면 3중 LOOP
*/
import java.awt.Point;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
//210804 KB, 516 ms, 1527 B
public class Main {
	static int N, L, R, ansPopMove=0, sum=0, A[][], compass[][]= {{-1,0},{0,-1},{1,0},{0,1}};
	static List<Point> list;
	static boolean Mm[][];
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N=sc.nextInt(); L=sc.nextInt(); R=sc.nextInt(); sc.nextLine();
		A = new int[N][N];
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) A[i][j]=sc.nextInt();
		sc.close();
		
		list = new LinkedList<>();

		boolean flag;//인구이동이 가능하면 true
		while(true) 
		{
			flag=false;//초기에는 인구이동 불가
			Mm = new boolean[N][N];

			for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
			if( Mm[i][j] ) continue;
			
			list.clear();
			sum=0; 
			
			DFS(i, j);
			
			if(list.size()==1) continue;
			flag=true;
			
			int newPop = sum / list.size();
			while(!list.isEmpty())
				A[list.get(0).x][list.remove(0).y] = newPop;
			}
			
			//2차원A 다 돌고 난 후에 인구이동여부 확인
			if(flag) ansPopMove++;//인구이동이 일어났으면 값+1, 재순환
			if(!flag)break;//탈출
		 }
	 
		System.out.println(ansPopMove);
	}
	static void DFS(int r, int c) {
		if(Mm[r][c])//없으면 갔던곳 계속 간다
			return;
		
		Mm[r][c] = true;
		list.add(new Point(r, c));
		sum += A[r][c];
		
		for(int d=0; d<4; d++) {
			int nr=r+compass[d][0], nc=c+compass[d][1];
			
			if(nr<0 || nc<0 || nr>=N || nc>=N) continue;
			int adjSub = Math.abs(A[r][c] - A[nr][nc]);//다음국가와 인구차 비교를 해서 범위 밖  : 방문X
			if(adjSub<L || adjSub>R) continue;//인구 차이가 L명 이상, R명 이하
			if(Mm[nr][nc]) continue;
			
			DFS(nr, nc);
		}
	}
}