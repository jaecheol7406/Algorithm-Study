/*
 * �˰��� : A[i]�Է¹��ڸ��� x���� ���� ������ �˻��Ͽ� ������ �ٷ� ������Ѵ�
 * ���� : �迭���� - �迭�� �Է¹����鼭  x���� ���Ͽ� ���
 * ��������
 *  int[] A -> int a 
 *  ���� 1���񱳸� (�迭�� ����X)�ϹǷ� �޸�ȿ���� ���� �迭���Ժ��� �ܼ����� �������� ó��
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
//16444KB, 188ms, 625B
public class x����������_��Ǯ�� {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int n=Integer.parseInt(st.nextToken());
		int x=Integer.parseInt(st.nextToken());
		int[] A = new int[n];
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<n; i++) {
			A[i] = Integer.parseInt(st.nextToken());
			if(A[i] < x)//x���� ���� �� ���� �˻��Ͽ������� �ٷ� ����Ѵ�
				System.out.print(A[i] +" ");
		}
	}
}
