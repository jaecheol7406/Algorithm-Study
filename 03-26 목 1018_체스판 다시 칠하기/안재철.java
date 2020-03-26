import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 1018_체스판 다시 칠하기
 * solve() -> makeChess()
 * 
 * 만들 수 있는 모든 8x8 체스판에 대해, 2가지 경우
 * 		1. 맨 왼쪽 위가 W인 경우
 * 		2. 맨 왼쪽 위가 B인 경우
 * 중 다시 칠해야하는 최소 개수 적은 경우 계산, 가장  최솟값 저장 후 출력
 */
public class Main {
	static int N, M;
	static char[][] map;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		
		map = new char[N][M];
		for(int i = 0; i < N; i++) {
			String input2 = br.readLine();
			for(int j = 0; j < M; j++) {
				map[i][j] = input2.charAt(j);
			}
		}
		
		solve();
	}
	
	static void solve() {
		int minCount = Integer.MAX_VALUE;
		for(int startI = 0; startI <= N - 8; startI++) {
			for(int startJ = 0; startJ <= M - 8; startJ++) {
				
				int WCount = makeChess(startI, startJ, 'W');
				int BCount = makeChess(startI, startJ, 'B');
				int small = Integer.min(WCount, BCount);
				minCount = Integer.min(minCount, small);
			}
		}
		System.out.println(minCount);
	}
	
	static int makeChess(int startI, int startJ, char color) {
		char another;
		if(color == 'W')
			another = 'B';
		else
			another = 'W';
		
		char nextColor = color;
		int count = 0;
		for(int i = startI; i < startI + 8; i++) {
			for(int j = startJ; j < startJ + 8; j++) {
				if(nextColor == color) {
					nextColor = another;
					if(map[i][j] != color)
						count++;
				} else {
					nextColor = color;
					if(map[i][j] != another)
						count++;
				}
			}
			
			if(nextColor == color)
				nextColor = another;
			else
				nextColor = color;
		}
		return count;
	}
}