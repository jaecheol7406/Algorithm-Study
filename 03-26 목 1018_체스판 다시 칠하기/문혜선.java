
/*
 * 흐름 : main입력 - 8x8체스판으로 분할해서 chessMap배열에 저장 - sol(chessMap)호출 - 리턴값과 기존최소값 비교후 갱신
 * 알고리즘
 *  1) 이중for문으로 (0,0)이 시작할수있는 유효범위를 만들고 arraycopy()함수 이용하여 1줄씩 8번복사하여 chessMap[8][8]만듬
 *  2) 체스판이 완성되면 검사하는 함수sol호출
 *  3) 색칠되는 경우의 수 2가지이고 각 경우의 수의 홀수줄과 짝수출의 값이 같으므로 짝을 이루어서 r+=2증가량으로 for문을 만들어서 검사
 *  4) 경우2의 경우에는 검사배열이 1과 반대(경우1의 홀수줄 =경우2의 짝수줄과 대응)
 * 
 * 주의점 : 최소값을 구하는것이라 전역min과 지역min을 모두 Max_Value를 해서 오답 
 *  해결 : 지역min은 초기값을 0으로 두고 비교히 반환
 */
import java.util.Scanner;
//15788 KB, 120 ms, 1170 B
public class 체스판다시칠하기_내풀이 {
	static int n, m, MinPaintings=Integer.MAX_VALUE;
	static char board[][];
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		n=sc.nextInt(); m=sc.nextInt(); sc.nextLine();
		board = new char[n][m];
		for(int i=0; i<n; i++) 
			board[i] = sc.nextLine().toCharArray();
		sc.close();
		
		//보드를 8x8체스판으로 분할 
		char chessMap[][] = new char[8][8];
		for(int i=0; i<n-8+1; i++) for(int j=0; j<m-8+1; j++) {
				for(int n=0; n<8; n++) {
//					System.arraycopy(src, srcPos, dest, destPos, length);
					System.arraycopy(board[n+i], j, chessMap[n], 0, 8);
				}
				MinPaintings  = Math.min(MinPaintings, sol(chessMap));
		}
		
		System.out.println(MinPaintings);
	}
	static char[] t1 = {'B','W','B','W','B','W','B','W'};
	static char[] t2 = {'W','B','W','B','W','B','W','B'};
	static int sol(char[][] map) {
		int coloringCase1=0, coloringCase2=0;
		
		for(int r=0; r<8; r+=2) for(int c=0; c<8; c++) {//경우1
			if(t1[c] != map[r][c]) coloringCase1++;
			if(t2[c] != map[r+1][c]) coloringCase1++;
		}
		for(int r=0; r<8; r+=2) for(int c=0; c<8; c++) {//경우2:경우1의 홀수줄 =경우2의 짝수줄과 대응
			if(t2[c] != map[r][c]) coloringCase2++;
			if(t1[c] != map[r+1][c]) coloringCase2++;
		}
		
		return Math.min(coloringCase1, coloringCase2);
	}

}
