package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
/*
 * 18808_스티커 붙이기
 */
public class Main {
	static int N, M, K;
	static int[][] notebook;
	static int count;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		notebook = new int[N][M];
		
		K = Integer.parseInt(input[2]);
		for(int k = 0; k < K; k++) {
			input = br.readLine().split(" ");
			int r = Integer.parseInt(input[0]);
			int c = Integer.parseInt(input[1]);
			
			int[][] st = new int[r][c];
			for(int i = 0; i < r; i++) {
				input = br.readLine().split(" ");
				for(int j = 0; j < c; j++)
					st[i][j] = Integer.parseInt(input[j]);
			}
			
			stick(st);
		}
		
		System.out.println(count);
	}
	
	static void stick(int[][] st) {
		for(int ro = 0; ro < 4; ro++) {
			int R = st.length;
			int C = st[0].length;
			if(R > N || C > M) {
				st = rotate(st);
				continue;
			}
			
			for(int startX = 0; startX <= N - R; startX++) {
				for(int startY = 0; startY <= M - C; startY++) {
					if(suit(st, startX, startY)) {
						stickIt(st, startX, startY);
						return;
					}
				}
			}
			
			if(ro == 3)
				break;
			
			st = rotate(st);
		}
	}
	
	static boolean suit(int[][] st, int x, int y) {
		for(int i = x; i < x + st.length; i++) {
			for(int j = y; j < y + st[0].length; j++) {
				if(st[i - x][j - y] == 0 || st[i - x][j - y] == 1 && notebook[i][j] == 0)
					continue;
				
				return false;
			}
		}
		
		return true;
	}
	
	static void stickIt(int[][] st, int x, int y) {
		for(int i = x; i < x + st.length; i++) {
			for(int j = y; j < y + st[0].length; j++) {
				if(st[i - x][j - y] == 1) {
					notebook[i][j] = 1;
					count++;
				}
			}
		}
	}
	
	static int[][] rotate(int[][] st) {
		int R = st.length;
		int C = st[0].length;
		
		int[][] temp = new int[C][R];
		for(int i = 0; i < R; i++) {
			for(int j = 0; j < C; j++) {
				temp[j][R - 1 - i] = st[i][j];
			}
		}
		
		return temp;
	}
}