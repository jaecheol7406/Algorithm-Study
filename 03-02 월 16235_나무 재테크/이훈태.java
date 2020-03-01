package com.exam.day0226;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

/**
 *  나무 재테크 : https://www.acmicpc.net/problem/16235
 *  ※ 문제 조건
 *   - N×N 크기의 땅 ( 1×1 크기의 칸 ). (r, c)
 *   - M개의 나무
 *   ① 봄 : 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다. 각각의 나무는 나무가 있는 1×1 크기의 칸에 있는 양분만 먹을 수 있다.
 *         하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다. 
 *         만약, 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 나무는 양분을 먹지 못하고 즉시 죽는다.
 *   ② 여름 : 봄에 죽은 나무가 양분으로 변하게 된다. 각각의 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다. 
 *           소수점 아래는 버린다.
 *   ③ 가을 : 나무가 번식한다. 번식하는 나무는 나이가 5의 배수이어야 하며, 인접한 8개의 칸에 나이가 1인 나무가 생긴다.
 *   ④ 겨울 : 땅에 양분이 추가. (r,c) 에 추가되는 양분은 A[r][c].
 *   
 *   ★★★★★★★★★★★★★★★★★★★★  해결 방법 S ★★★★★★★★★★★★★★★★★★★★ 
 *   시뮬레이션. 문제의 조건대로 구현.
 *   
 *   ※ 땅이 가지고 있어야 하는 정보
 *  - a[r][c] : 겨울마다 추가되는 양분
 *  - d[r][c] : 칸에 저장되어 있는 양분
 *  - tree[r][c] : 심어져 있는 나무(나이를 저장)
 *   
 *  각각의 칸에 대해서 봄, 여름, 가을, 겨울을 독립적으로 수행
 *  ( 각각의 칸에 대해서 적용되는게 독립적 ==> 하나의 칸에 대해서 봄 ~ 겨울 )
 *   ★★★★★★★★★★★★★★★★★★★★  해결 방법 E ★★★★★★★★★★★★★★★★★★★★ 
 */
public class Ex16235 {
    static final int[] dx = {-1, -1, -1, 0, 0, 1, 1, 1};
    static final int[] dy = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int n = Integer.parseInt(st.nextToken()); // 행, 열
		int m = Integer.parseInt(st.nextToken()); // 나무의 개수
		int l = Integer.parseInt(st.nextToken()); // 년 수
		
		int[][] a = new int[n][n]; // 겨울마다 추가되는 양분
		int[][] d = new int[n][n]; // 칸에 저장되어 있는 양분
		ArrayList<Integer>[][] tree = new ArrayList[n][n]; // 심어져 있는 나무(나이를 저장)
		
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < n; j++) {
				a[i][j] = Integer.parseInt(st.nextToken());
				d[i][j] = 5; // // 가장 처음에 양분은 모든 칸에 5
				tree[i][j] = new ArrayList<>();
			}
		}
		
		// 상도가 심은 나무의 정보 --> 나무를 칸을 기준으로 저장. 그 나무를 저장하는 곳엔 나이를 저장.
		while(m-- > 0) { 
			st = new StringTokenizer(br.readLine());
			
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			int age = Integer.parseInt(st.nextToken());
			
			tree[x - 1][y - 1].add(age);
		}
		
		// 총 l년 동안 진행
		while(l-- > 0) {
			int[][] p = new int[n][n]; // 칸에 나무가 몇 개 생길것인지를 저장
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					ArrayList<Integer> temp = new ArrayList<>(); // 나무가 살아남으면 temp로 이동시키고, 살아남지 못하면 이동시키지 않는다.
					Collections.sort(tree[i][j]); // 하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다. 따라서 정렬.
					
					int dead = 0; // 죽는 나무에 추가되는 양분을 저장
					for(int x : tree[i][j]) {
						if(x <= d[i][j]) {
							d[i][j] -= x; // 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다. 
							temp.add(x + 1);
							
							if((x + 1) % 5 == 0) { // 번식하는 나무는 나이가 5의 배수이어야 하며
								for(int k = 0; k < 8; k++) {
									int nx = i + dx[k];
									int ny = j + dy[k];
									
									if(nx >= 0 && nx < n && ny >= 0 && ny < n) { // 상도의 땅을 벗어나는 칸에는 나무가 생기지 않는다.
										p[nx][ny] += 1; // 인접한 8개의 칸에 나이가 1인 나무가 생긴다.
									}
								}
							}
						} else { // 만약, 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 나무는 양분을 먹지 못하고 즉시 죽는다.
							dead += x/2; // 각각의 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다.
						}
					}
					
					tree[i][j] = temp;  // 살아남은 나무를 모두 바꿔주고
					d[i][j] += dead;    // 양분 추가
					d[i][j] += a[i][j]; // 각 칸에 추가되는 양분의 양은 A[r][c]이고, 입력으로 주어진다
				}
			} // 모든 칸에 대한 처리가 완료
			
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					for(int k = 0; k < p[i][j]; k++) {
						tree[i][j].add(1); // 인접한 8개의 칸에 나이가 1인 나무가 생긴다.
					}
				}
			}
		}
		
		int ans = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				ans += (int)tree[i][j].size(); // 각 칸의 나무 나이의 개수(= 나무의 개수)를 저장
			}
		}
		
		System.out.println(ans);
		
	}
}
