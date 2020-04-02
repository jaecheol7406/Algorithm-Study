/*
�Լ�ȣ�� : main�Է� - sol(r,c) - ũ��2���̻��̸� �α��� ����,2��for������ �ٽ� �迭A��ȯ
sol(r,c) : DFS�� �̿��� �湮ȭ�� ��ǥ���� ����Ʈ�� ��� ���ձ� �α��� ����

�˰��� : dfs�� �̿��� ���Ǹ����ϴ� 2���̻� ������ĵ��� �̿��� ���ձ����� ����� �α��� ���� 
	 -> ��ü��ȯ �� �Ŀ� �α��̵��Ͼ���� �����+1, ���ȯ
	
������ 1 : visited�޸��ʱ�ȭ�� 2��for��  ����X �ܺ�O
		���� �ʱ�ȭ - �迭A ��ȸ�� ������ ���� ��� ���ŵǹǷ� �־��ǰ��� ���ѷ���
		�ܺ� �ʱ�ȭ - A��ȸ�� ������ ������ ������������ �����Ѵ�
������2 : �α��̵� ����
		dfs�� ���̴� �׷츶�� �α��̵��� �Ͼ�°Ծƴ϶� A�� ��� ��ȯ�ϰ� �� �� �׷칭�ΰ� �����ϸ� �α��̵�+1
������3 : 2�����迭 ��ȯ 2�����ѰԵ������Ѵٸ� 3�� LOOP
*/
import java.awt.Point;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
//210804 KB, 516 ms, 1527 B
public class Main {
	static int N, L, R, ansPopMove=0, sum=0, A[][], compass[][]= {{-1,0},{0,-1},{1,0},{0,1}};
	static List<Point> list;
	static boolean Mm[][];
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N=sc.nextInt(); L=sc.nextInt(); R=sc.nextInt(); sc.nextLine();
		A = new int[N][N];
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) A[i][j]=sc.nextInt();
		sc.close();
		
		list = new LinkedList<>();

		boolean flag;//�α��̵��� �����ϸ� true
		while(true) 
		{
			flag=false;//�ʱ⿡�� �α��̵� �Ұ�
			Mm = new boolean[N][N];

			for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
			if( Mm[i][j] ) continue;
			
			list.clear();
			sum=0; 
			
			DFS(i, j);
			
			if(list.size()==1) continue;
			flag=true;
			
			int newPop = sum / list.size();
			while(!list.isEmpty())
				A[list.get(0).x][list.remove(0).y] = newPop;
			}
			
			//2����A �� ���� �� �Ŀ� �α��̵����� Ȯ��
			if(flag) ansPopMove++;//�α��̵��� �Ͼ���� ��+1, ���ȯ
			if(!flag)break;//Ż��
		 }
	 
		System.out.println(ansPopMove);
	}
	static void DFS(int r, int c) {
		if(Mm[r][c])//������ ������ ��� ����
			return;
		
		Mm[r][c] = true;
		list.add(new Point(r, c));
		sum += A[r][c];
		
		for(int d=0; d<4; d++) {
			int nr=r+compass[d][0], nc=c+compass[d][1];
			
			if(nr<0 || nc<0 || nr>=N || nc>=N) continue;
			int adjSub = Math.abs(A[r][c] - A[nr][nc]);//���������� �α��� �񱳸� �ؼ� ���� ��  : �湮X
			if(adjSub<L || adjSub>R) continue;//�α� ���̰� L�� �̻�, R�� ����
			if(Mm[nr][nc]) continue;
			
			DFS(nr, nc);
		}
	}
}