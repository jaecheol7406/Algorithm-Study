/*
  ox�����̹Ƿ� �ȵǴ������� �ĳ��� : loop���� ���������Ǹ����ؾ� O, X�ĳ���� if�� flag=false; break;
  seq�� ���ӵǴ³����� ĭ���� �ӽ����� : for�������� -> �������� �Ѵ�(���ʰ�� �˻��)
  ����  ���θ� ���� ������ ���������� �缳�� h = map[i][j]; cnt=1;
  ������ ���� �˻��Ҷ��� j�ε����� �̵����� ���ΰ� ��ġ�� �ʵ��� �����
  �� �˻��ϴ� �Լ��� �������ʰ� y=x�� ��Ī
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
				if(h+1<map[i][j] || h-1>map[i][j]) {flag =false; break;}//�������� 1�̻� Ż��
				if(h+1==map[i][j]) {
					if(cnt<L) {flag=false; break;}
					//���� ���θ� ���� �� �������� �缳��
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
