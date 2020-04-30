/*실패
	순서 : main - check_Drop() - mark_Drop() -  bomb()
	check_Drop() : 전부 아래로 떨어졌는지 확인
	mark_Drop() : 재귀함수를 이용해 바닥과 연결된 뿌요들을 true로 표시
	bomb() : 한번 터지고 중력을받아 밑으로 내려온다
	
	알고리즘
	1) 배열에서 dfs를 이용하여 연결된뿌요를 모두 표시하고 2충for문으로 검색하여 연결안된 뿌요가 나온다면 false
	2) true인경우에는 해당뿌요를 제외하고 나머지부분은 뿌요나 바닥이 보일때까지 밑으로 이동

*/
import java.util.Scanner;

public class Puyo_내풀이 {
	static char[][] A = new char[12][6];
	static int[][] compass= {{-1,0}, {0,1}, {1,0}, {0,-1}};//북동남서
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		for(int i=0; i<12; i++) A[i] = sc.nextLine().toCharArray();
		sc.close();
		
		int ans=0;
		while(check_Drop()) {
			bomb();
			ans++;
		}
		System.out.println(ans);
	}
	static boolean visited[][];
	static void mark_Drop(int r, int c) {
		if(visited[r][c])
			return;
		
		visited[r][c]= true;
		
		for(int d=0; d<4; d++) {
			int nr=r+compass[d][0], nc=c+compass[d][1];
			if(nr<0||nc<0||nr>=12||nc>=6) continue;
			if(visited[nr][nc]) continue;
			
			mark_Drop(nr, nc);
			
		}
		
	}
	static boolean check_Drop() {
		visited = new boolean[12][6];
		mark_Drop(11,0);
		boolean flag=false;
		int Mm[][] = new int[12][6];
		for(int i=0; i<12; i++) for(int j=0; j<6; j++) {
			if(A[i][j]=='.') continue;
			
			
		}
		
		return flag==true ? true : false;
	}
	static void bomb() {
		//하다가 실패
	}

}
