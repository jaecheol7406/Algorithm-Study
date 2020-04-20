/*
	 ���� : main - axis():C������ ��� y=x�� ��Ī
	 �˰���
	 C������ ��쿡�� y=x���Ī�� �Ѵ�
	 A[i]�� �������� ������ �� ������ 0�� �����ϰ� ������ ���� al���Ϳ� [����,Ƚ��]���·� ����
	 Ƚ��[1]�� �������� �������� ����
	 sorted(int[])�� �����迭�� ���� ���� rltAry�� �迭�� �߰������ش� (A[i]�� �ٷ� �߰��� �ȵǱ� ����)
	 ��� �� �ִ밪�� ���Ž����ش�
	 flag������ C������ �� ��쿡�� �ٽ� ���Ī�� ���� ����ġ�� �����
*/
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class �������迭������_��Ǯ�� {

	public static void main(String[] args) {
// ���ĵ� ����� �迭�� ���� ����, ���� ���� Ƚ���� ��� ������, ������ ���� �����̴�.
//		�� �Ǵ� ���� ũ�Ⱑ 100�� �Ѿ�� ��쿡�� ó�� 100���� ������ �������� ������.
		Scanner sc = new Scanner(System.in);
		int r=sc.nextInt(), c=sc.nextInt(), k=sc.nextInt();
		int[][] A = new int[3][3];
		for(int i=0; i<3; i++) for(int j=0; j<3; j++) A[i][j]=sc.nextInt();
		sc.close();
		
		int minSec=0, sizeR=3, sizeC=3;//
		while(A[r-1][c-1] != k) {
			A = (sizeR>=sizeC) ? A : axis(A, sizeR, sizeC);//C������ ��� ������ r����� �����ϹǷ� ��ġ�� �ٲ۴����� �����Ѵ�
			boolean flag = (sizeR>=sizeC) ? false : true; //���� �� c������ �ٽ� y=x���Ī�ؾ���
			int[] sorted;//�迭�� �����
			
			ArrayList<int[]> rltAry = new ArrayList<>();
			for(int i=0; i<A.length; i++)
			{
				Arrays.sort(A[i]);//������������ ���� ����
				int g[]= (A[i][0]==0) ? new int[A[i].length-1] : new int[A[i].length];
				int num, cnt=1;
				ArrayList<int[]> al = new ArrayList<>();
				for(int j=1; j<A[i].length; j++) {//�ε��� ������ 1����
					if(A[i][j] == 0) continue;
					if(A[i][j-1] == A[i][j]) 
						cnt++;//A[i][j]���� �������� ����
					else {
						num = A[i][j-1];
						al.add(new int[]{num,cnt});
						cnt=1;
					}
					
					if(j==A[i].length-1) {//������ �迭�� ������ �߰�������Ѵ�
						num = A[i][j];
						al.add(new int[]{num,cnt});
					}
				}
				
				al.sort(new Comparator<int[]>(){//[����,Ƚ��] �߿��� Ƚ��[1]�� �������� �������� ����
					@Override
					public int compare(int[] o1, int[] o2) {
						int v1=o1[1], v2=o2[1];//[����,Ƚ��] �߿��� Ƚ��[1]�� ���������Ѵ�
						
						if(v1==v2) return 0;
						else if(v1 > v2) return 1;
						else return -1;
					}
				});
				
				sorted = new int[2* al.size()];
				int idxS=0;
				for(int[] a : al) {
					sorted[idxS++] = a[0];
					sorted[idxS++] = a[1];
				}
				
//				System.out.println(Arrays.toString(sorted));
//				A[i] = sorted.clone(); ũ�⶧���� �ȵ�
				rltAry.add(sorted);

				if(flag)
					sizeR = (sizeR < sorted.length) ? sorted.length : sizeR;
				else
					sizeC = (sizeC < sorted.length) ? sorted.length : sizeC;//R���� ->���� ��������
					
			}
			
			A = new int[sizeR][sizeC];
			for(int i=0; i<A.length; i++) {
				A[i] = rltAry.get(i).clone();//ArrayList<int> -> int[]q�迭�� clone���� ���԰���
//				System.out.println(Arrays.toString(A[i]));
			}
			
			
			if(flag)
				A = axis(A,sizeR, sizeC);
			minSec++;
		}
		System.out.println(minSec);
	}
	static int[][] axis(int[][] P, int r, int c){//y=x���Ī, ���簢�� �迭�� ���
//		int[][] R = new int[c][r]; //�࿭�� ���簢���ΰ��
		
		for(int i=0; i<P.length; i++)
			for(int j=i; j<P[0].length; j++) //in[0].length : ������
			{
				int t = P[i][j];
				P[i][j] = P[j][i];
				P[j][i] = t;
			}
		return P;
	}

}
//https://www.acmicpc.net/problem/17140