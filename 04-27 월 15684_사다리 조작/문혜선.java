import java.util.Arrays;
import java.util.Scanner;

/*
	���� main - isRight() - bruteFoce()
	
	�˰�
 	isRight(int[][] A)
	��ٸ��� i����� i���������� �˻�
	i�ϳ��� �ȸ����� return false, ������ ��� Ž���ѵڿ� �� ������ return true
	
	��ٸ� �߰�
	1) ��ٸ��� 0~3�� �߰��Ǵ°�츦 loop���� �����
	2) ��ٸ� �߰����� �˻� - 0���߰��� �ʱⰪ�� isRight(2�����迭)�� �־ return�� Ȯ��
	3) ������ġ�� �˼��������Ƿ� brute force�� ��簳���� ���� �׽�Ʈ�Ѵ�
	������ ����
	1) ���μ��� ����X, �ߺ�X, �ݵ�� ���� �� O
	2) 2���� �迭������ (1,1)
	3) �򰥸���H�ǹ�(���μ����� ���μ��� ���� �� �ִ� ��ġ�� ����) �����̿ܿ� ���ο� ���μ��� �߰��� �� �ִٴ� ���ΰ�?
 */		
public class ��ٸ�����_��Ǯ��2 {
	static int N, M, H, ansMin=0, existM[][];
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N=sc.nextInt(); M=sc.nextInt(); H=sc.nextInt(); sc.nextLine();
		existM = new int[M][N];
		for(int i=0; i<M; i++){
			int r=sc.nextInt(), c=sc.nextInt();
			existM[r -1][c -1] = 1;
			existM[r -1][c -1 +1] = 1;
		}
		sc.close();
		ansMin = 10;
		boolean flag=false;//��ٸ� 0������ ���Ǹ�������
		if(isRight(existM)) //��ó������ �ʱⰪ���� ����Ȯ�ΰ˻�  : ��ٸ� 0���ΰ��
			flag=true;
		
		loop : 
		for (int n= 1; n < 4 ; n++) {//��ٸ��� 1~3�� �߰��Ǵ� ���
			if(flag) break;
			int[][] C = new int[M][N];
//			for (int i = 0; i < M; i++) C[i] = existM[i].clone(); �ʱ�ȭ�κ��� existM�� ���� ��ٸ��Ѱ��� c�� �����Ѵ�  
			if(bruteForce(C, 0, 0, n)) {
				ansMin = n;
				break loop;
			  }
		}
		System.out.println(ansMin > 3 ? -1 : ansMin);
	}
	static boolean bruteForce(int[][] Pa, int r, int c, int k){
		if(k==0) {
			if( isRight(Pa))
				return true;
			return false;
		}
        for (int i = (c < N ? r : r+1); i <= H; i++) {
            for (int j = 1; j < N; j++) {
                if(Pa[i][j] == 1 || Pa[i][j-1] == 1 || Pa[i][j+1] == 1) continue;
                Pa[i][j] = 1;
                bruteForce(Pa, i, j, k+1);
                Pa[i][j] = 0;
            }
        }
		return false;
	}
/*	
 	isRight(int[][] A)
	��ٸ��� i����� i���������� �˻�
	i�ϳ��� �ȸ����� return false, ������ ��� Ž���ѵڿ� �� ������ return true
*/	
	static boolean isRight(int[][] Pa) {
		int exitNum = -1;
		for(int j=0; j<N ; j++) {
			int r=0,c=j;
			
			while(r<M) {
				if (Pa[r][c] == 1) {
					if (c-1 >= 0 && Pa[r][c-1] == 1)// �������� ��ǥ�̵�
						c--;
					else if (c+1 < N && Pa[r][c+1] == 1)//���������� ��ǥ�̵�
						c++;
				}
				r++;
			}
			exitNum=c;
//			System.out.println(j+"���� �������" + exitNum);
   			if( exitNum == j-1) continue;
			return false;
//			if(j==N-1) return true;//�Ǹ������ٿ� �ξ �����Ѱ���� ǥ���ϱ�
		}
//		System.out.println("��⿡�� ����������� �ڵ带 �߸��ۼ���");
		return true;
	}

}
