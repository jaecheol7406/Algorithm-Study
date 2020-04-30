/*
	순서 : main 입력 - 파이프번호,방문배열 큐2개생성 - L초가 되기전가지 영억의 개수 세기
	알고리즘
	 1)방향 for문을 수행하면서 기준파이브가 갈수없는 방향 제외, 범위중복0값 제외, (r,c)와(nr,nc)값의 파이프가 서로연결되어있는지 체크 한다음에 큐에추가
	 2) 큐1개로 하면 시간대별로 분리가 어려우므로 Q1에는 이번초의 좌표값, Q2에는 새로추가되는 좌표값 추가
	 3) Q1가 비면  해당초가 끝나므로 Q2값을 덮어씌우고 Q2초기화
*/
import java.awt.Point;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class 탈주범검거_내풀이 {
	static final int compass[][] = {{-1,0},{0,1}, {1,0}, {0,-1}}; //북동남서
	//북동남서 순서 기존파이프기준방향계산과 두 파이브가 연결되어있는지 여부확인
	static final int pipeOpened[][] = { {},{1,1,1,1},{1,0,1,0}, {0,1,0,1}, {1,1,0,0},{0,1,1,0},{0,0,1,1},{1,0,0,1}};
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int testCase=sc.nextInt(); sc.nextLine();
		for(int tc=1; tc<=testCase; tc++) {
			int N=sc.nextInt(), M=sc.nextInt(), R=sc.nextInt(), C=sc.nextInt(), L=sc.nextInt(); sc.nextLine();
			int map[][] = new int[N][M];
			for(int i=0; i<N; i++) for(int j=0; j<M; j++) map[i][j]=sc.nextInt();
			
			int ansCnt=1, time=1;
			Queue<Point> Q1 = new LinkedList<>(), Q2 = new LinkedList<>();
			boolean visited[][] = new boolean[N][M];
			Q1.add(new Point(R,C));
			visited[R][C] = true;
			while(time < L)
			{
				while(! Q1.isEmpty()) {
				int r=Q1.peek().x, c=Q1.remove().y;
				
				for(int d=0; d<4; d++) {
					if( pipeOpened[ map[r][c] ][d] ==0) continue;//안가는 방향 제외
					
					int nr=r+compass[d][0], nc=c+compass[d][1];
					if(nr<0||nc<0||nr>=N||nc>=M) continue;
					if(visited[nr][nc]) continue;//4방향 돌리면서 기존파이프 중복제외
					if(map[nr][nc] ==0) continue;//파이프없는 부분 제외
					if(pipeOpened[ map[nr][nc] ][ (d+2)%4 ] == 0) continue;//파이프가있더라도 상호연결 안되면 제외
					
					ansCnt++;
					visited[nr][nc] = true;;
					Q2.add(new Point(nr, nc));//다음회차에 사용할 큐는 2번에 담기
					
				}
				}
				Q1.addAll(Q2);
				Q2.clear();
				time++;
			}
			
			System.out.println("#"+tc+ " " + ansCnt);
		}
		sc.close();
		
	}
}
