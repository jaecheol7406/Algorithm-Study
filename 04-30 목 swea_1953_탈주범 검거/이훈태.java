package com.test.swea;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

/**
 *  탈주범 검거 
 *  
 *  Solution
 *  Queue 에 탈주범의 위치를 넣는다.
 *  파이프의 종류에 따라 갈 수 있는 곳이 달라지는 점에 유의 
 *  파이프를 연결하기 위해서 해당 위치에서 파이프가 연결된 곳의 정보를 status 로 지정 
 */
public class Sw1953 {
	static class Pair {
		int x;
		int y;
		
		public Pair(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}
	
	static int n, m, r, c, l, cnt;
	static int[][] map;
	static boolean[][] visit;
	
	static int[] dx = {-1, 0, 1, 0};
	static int[] dy = {0, 1, 0, -1};
	
	static boolean[][] status = {
			{true, true, true, true}, {true, false, true, false},
			{false, true, false, true}, {true, true, false, false},
			{false, true, true, false}, {false, false, true, true},
			{true, false, false, true}
	};
	
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        int T = Integer.parseInt(br.readLine());

        for (int t = 1; t <= T; t++) {
            st = new StringTokenizer(br.readLine());

            n = Integer.parseInt(st.nextToken());
            m = Integer.parseInt(st.nextToken());
            r = Integer.parseInt(st.nextToken());
            c = Integer.parseInt(st.nextToken());
            l = Integer.parseInt(st.nextToken());

            map = new int[n][m];
            visit = new boolean[n][m];
            cnt = 0;

            for (int i = 0; i < n; i++) {
                st = new StringTokenizer(br.readLine());
                for (int j = 0; j < m; j++) {
                    map[i][j] = Integer.parseInt(st.nextToken());
                }
            }

            solution();
            
            System.out.println("#" + t + " " + cnt);
        }
    }

    private static void solution() {
        Queue<Pair> queue = new LinkedList<>();
        queue.add(new Pair(r, c));
        visit[r][c] = true;
        int nx, ny;

        while (l-- > 0) {
            int len = queue.size();
            for (int t = 0; t < len; t++) {
                Pair target = queue.poll();
                cnt++;

                for (int i = 0; i < 4; i++) {
                    nx = target.x + dx[i];
                    ny = target.y + dy[i];
                    int type = map[target.x][target.y];

                    if (status[type - 1][i] && isValid(nx, ny)) { // 파이프가 뚫려 있는지, map 밖으로 나가지 않았는지
                        if (map[nx][ny] != 0 && !visit[nx][ny]) { // 인접 지역에 파이프가 있는지, 이전 방문한 곳인지
                            int nType = map[nx][ny];

                            if (status[nType - 1][(i + 2) % 4]) {
                                queue.add(new Pair(nx, ny));
                                visit[nx][ny] = true; // 방문 처리
                            }
                        }
                    }
                }
            }
        }
    }

    private static boolean isValid(int x, int y) {
        if (x < 0 || y < 0 || x >= n || y >= m) return false;
        return true;
    }
}
