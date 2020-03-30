package com.exam.month03;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/**
 *  인구 이동 : https://www.acmicpc.net/problem/16234
 *  
 *  함수 호출 : main -> solve -> find -> move 반복
 *  시간 복잡도 : O(2000 * N^2)
 *  
 *  Solution
 *  ① 입력 받은 map 을 i = 0, j = 0 부터 find 함수로 dfs 탐색을 한다.
 *  ② 그 다음 연합을 이루는 국가 수를 카운팅 하여 2개 이상이면 인구 이동을 시작.
 *  ③ 최종적으로 res 에 가능한 인구 이동 회수를 카운트 하여 리턴.
 */
public class Ex16234 {
	
	static int[] dx = {0, 0, 1, -1};
	static int[] dy = {1, -1, 0, 0};
	
	static int n, l, r;
	static int[][] map;
	
	static int[][] visit; // 0 : 방문 X , 1 : 연합을 이루는 국가 , 2 : 최종적인 인구값으로 변경된 국가
	static int cnt;
	
	static void move(int x, int y, int value) {
		if (x < 0 || x > n - 1 || y < 0 || y > n - 1) return;
		if (visit[x][y] != 1) return;
		
		// 여기까지 왔으면 연합을 이루는 국가임
		visit[x][y] = 2;
		
		map[x][y] = value;
		move(x - 1, y, value);
		move(x + 1, y, value);
		move(x, y - 1, value);
		move(x, y + 1, value);
	}
	
	// parameter : 행, 열, 이전 국가의 인구수
	// 연합을 이루는 모든 국가의 인구수를 반환
	static int find(int x, int y, int value) {
		if (x < 0 || x > n - 1 || y < 0 || y > n - 1) return 0;
		if (visit[x][y] != 0) return 0;
		
		if(value != -1) { // 초기 이전 국가가 없을 때 -1을 줬으므로
			int diff = Math.abs(value - map[x][y]); // 인구 차이
			if (diff < l || diff > r) return 0;
		}
		
		// 여기까지 왔으면 연합이 될 수 있는 국가임 
		visit[x][y] = 1;
		++cnt; // 연합을 이루는 총 국가의 개수를 카운트
		
		int sum = map[x][y]; // 초기값 = 현재 국가의 인구수
		sum += find(x - 1, y, map[x][y]); // 상 : (x-1, y) 에 대해서는 map[x][y] 가 이전 국가의 인구수
		sum += find(x + 1, y, map[x][y]); // 하
		sum += find(x, y - 1, map[x][y]); // 좌
		sum += find(x, y + 1, map[x][y]); // 우
		
		return sum;
	}
	
	static int solve() { // 총 인구 이동 횟수 반환
		int res = 0;
		boolean ok;
		
		do {
			ok = false;
			
			visit = new int[n][n];
			for (int i = 0; i < n; i++) {
				for (int j = 0 ;j < n ; j++) {
					visit[i][j] = 0;
				}
			}
			
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (visit[i][j] == 0) {
						cnt = 0;
						int sum = find(i, j, -1); // 이전 국가의 인구수
						if (cnt > 1) { // 연합을 이루는 국가가 2개 이상이라면 인구 이동을 해야하는 경우
							ok = true;
							move(i, j, sum / cnt);
						} else {
							visit[i][j] = 2; // 인구이동 없이 최종적인 값으로만 입력해줌
						}
					}
				}
			}
			
			if(ok) ++res;
		} while(ok);
		
		
		return res;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		n = Integer.parseInt(st.nextToken());
		l = Integer.parseInt(st.nextToken());
		r = Integer.parseInt(st.nextToken());
		
		map = new int[n][n];
		for (int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < n; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		System.out.println(solve());
	}
}
