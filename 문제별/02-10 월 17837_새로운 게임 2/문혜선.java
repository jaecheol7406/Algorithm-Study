// 17428 KB KB, 160 ms, 2681 B
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Main {
	static int N, K, ansTurn=1;
	static int[][] compass= {{0,0}, {0,1}, {0,-1}, {-1,0}, {1,0}}, colorMap;
	static Horse[] horses;
	static ArrayList<Integer>[][] chessMap;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt(); K =sc.nextInt(); sc.nextLine();
		colorMap = new int[N][N];
		for(int i=0; i<N; i++)	for(int j=0; j<N; j++) colorMap[i][j] = sc.nextInt();
		horses = new Horse[K];
		for(int i=0; i<K; i++) {
			horses[i] = new Horse( sc.nextInt()-1, sc.nextInt()-1, sc.nextInt() ); 
			sc.nextLine();
		}
		sc.close();
		
		chessMap = new ArrayList[N][N];
		for(int i=0; i<N; i++)	for(int j=0; j<N; j++) chessMap[i][j] = new ArrayList<Integer>();
		for(int ii=0; ii<horses.length; ii++)
			chessMap[horses[ii].i][horses[ii].j].add(ii);
		
		while(! solution()) ansTurn++;
		System.out.println(ansTurn >= 1000 ? -1 : ansTurn);
	}
	static boolean solution() {
		if(ansTurn >= 1000) return true;
		for(int hh=0; hh<K; hh++)
		{
			Horse h = horses[hh];
			int nowHorse = chessMap[h.i][h.j].indexOf(hh);
			ArrayList<Integer> subHorses = new ArrayList<>();
			for(int i=nowHorse; i<chessMap[h.i][h.j].size(); i++)
				subHorses.add(chessMap[h.i][h.j].get(i));//add(i);
			for(Integer sh : subHorses)	chessMap[h.i][h.j].remove(sh);
			
			int ni = h.i + compass[h.dir][0], nj = h.j + compass[h.dir][1];
			if(ni<0 || ni>=N || nj<0 || nj>=N || colorMap[ni][nj] ==2) 
			{
				h.dir = (h.dir%2 ==0) ? h.dir-1  : h.dir+1;
				int mi = h.i + compass[h.dir][0], mj = h.j + compass[h.dir][1];
				
				if(mi<0 || mi>=N || mj<0 || mj>=N || colorMap[mi][mj]==2) {
					chessMap[h.i][h.j].addAll(subHorses);
					continue;
				}
				if(colorMap[mi][mj] == 1) Collections.reverse(subHorses);
				chessMap[mi][mj].addAll(subHorses);
				for(Integer sh : subHorses) {
					horses[sh].i = mi;
					horses[sh].j = mj;
				}
				if(chessMap[mi][mj].size() >= 4) return true;
				continue;
			}
			
			switch(colorMap[ni][nj]) {
			case 0://흰색
				chessMap[ni][nj].addAll(subHorses);
				for(Integer sh : subHorses) {
					horses[sh].i = ni;
					horses[sh].j = nj;
				}
				if(chessMap[ni][nj].size() >= 4) return true;
				break;
			case 1: //빨강
				Collections.reverse(subHorses);
				chessMap[ni][nj].addAll(subHorses);
				for(Integer sh : subHorses) {
					horses[sh].i = ni;
					horses[sh].j = nj;
				}
				if(chessMap[ni][nj].size() >= 4) return true;
				break;
			}
		}
		return false;
	}
	static class Horse{
		int i, j, dir;
		public Horse(int i, int j, int dir) {
			this.i = i;
			this.j = j;
			this.dir = dir;
		}
	}
}