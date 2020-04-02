package com.exam.month04;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

/**
 *  숨바꼭질 5 : https://www.acmicpc.net/problem/17071
 *  
 *  BFS + 최적화
 *  시간복잡도 O(500000)
 * 
 *       ★★★ Point ★★★
 *  +1, -1 을 이용하면 2초 후에 제자리로 돌아오는 것이 가능함.
 *  따라서, 짝수 / 홀수 시간에 한 번씩만 방문하면 됨.
 */
public class Ex17071 {
	
	static final int MAX = 500000;
	
	static int n;
	static int m;
	
	static int res = -1;
	
	static boolean[][] check = new boolean[MAX + 1][2];
	
	static void bfs() {
		Queue<Integer> q = new LinkedList<Integer>();
		q.add(n);
		check[n][0] = true;
		
		int time = 1;
		
		while (!q.isEmpty()) {
			m += time;
			
			if (m > MAX) break;
			if (check[m][time % 2]) {
				res = time;
				return;
			}
			
			int size = q.size();
			for (int i = 0; i < size; i++) {
				int now = q.remove();
				int[] tmp = {now - 1, now + 1, now * 2};
				
				for (int k = 0; k < 3; k++) {
					int next = tmp[k];
					if (next == m) {
						res = time;
						return;
					}
					
					if (next < 0 || next > MAX) continue;
					if (check[next][time % 2]) continue;
					
					q.add(next);
					check[next][time % 2] = true;
				}
			}
			
			time++;
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		
		if(n == m) {
			System.out.println(0);
			System.exit(0);
		}
		
		bfs();
		
		System.out.println(res);
	}
}
