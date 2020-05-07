/*
	item�迭ũ�Ⱑ ���ϴ� DFS

 	���� : main - DFS()
 	dfs() : ����items�� �μ��� �޾Ƽ� 2��°~������-1���� �ε����� ��� Ž���ϸ� ��������������
	
	�˰�
	Ư����ġ ������ �߰��� ���ϰ� �ϱ� ���ؼ� ArrayList���
	�ε��� 1������ �����迭��ũ���� -1���� �ε��� ������ ����
	
	������
	1) ù������ �ε��� 1��
	2) ������ ����� ũ�Ⱑ �ϳ��� �پ���(item�Է½� ���������� �����ϰ� �Ű������� �ѱ��)
*/
import java.util.ArrayList;
import java.util.Scanner;
//18532KB, 156ms, 725B
public class ������������_��Ǯ�� {
	static int N;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N=sc.nextInt(); sc.nextLine();
		ArrayList<Integer> gusil = new ArrayList<>(N);
		for(int i=0; i<N; i++) gusil.add( sc.nextInt() );
		sc.close();
		
		System.out.println( DFS(gusil, N-2, 0) );
	}
	static int DFS(ArrayList<Integer> items, int k, int E) {
		if(k==0)//&&items.size() < 3 
			return E;
		
		int retE=0 ; 
		for(int i=1; i<items.size()-1; i++) {//ù ��°�� ������  ����(1~N-1) -> �����������̹Ƿ� N��� item.size()
			int add = items.get(i-1) * items.get(i+1); 
			int saved = items.get(i);

			items.remove(i);
			int e = DFS(items, k-1, E + add);
			retE = Math.max(retE, e);
			
			items.add(i, saved);
		}
		return retE;
	}
}