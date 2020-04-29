package com.exam.swtest;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/**
 *  사다리 조작 : https://www.acmicpc.net/problem/15684
 *  
 *  재귀를 통해 사다리를 놓는다.
 *  i번 세로줄과 i+1번 세로줄의 사이에 j번 가로줄을 연결하면  ==> a[i][j] = 1;
 */
public class Ex15684 {
    static int n, m, h;
    static int ans = 4;
    static int[][] a = new int[30][10];
    
    // 제대로 연결된 사다리인지 확인
    static boolean ladder() {
        for(int i = 0; i < n; i++) {
            int k = i;
            
            for(int j = 0; j < h; j++) {
                if (a[j][k] == 1) {
                    k += 1;
                } else if (k > 0 && a[j][k - 1] == 1) {
                    k -= 1;
                }
            }
            
            if (i != k) return false;
        }
        
        return true;
    }
    
    
    
    static void solve(int cnt, int x, int y) {
        // 정답을 구하면 정답보다 많이 사다리를 놓을 필요가 없으므로
    	if (ans <= cnt) return;
        
    	// 사다리를 하나 놓을 때마다 제대로 연결된 사다리인지 확인
        if(ladder()) {
            if (ans > cnt) ans = cnt;
            
            return;
        }
        
        // 사다리 최대 3개까지 
        if (cnt == 3) return;
        
        for(int i = x; i < h; i++, y = 0) {
            for(int j = y; j < n - 1; j++) {
                if (a[i][j] == 1) {
                    j += 1;
                } else {
                    a[i][j] = 1; // 사다리 놓는다
                    solve(cnt + 1, i, j + 2); // 현재 위치 (i, j)에 사다리를 놓고 j+2 로 점프하여 재귀 호출
                    a[i][j] = 0;
                }
            }
        }
    }
    
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        n = Integer.parseInt(st.nextToken());  // 세로선의 개수
        m = Integer.parseInt(st.nextToken());  // 가로선의 개수
        h = Integer.parseInt(st.nextToken());  // 세로선마다 가로선을 놓을 수 있는 위치의 개수
        
        for(int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            
            a[x - 1][y - 1] = 1;
        }
        
        solve(0, 0, 0);
        
        System.out.println(ans < 4 ? ans : -1);
    }
}
