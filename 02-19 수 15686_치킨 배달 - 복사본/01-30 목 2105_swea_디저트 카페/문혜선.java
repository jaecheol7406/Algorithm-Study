//1. 값을 index로 두어 boolean형 중복확인배열(해설)
//2. ArrayList를 이용한 중복처리(내방법)
import java.util.ArrayList;
import java.util.Scanner;

public class Main_0123_2105_swea_디저트카페 {
	static int [][] map, M, compass={ {-1,1}, {1,1}, {1,-1}, {-1,-1}};//북동, 남동, 서남, 서북 - clockwise
	static int N, resultMax;
	static ArrayList<Integer> deserts = new ArrayList<>();
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
//		int testcase=sc.nextInt(); sc.nextLine();
//		for(int t=0; t<testcase; t++)
			for(int t=0; t<1; t++)
		{
			resultMax=-1;
			System.out.println(1);
			N = sc.nextInt(); sc.nextLine();
			map = new int[N][N];
			for(int i=0; i<N; i++)
				for(int j=0; j<N; j++)
					map[i][j] = sc.nextInt();
			
			for(int i=0; i<N-2; i++)
				for(int j=0; j<N-1 ; j++) 
				{
					for(int dd=0; dd<4; dd++) {
						int ni = i + compass[dd][0], nj = j + compass[dd][1];
						if(ni<0 || nj<0 || ni>=N || nj>=N) continue;
						
						M = new int[N][N];//출발점은 메모표시안함
						deserts.clear();
						deserts.add(map[i][j]);//
						makeSquare(i, j, ni, nj, dd);
					}
				}
		System.out.println(resultMax);
		}
		sc.close();
	} 
	static void makeSquare(int sr, int sc, int r, int c, int dir) {
		if(sr==r && sc==c) {
			int endSize = deserts.size();
			resultMax = Math.max(endSize, resultMax);
			return;
		}
		deserts.contains(map[r][c]);
//		for(int d : deserts) 
//			if(d == map[r][c]) return;
		
		//검사통과
		M[r][c] = 1;
		deserts.add(map[r][c]);
		
		//다음이동
		for(int cnt=0; cnt<2; cnt++) {
			int newDir = (dir+cnt)%4;
			int nr = r+compass[newDir][0], nc = c+compass[newDir][1];
			if(nr<0 || nc<0 || nr>=N || nc>=N) continue;
			if( map[nr][nc]==1) continue;
			
			makeSquare(sr, sc, nr, nc, newDir);
		}
		M[r][c]=0;
		deserts.remove(deserts.size()-1);

		return;
	}

}
