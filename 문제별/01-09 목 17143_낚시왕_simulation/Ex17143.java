package com.exam.day0109;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/**
 *  낚시왕 : https://www.acmicpc.net/problem/17143
 */
public class Ex17143 {
	
	static class Shark {
		int s;
		int d;
		int z;
		
		public Shark(int s, int d, int z) {
			this.s = s;
			this.d = d;
			this.z = z;
		}
	}
	
	static int R, C, M;
	static Shark[][] arr = new Shark[100][100];
	
	static int[] dx = {-1, 1, 0, 0};
	static int[] dy = {0, 0, 1, -1};
	
	static int solve() {
		int sum = 0;
		Shark[][] backup  = new Shark[100][100];
		
		for(int t = 0; t < C; t++) {
			for(int i = 0; i < R; i++) {
				if(arr[i][t] != null) {
					sum += arr[i][t].z;
					arr[i][t] = null;
					break;
				}
			}
			
			for(int i = 0; i < R; i++) {
				for(int j = 0; j < C; j++) {
					backup[i][j] = arr[i][j];
					arr[i][j] = null;
				}
			}
			
			for(int i = 0; i < R; i++) {
				for(int j = 0; j < C; j++) {
					Shark cur = backup[i][j];
					if(cur != null) {
						int nx = i + cur.s * dx[cur.d];
						int ny = j + cur.s * dy[cur.d];
						
						if(nx < 0) {
							nx = -nx;
							cur.d = 1;
						}
						if(nx > R - 1) {
							int a = nx / (R - 1);
							int b = nx % (R - 1);
							if(a % 2 == 0) {
								nx = b;
							} else {
								nx = R-1 - b;
								cur.d = 0;
							}
						}
						
						if(ny < 0) {
							ny = -ny;
							cur.d = 2;
						}
						if(ny > C - 1) {
							int a = ny / (C - 1);
							int b = ny % (C - 1);
							if(a % 2 == 0) {
								ny = b;
							} else {
								ny = C-1 - b;
								cur.d = 3;
							}
						}
						
						if(arr[nx][ny] == null || (arr[nx][ny] != null && arr[nx][ny].z < cur.z)) {
							arr[nx][ny] = cur;
						}
						
					}
				}
			}
		}
		
		return sum;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		st = new StringTokenizer(br.readLine());
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		for(int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(st.nextToken()) - 1;
			int c = Integer.parseInt(st.nextToken()) - 1;
			int s = Integer.parseInt(st.nextToken());
			int d = Integer.parseInt(st.nextToken()) - 1;
			int z = Integer.parseInt(st.nextToken());
			arr[r][c] = new Shark(s, d, z);
		}
		
		System.out.println(solve());
	}
	
}
