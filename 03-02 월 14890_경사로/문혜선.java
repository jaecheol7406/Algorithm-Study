/*
  ox문제이므로 안되는조건은 쳐낸다 : loop으로 모든원소조건만족해야 O, X쳐내기는 if로 flag=false; break;
  seq로 연속되는높이의 칸수를 임시저장 : for문돌릴때 -> 방향으로 한다(왼쪽경사 검사용)
  왼쪽  경사로를 만든 다음에 지역변수를 재설정 h = map[i][j]; cnt=1;
  오른쪽 경사로 검사할때는 j인덱스를 이동시켜 경사로가 겹치지 않도록 만든다
  열 검사하는 함수를 만들지않고 y=x축 대칭
/*

import java.io.*;
import java.util.StringTokenizer;
//14088 KB, 96 ms, 1571 B
public class  Main{
	static int ansRoad=0;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		while(! st.hasMoreTokens())
			st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken());
		int L = Integer.parseInt(st.nextToken());
		int[][] matrix = new int[N][N];
		
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) {
			while(! st.hasMoreTokens()) st = new StringTokenizer(br.readLine());
			matrix[i][j] = Integer.parseInt(st.nextToken());
		}
		solveRow(matrix, N, L);
		for(int i=0; i<N; i++) for(int j=i; j<N; j++) {
			int t = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = t;
		}
		solveRow(matrix, N, L);
		System.out.println(ansRoad);
	}
	static void solveRow(int[][] map, int N, int L){
		for(int i=0; i<N; i++) 
		{
			int h =map[i][0];
			int cnt=1;
			boolean flag = true;
			
			for(int j=1; j<N; j++) {
				if(h==map[i][j]) {cnt++; continue;}
				if(h+1<map[i][j] || h-1>map[i][j]) {flag =false; break;}//높이차가 1이상 탈락
				if(h+1==map[i][j]) {
					if(cnt<L) {flag=false; break;}
					//왼쪽 경사로를 만든 후 지역변수 재설정
					h = map[i][j];
					cnt=1;
				}else {
					int t_cnt=0, t_h=map[i][j];
					for(; j<N; j++) {
						if(t_h != map[i][j]) break;
						t_cnt++;
						if(t_cnt == L) break;
					}
					if(t_cnt == L) {
						h = map[i][j];
						cnt=0;
						continue;
					}
					flag = false;
					break;
				}
			}//for - j
			if(flag) 
				ansRoad++;
		}
	}
}
