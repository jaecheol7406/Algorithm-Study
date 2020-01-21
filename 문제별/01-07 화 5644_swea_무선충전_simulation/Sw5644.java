package com.exam.day0107;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Sw5644 {
	
	static class AP {
		int x;
		int y;
		int c;
		int p;
		
		AP(int x, int y, int c, int p) {
			this.x = x;
			this.y = y;
			this.c = c;
			this.p = p;
		}
	}
	
	static int M; // 총 이동 시간
	static int A; // BC의 개수
	static int dx[] = {0, -1, 0, 1, 0};
	static int dy[] = {0, 0, 1, 0, -1};
	static int Ainfo[]; // A의 이동정보
	static int Binfo[]; // B의 이동정보
	static ArrayList<AP> aplist; // AP의 정보
    
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			M = Integer.parseInt(st.nextToken());
			A = Integer.parseInt(st.nextToken());
			Ainfo = new int[M];
			Binfo = new int[M];
			
            // 사용자 A의 이동정보
			st = new StringTokenizer(br.readLine());
			for(int i = 0; i < M; i++) {
				Ainfo[i] = Integer.parseInt(st.nextToken());
			}
			
            // 사용자 B의 이동정보
			st = new StringTokenizer(br.readLine());
			for(int i = 0; i < M; i++) {
				Binfo[i] = Integer.parseInt(st.nextToken());
			}
			
            // BC의 정보를 ArrayList에 저장한다.
			aplist = new ArrayList<AP>();
			for(int i = 0; i < A; i++) {
				st = new StringTokenizer(br.readLine());
				int y = Integer.parseInt(st.nextToken()); // 행
				int x = Integer.parseInt(st.nextToken()); // 열
				int c = Integer.parseInt(st.nextToken()); // 충전 범위
				int p = Integer.parseInt(st.nextToken()); // 성능
				
				aplist.add(new AP(x, y, c, p));
			}
			
			int ans = solve();
			System.out.println("#" + tc + " " + ans);
		}
	}
	
    
	static int solve() {
		int x1 = 1;
		int y1 = 1;
		int x2 = 10;
		int y2 = 10;
        
        // 0초일때의 합
		int sum = getMax(x1,y1,x2,y2);
		
		for(int time = 0; time < M; time++) {
			x1 += dx[Ainfo[time]];
			y1 += dy[Ainfo[time]];
			x2 += dx[Binfo[time]];
			y2 += dy[Binfo[time]];
			sum += getMax(x1,y1,x2,y2);
		}
		
		return sum;
	}
	
	/*
	 *  충전양의 최대값을 구하는 함수
	 */
	static int getMax(int x1, int y1, int x2, int y2) {
		int[][] bt = new int[2][A];
		
		// 사용자 A의 충전양 정보
		for(int j = 0; j < A; j++) {
			bt[0][j] = check_range(x1, y1, j);
		}
		
		// 사용자 B의 충전양 정보
		for(int j = 0; j < A; j++) {
			bt[1][j] = check_range(x2, y2, j);
		}
		
		int max = 0;
		for(int i = 0; i < A; i++) {
			for(int j = 0; j < A; j++) {
				int sum = bt[0][i] + bt[1][j];
                
				if(i == j && bt[0][i] == bt[1][j]) sum /= 2;
				if(sum > max) max = sum;
			}
		}

		return max;
	}
	
	/*
	 *  사용자가 BC 충전 범위에 속하는지 체크하는 함수
	 */
	static int check_range(int x, int y, int apnum) {

		int a = Math.abs(x - aplist.get(apnum).x);
		int b = Math.abs(y - aplist.get(apnum).y);
		int dist = a + b;
        
		if(dist <= aplist.get(apnum).c) {
			return aplist.get(apnum).p;
		} else {
			return 0;
		}
	}
	
}