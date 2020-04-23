package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
/*
 * 17779_게리맨더링 2
 * 
 * main -> solve
 * 
 * 1. 인구정보 p에 저장하고, 모든 x y d1 d2 값에 대해 2.조건에 따라 경계선 5를 map에 그려놓는다.
 * 2. 선거구 인구 정보 저장할 배열 re 만들어 놓고 map을 순회하는데, 값이 5이면 가운데 채워가면서 re[4]에 인구수 더한다.
 * 3. 5가 아니면 4.조건에 따라 re 0,1,2,3에 인구수 더한다.
 * 4. re에서 최대 최소 차이 구해서 minDiff에 갱신한다. 
 */
public class No17779_게리맨더링2 {
	static int N;
	static int[][] p;
	static int minDiff = Integer.MAX_VALUE;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		
		p = new int[N + 1][N + 1];
		for(int i = 1; i <= N; i++) {
			String[] input = br.readLine().split(" ");
			for(int j = 0; j < N; j++)
				p[i][j + 1] = Integer.parseInt(input[j]);
		}
		
		solve();
		System.out.println(minDiff);
	}
	
	static void solve() {
		for(int x = 1; x <= N - 2; x++) {
			for(int d1 = 1; d1 <= N - x - 1; d1++) {
				for(int d2 = 1; d2 <= N - x - d1; d2++) {
					for(int y = d1 + 1; y <= N - d2; y++) {
						
						int[][] map = new int[N + 1][N + 1];
												
						for(int v = 0; v <= d1; v++) {
							map[x + v][y - v] = 5;
							map[x + d2 + v][y + d2 - v] = 5;
						}
						
						for(int v = 0; v <= d2; v++) {
							map[x + v][y + v] = 5;
							map[x + d1 + v][y - d1 + v] = 5;
						}
						
						int[] re = new int[5];
						
						for(int i = 1; i <= N; i++) {
							for(int j = 1; j <= N; j++) {
								if(map[i][j] == 5) {
									re[4] += p[i][j];
									
									if(i == x && j == y || i == x + d1 + d2 && j == y - d1 + d2)
										continue;
									
									while(true) {
										re[4] += p[i][++j];

										if(map[i][j] == 5)
											break;
									}
									
									continue;
								}
																
								if(1 <= i && i < x + d1 && 1 <= j && j <= y)
									re[0] += p[i][j];
								else if(1 <= i && i <= x + d2 && y < j && j <= N)
									re[1] += p[i][j];
								else if(x + d1 <= i && i <= N && 1 <= j && j < y - d1 + d2)
									re[2] += p[i][j];
								else
									re[3] += p[i][j];
							}
						}
						
						Arrays.sort(re);
						int diff = re[4] - re[0];
						if(minDiff > diff)
							minDiff = diff;
					}
				}
			}
		}
	}
}