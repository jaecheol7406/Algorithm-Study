//15924 KB, 164 ms, 1448 B
import java.util.ArrayList;
import java.util.Scanner;
/*
 * 뱀이 위치하는곳을 Arraylist에   좌표를 추가하여 snakePos큐
 * 			뱀의 길이, 현재위치, 좌표 추가삭제 for-each검색
 * 
 * 오래걸린부분 
 * 1) 숫자 + 영어문자 한줄에 입력받을때 문자처리부분 next()로는 char입력이 안됨
 *  		  String으로받고 charAt(0)
 * 2) 배열값으로 for문판별조건 만들때 : i값도 같이 주는거 빼먹어서 인덱스오류
 */

public class Main {
	static int N, K, L, A[][], ansSec=1, compass[][] ={{0,1}, {1,0}, {0,-1}, {-1,0}};
	static ArrayList<P> snakePos = new ArrayList<>();
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N =sc.nextInt(); sc.nextLine(); K =sc.nextInt(); sc.nextLine();
		A = new int[N][N];
		for(int i=0; i<K; i++) 
			A[sc.nextInt() -1][sc.nextInt() -1] = 5;
		L = sc.nextInt(); sc.nextLine();
		int[][] changeDir = new int[L][2];
		for(int i=0; i<L; i++) {
			changeDir[i][0] = sc.nextInt(); 
			char c = sc.next().charAt(0); sc.nextLine();
			if(c == 'D') changeDir[i][1]=1; else changeDir[i][1]=-1;
			
		}
		sc.close();
		int dir=0, r=0, c=0;
		
		snakePos.add(new P(0,0));
		loop :
		while(true) {
			int nr =r+compass[dir][0], nc = c+compass[dir][1];
//			종료조건 : 벽과 만나거나 자신과 부딛힘
			if(nr<0 || nr>=N || nc<0 || nc>=N) break;
			for(P p : snakePos) 
				if(nr==p.r && nc==p.c) 
					break loop;
			
//			사과먹으면서 위치이동
			snakePos.add(new P(nr,nc));//새로운 위치이
			if(A[nr][nc] == 5) //사과값 5
				A[nr][nc] =0;//1칸에 사과가 1개가 있다고 가정하므로 사과먹은후의 값은 0
			else 
				snakePos.remove(0);//사과를 안먹은경우만 위치이동하면서 첫항제거
			
//			x초가 되면 방향 바꾸기
			int i=0;
			for(; i<L && changeDir[i][0] <= ansSec; i++) {//핀별조건이 배열값일때 유의
				if(changeDir[i][0] != ansSec) continue;
				
				int nDir = (dir + changeDir[i][1]) % 4;
				if(nDir == -1) nDir=3;
				dir = nDir;
			}
//			다음 loop을 위해 기존의값을 새로운값으로 바꾸기
			r=nr; c=nc; 
			
			ansSec++;
		}
		System.out.println(ansSec);
	}
	static class P{
		int r, c;
		public P(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}
}