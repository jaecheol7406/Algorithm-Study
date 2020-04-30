/*����
	���� : main - check_Drop() - mark_Drop() -  bomb()
	check_Drop() : ���� �Ʒ��� ���������� Ȯ��
	mark_Drop() : ����Լ��� �̿��� �ٴڰ� ����� �ѿ���� true�� ǥ��
	bomb() : �ѹ� ������ �߷����޾� ������ �����´�
	
	�˰���
	1) �迭���� dfs�� �̿��Ͽ� ����Ȼѿ並 ��� ǥ���ϰ� 2��for������ �˻��Ͽ� ����ȵ� �ѿ䰡 ���´ٸ� false
	2) true�ΰ�쿡�� �ش�ѿ並 �����ϰ� �������κ��� �ѿ䳪 �ٴ��� ���϶����� ������ �̵�

*/
import java.util.Scanner;

public class Puyo_��Ǯ�� {
	static char[][] A = new char[12][6];
	static int[][] compass= {{-1,0}, {0,1}, {1,0}, {0,-1}};//�ϵ�����
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		for(int i=0; i<12; i++) A[i] = sc.nextLine().toCharArray();
		sc.close();
		
		int ans=0;
		while(check_Drop()) {
			bomb();
			ans++;
		}
		System.out.println(ans);
	}
	static boolean visited[][];
	static void mark_Drop(int r, int c) {
		if(visited[r][c])
			return;
		
		visited[r][c]= true;
		
		for(int d=0; d<4; d++) {
			int nr=r+compass[d][0], nc=c+compass[d][1];
			if(nr<0||nc<0||nr>=12||nc>=6) continue;
			if(visited[nr][nc]) continue;
			
			mark_Drop(nr, nc);
			
		}
		
	}
	static boolean check_Drop() {
		visited = new boolean[12][6];
		mark_Drop(11,0);
		boolean flag=false;
		int Mm[][] = new int[12][6];
		for(int i=0; i<12; i++) for(int j=0; j<6; j++) {
			if(A[i][j]=='.') continue;
			
			
		}
		
		return flag==true ? true : false;
	}
	static void bomb() {
		//�ϴٰ� ����
	}

}
