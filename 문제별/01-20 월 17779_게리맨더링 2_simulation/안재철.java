import java.util.Arrays;
import java.util.Scanner;
/* 17779_게리맨더링 2
 */
public class Main {
	
	static int N;
	static int[][] map;
	static int[][] partition;
	static int x, y, d1, d2;
	static int re = Integer.MAX_VALUE;
	
	public static void main(String[] args){
		input();
		solve();
		System.out.println(re);
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		
		N = sc.nextInt();
		map = new int[N + 1][N + 1];
		partition = new int[N + 1][N + 1];
		
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++)
				map[i][j] = sc.nextInt();
		}
		
		sc.close();
	}
	
	static void solve() {
		for(int x = 1; x <= N - 2; x++) {
			for(int y = 2; y <= N - 1; y++) {
				for(int d1 = 1; d1 <= y - 1; d1++) {
					for(int d2 = 1; d2 <= N - y; d2++) {
						if(!(x + d1 + d2 <= N && 1 <= y - d1 && y + d2 <= N))
							continue;
						
						re = Integer.min(re, calcDiff(x, y, d1, d2));
						partition = new int[N + 1][N + 1];
					}
				}
			}
		}
	}
	
	static int calcDiff(int x, int y, int d1, int d2) {
		int[] sections = new int[6];
		
		// 1, 4 경계선 그리기
		for(int i = 0; i <= d1; i++) {
			partition[x + i][y - i] = 5;
			partition[x + d2 + i][y + d2 - i] = 5;
		}
		
		// 2, 3 경계선 그리기
		for(int i = 0; i <= d2; i++) {
			partition[x + i][y + i] = 5;
			partition[x + d1 + i][y - d1 + i] = 5;
		}
		
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				// 경계선일 때
				if(partition[i][j] == 5) {
					
					sections[5] += map[i][j];
					
					// 맨 윗 경계 꼭짓점, 아래 꼭짓점일 때는 아무것도 안하고 다음구역으로
					if(i == x || i == x + d1 + d2)
						continue;
					
					// 경계선 가운데 있는 구역 모두 5선거구 인구로 계산
					while(j != N && partition[i][++j] != 5) {
						partition[i][j] = 5;
						sections[5] += map[i][j];
					}
					sections[5] += map[i][j];
					
				// 경계선 아닐 때는 각 선거구의 범위에 따라 인구 계산
				} else {
					if(1 <= i && i < x + d1 && 1 <= j && j <= y) // 1선거구
						sections[1] += map[i][j];
					else if(1 <= i && i <= x + d2 && y < j && j <= N) // 2선거구
						sections[2] += map[i][j];
					else if(x + d1 <= i && i <= N && 1 <= j && j < y - d1 + d2) // 3선거구
						sections[3] += map[i][j];
					else // 4선거구
						sections[4] += map[i][j];
				}
			}
		}
		
		Arrays.sort(sections, 1, 6);
		return sections[5] - sections[1];
	}
}