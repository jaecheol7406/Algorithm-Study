package com.exam.day0226;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

/**
 *  이차원 배열과 연산 : https://www.acmicpc.net/problem/17140
 */
public class Ex17140 {
	
	static int R, C, K;
	static int[][] a = new int[100][100];
	
	static class Number {
		int x, count;

		public Number(int x, int count) {
			this.x = x;
			this.count = count;
		}
	}
	
	static int solve() {
		int rsize = 3;
		int csize = 3;
		
		for(int t = 0; t <= 100; t++) {
			if(a[R][C] == K) return t;
			
			if(rsize >= csize) {
				for(int i = 0; i < rsize; i++) {
					List<Number> numList = new ArrayList<Number>();
					int[] cnt = new int[101];
					for(int j = 0; j < csize; j++) {
						cnt[a[i][j]]++;
					}
					
					for(int c = 1; c <= 100; c++) {
						if(cnt[c] > 0) {
							numList.add(new Number(c, cnt[c]));
						}
					}
					
					numList.sort((lhs, rhs)-> {
						return lhs.count - rhs.count;
					});
					
					int idx = 0;
					for(Number num : numList) {
						if(idx >= 99) break;
						a[i][idx++] = num.x;
						a[i][idx++] = num.count;
					}
					
					csize = Math.max(csize, idx);
					for(; idx < 100; idx++) {
						a[i][idx] = 0;
					}
				}
			} else {
				for(int j = 0; j < csize; j++) {
					List<Number> numList = new ArrayList<Number>();
					int[] cnt = new int[101];
					for(int i = 0; i < rsize; i++) {
						cnt[a[i][j]]++;
					}
					
					for(int c = 1; c <= 100; c++) {
						if(cnt[c] > 0) {
							numList.add(new Number(c, cnt[c]));
						}
					}
					
					numList.sort((lhs, rhs)-> {
						return lhs.count - rhs.count;
					});
					
					int idx = 0;
					for(Number num : numList) {
						if(idx >= 99) break;
						a[idx++][j] = num.x;
						a[idx++][j] = num.count;
					}
					
					rsize = Math.max(rsize, idx);
					for(; idx < 100; idx++) {
						a[idx][j] = 0;
					}
				}
			}
		}
		
		return -1;
	}
	
	public static void main(String[] args) throws IOException {
		 BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		 StringTokenizer st = new StringTokenizer(br.readLine());
		 
		 R = Integer.parseInt(st.nextToken()) - 1;
		 C = Integer.parseInt(st.nextToken()) - 1;
		 K = Integer.parseInt(st.nextToken());
		 
		 for(int i = 0; i < 3; i++) {
			 st = new StringTokenizer(br.readLine());
			 for(int j = 0; j < 3; j++) {
				 a[i][j] = Integer.parseInt(st.nextToken());
			 }
		 }
		 
		 System.out.println(solve());
	}
}
