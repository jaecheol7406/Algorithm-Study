/*
	순서 : main - DFS():배열을6번방문해서 숫자만들기
	
	HashSet을 쓰면 다 빠르다
	조건이간단해서 방향을 배열로안주고 (x+1,y)식으로 함수4개만드는게 간단
	
	**2중 for문으로 DFS를 안돌리면 중복허용이라 (0,0)에서 빠져나가질 못한다**
	
	주의점
	1. 중복허용 - 메모사용하지않는다
	2. 0으로시작하는 숫자가능 (Stringd이나 Integer나 상관없음)
*/
import java.util.ArrayList;
import java.util.Scanner;
//17996KB, 328ms, 859B
public class 숫자판점프_내풀이 {
	static int[][] A = new int[5][5], compass = {{-1,0}, {0,-1}, {1,0}, {0,1}};
	static boolean[][] visited = new boolean[5][5];
	static ArrayList<Integer> list = new ArrayList<>();
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		for(int i=0; i<5; i++) for(int j=0; j<5; j++) A[i][j]=sc.nextInt();
		sc.close();

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				DFS(i, j, 6, 0);// == DFS(i, j, 5, A[i][j])
		
		System.out.println(list.size());
	}
	static void DFS(int r, int c, int k, int num) {
		if (k == 0) {// r==5 && c==5){
			if (!list.contains(num))//중복(contains)되지않는다면 새로추가
				list.add(num);
			return;
		}
		for(int d=0; d<4; d++) {
			int nr=r+compass[d][0], nc=c+compass[d][1];
			if(nr<0||nc<0||nr>4||nc>4) continue;
			
			DFS(nr, nc, k - 1, 10*num + A[r][c]);
		}
	}
}
