/*
	���� : main - DFS():�迭��6���湮�ؼ� ���ڸ����
	
	HashSet�� ���� �� ������
	�����̰����ؼ� ������ �迭�ξ��ְ� (x+1,y)������ �Լ�4������°� ����
	
	**2�� for������ DFS�� �ȵ����� �ߺ�����̶� (0,0)���� ���������� ���Ѵ�**
	
	������
	1. �ߺ���� - �޸��������ʴ´�
	2. 0���ν����ϴ� ���ڰ��� (Stringd�̳� Integer�� �������)
*/
import java.util.ArrayList;
import java.util.Scanner;
//17996KB, 328ms, 859B
public class ����������_��Ǯ�� {
	static int[][] A = new int[5][5], compass = {{-1,0}, {0,-1}, {1,0}, {0,1}};
	static boolean[][] visited = new boolean[5][5];
	static ArrayList<Integer> list = new ArrayList<>();
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		for(int i=0; i<5; i++) for(int j=0; j<5; j++) A[i][j]=sc.nextInt();
		sc.close();

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				DFS(i, j, 6, 0);// == DFS(i, j, 5, A[i][j])
		
		System.out.println(list.size());
	}
	static void DFS(int r, int c, int k, int num) {
		if (k == 0) {// r==5 && c==5){
			if (!list.contains(num))//�ߺ�(contains)�����ʴ´ٸ� �����߰�
				list.add(num);
			return;
		}
		for(int d=0; d<4; d++) {
			int nr=r+compass[d][0], nc=c+compass[d][1];
			if(nr<0||nc<0||nr>4||nc>4) continue;
			
			DFS(nr, nc, k - 1, 10*num + A[r][c]);
		}
	}
}
