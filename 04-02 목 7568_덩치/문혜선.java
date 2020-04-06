/*
  ȣ����� : main - Ŭ����Descending():�����Ը� �������� �������� ����
�˰��� : �񱳱����� 2���� �̹Ƿ� ���� �����Ը� �������� �������� ���� �� �ڿ� Ű�� �������� �񱳸� �ؼ� Ŭ ���� ��ŷ�� +1 �Ѵ�

������ ��� : Descending()�Լ��� �ε����� �ٲپ(�񱳱���) sort�Լ� 2������ ���ĳ������� �ߴµ� ������ �ȵ�

*/
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;

public class ��ġ_��Ǯ�� {
	static int n;
	static ArrayList<int[]> people;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		n=sc.nextInt(); sc.nextLine();
		people = new ArrayList<>();
		for(int i=0; i<n; i++) {
			people.add(new int[] {sc.nextInt(), sc.nextInt(), i, 0});//������, Ű, �ε�����ȣ, ����
			
		} sc.close();
		
		people.sort(new Descending());
//		index++;					�ε����� �ٲپ sort�Լ� 2������ ���ĳ������� �ߴµ� ������ �ȵ�
//		people.sort(new Descending());
	
		for(int i=0; i<n; i++) {
			int rank=1;
			for(int j=0; j<n; j++){
			if(i==j) continue;
			if(people.get(i)[1] < people.get(j)[1])
				rank++;
			}
			people.set(i,new int[] {people.get(i)[0],people.get(i)[1],people.get(i)[2],rank});
		}
		
		
		for(int[] person : people)
			System.out.print(person[3] + " ");
	}
	
	static int index=0;//�̰� compare�Լ��ȿ� ������ �� �ڵ����� �þ�鼭 ����� ����.....
	static class Descending implements Comparator<int[]>{
		@Override
		public int compare(int[] a, int[] b) {
			int v1 = a[0], v2 = b[0];//�����⸦ �������� �������� ����
//			int v1 = a[index], v2 = b[index];
//			index++;
			if (v1 > v2)
				return -1;
			else
				return 1;
		}
	}

}
