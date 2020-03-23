package com.lecture.problem2.bfs;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

/**
 *  아기 상어 : https://www.acmicpc.net/problem/16236
 *  
 *  거리가 가장 가까운 물고기를 찾기 위해 BFS 이용 ==> BFS 한 번의 시간 복잡도 O(N^2)
 *  모든 칸에 물고기가 있고, 상어가 이 물고기를 다 먹을 수 있다면 최대 N^2번 BFS 수행
 *  시간 복잡도 : O(N^4) (N <= 20 이기 때문에 가능)
 *  
 *  문제 주어진 조건대로 움직이면 됨.
 */
public class Ex16236 {
	static class Pair {
		int dist, x, y;

		public Pair(int dist, int x, int y) {
			this.dist = dist;
			this.x = x;
			this.y = y;
		}
	}
	
    static int[] dx = {0, 0, 1, -1};
    static int[] dy = {1, -1, 0, 0};
    
    static Pair bfs(int[][] a, int sx, int sy, int size) {
    	int n = a.length;
    	ArrayList<Pair> ans = new ArrayList<>(); // 상어가 먹을 수 있는 모든 물고기의 리스트
    	int[][] d = new int[n][n];
    	for(int i = 0; i < n; i++) {
    		for(int j = 0; j < n; j++) {
    			d[i][j] = -1;
    		}
    	}
    	
    	Queue<Integer> q = new LinkedList<Integer>();
    	q.add(sx);
    	q.add(sy);
    	d[sx][sy] = 0;
    	
    	while(!q.isEmpty()) {
    		int x = q.remove();
    		int y = q.remove();
    		
    		for(int k = 0; k < 4; k++) {
    			int nx = x + dx[k];
    			int ny = y + dy[k];
    			
    			if(nx >= 0 && nx < n && ny >= 0 && ny < n && d[nx][ny] == -1) {
    				boolean ok = false;
    				boolean eat = false;
    				
    				// 아기 상어는 자신의 크기보다 큰 물고기가 있는 칸은 지나갈 수 없고, 나머지 칸은 모두 지나갈 수 있다.
    				if(a[nx][ny] == 0) {
    					ok = true;
    				} else if(a[nx][ny] < size) { // 아기 상어는 자신의 크기보다 작은 물고기만 먹을 수 있다.
    					ok = eat = true;
    				} else if(a[nx][ny] == size) { // 크기가 같은 물고기는 먹을 수 없지만, 그 물고기가 있는 칸은 지나갈 수 있다.
    					ok = true;
    				}
    				
    				if(ok) {
    					q.add(nx);
    					q.add(ny);
    					d[nx][ny] = d[x][y] + 1;
    					if(eat) {
    						ans.add(new Pair(d[nx][ny], nx, ny));
    					}
    				}
    			}
    		}
    	}
    	
    	if(ans.isEmpty()) {
    		return null;
    	}
    	
    	Pair best = ans.get(0);
    	for(Pair p : ans) {
    		if(best.dist > p.dist) {
    			best = p;
    		} else if(best.dist == p.dist && best.x > p.x) {
    			best = p;
    		} else if(best.dist == p.dist && best.x == p.x && best.y > p.y) {
    			best = p;
    		}
    	}
    	
    	return best;
    }
    
    /**
     *  0: 빈 칸
     *  1, 2, 3, 4, 5, 6: 칸에 있는 물고기의 크기
     *  9: 아기 상어의 위치
     */
    public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int n = Integer.parseInt(st.nextToken());
		int[][] a = new int[n][n];
		
		int x = 0, y = 0; // 상어의 위치
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < n; j++) {
				a[i][j] = Integer.parseInt(st.nextToken());
				if(a[i][j] == 9) { // 상어
					x = i;
					y = j;
					a[i][j] = 0;
				}
			}
		}
		
		int ans = 0;  // 거리의 합
		int size = 2; // 크기
		int exp = 0;  // 경험치
		
		while(true) {
			Pair p = bfs(a, x, y, size); // bfs --> 가장 거리가 가까운 물고기의 거리, 위치(x,y)를 return
			if(p == null) break;
			a[p.x][p.y] = 0; // 먹었으면 물고기 없어지고
			ans += p.dist;   // 그 때의 거리(문제에서 거리의 합을 계산하라고 했기 때문)
			exp += 1;
			if(size == exp) {
				size += 1;
				exp = 0;
			}
			
			x = p.x;
			y = p.y;
		}
		
		System.out.println(ans);
	}
}
