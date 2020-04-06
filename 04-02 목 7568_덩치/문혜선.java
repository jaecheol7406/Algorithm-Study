/*
  호출순서 : main - 클래스Descending():몸무게를 기준으로 내림차순 정렬
알고리즘 : 비교기준이 2가지 이므로 먼저 몸무게를 기준으로 내림차순 정렬 한 뒤에 키를 기준으로 비교를 해서 클 수록 랭킹을 +1 한다

실패한 방법 : Descending()함수의 인덱스만 바꾸어서(비교기준) sort함수 2번으로 정렬끝내려고 했는데 구현이 안됨

*/
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;

public class 덩치_내풀이 {
	static int n;
	static ArrayList<int[]> people;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		n=sc.nextInt(); sc.nextLine();
		people = new ArrayList<>();
		for(int i=0; i<n; i++) {
			people.add(new int[] {sc.nextInt(), sc.nextInt(), i, 0});//몸무게, 키, 인덱스번호, 순위
			
		} sc.close();
		
		people.sort(new Descending());
//		index++;					인덱스만 바꾸어서 sort함수 2번으로 정렬끝내려고 했는데 구현이 안됨
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
	
	static int index=0;//이걸 compare함수안에 넣으면 왜 자동으로 늘어나면서 결과가 엉망.....
	static class Descending implements Comparator<int[]>{
		@Override
		public int compare(int[] a, int[] b) {
			int v1 = a[0], v2 = b[0];//몸무기를 기준으로 내림차순 정렬
//			int v1 = a[index], v2 = b[index];
//			index++;
			if (v1 > v2)
				return -1;
			else
				return 1;
		}
	}

}
