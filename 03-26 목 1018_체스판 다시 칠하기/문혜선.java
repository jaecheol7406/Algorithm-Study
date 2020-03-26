
/*
 * �帧 : main�Է� - 8x8ü�������� �����ؼ� chessMap�迭�� ���� - sol(chessMap)ȣ�� - ���ϰ��� �����ּҰ� ���� ����
 * �˰���
 *  1) ����for������ (0,0)�� �����Ҽ��ִ� ��ȿ������ ����� arraycopy()�Լ� �̿��Ͽ� 1�پ� 8�������Ͽ� chessMap[8][8]����
 *  2) ü������ �ϼ��Ǹ� �˻��ϴ� �Լ�solȣ��
 *  3) ��ĥ�Ǵ� ����� �� 2�����̰� �� ����� ���� Ȧ���ٰ� ¦������ ���� �����Ƿ� ¦�� �̷� r+=2���������� for���� ���� �˻�
 *  4) ���2�� ��쿡�� �˻�迭�� 1�� �ݴ�(���1�� Ȧ���� =���2�� ¦���ٰ� ����)
 * 
 * ������ : �ּҰ��� ���ϴ°��̶� ����min�� ����min�� ��� Max_Value�� �ؼ� ���� 
 *  �ذ� : ����min�� �ʱⰪ�� 0���� �ΰ� ���� ��ȯ
 */
import java.util.Scanner;
//15788 KB, 120 ms, 1170 B
public class ü���Ǵٽ�ĥ�ϱ�_��Ǯ�� {
	static int n, m, MinPaintings=Integer.MAX_VALUE;
	static char board[][];
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		n=sc.nextInt(); m=sc.nextInt(); sc.nextLine();
		board = new char[n][m];
		for(int i=0; i<n; i++) 
			board[i] = sc.nextLine().toCharArray();
		sc.close();
		
		//���带 8x8ü�������� ���� 
		char chessMap[][] = new char[8][8];
		for(int i=0; i<n-8+1; i++) for(int j=0; j<m-8+1; j++) {
				for(int n=0; n<8; n++) {
//					System.arraycopy(src, srcPos, dest, destPos, length);
					System.arraycopy(board[n+i], j, chessMap[n], 0, 8);
				}
				MinPaintings  = Math.min(MinPaintings, sol(chessMap));
		}
		
		System.out.println(MinPaintings);
	}
	static char[] t1 = {'B','W','B','W','B','W','B','W'};
	static char[] t2 = {'W','B','W','B','W','B','W','B'};
	static int sol(char[][] map) {
		int coloringCase1=0, coloringCase2=0;
		
		for(int r=0; r<8; r+=2) for(int c=0; c<8; c++) {//���1
			if(t1[c] != map[r][c]) coloringCase1++;
			if(t2[c] != map[r+1][c]) coloringCase1++;
		}
		for(int r=0; r<8; r+=2) for(int c=0; c<8; c++) {//���2:���1�� Ȧ���� =���2�� ¦���ٰ� ����
			if(t2[c] != map[r][c]) coloringCase2++;
			if(t1[c] != map[r+1][c]) coloringCase2++;
		}
		
		return Math.min(coloringCase1, coloringCase2);
	}

}
