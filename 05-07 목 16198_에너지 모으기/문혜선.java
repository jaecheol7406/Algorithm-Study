/*
	item배열크기가 변하는 DFS

 	순서 : main - DFS()
 	dfs() : 가변items을 인수로 받아서 2번째~마지막-1까지 인덱스를 모두 탐색하며 에너지합을구함
	
	알고
	특정위치 삭제와 추가가 편리하게 하기 위해서 ArrayList사용
	인덱스 1번부터 가변배열의크기의 -1까지 인덱스 범위로 설정
	
	주의점
	1) 첫구슬의 인덱스 1번
	2) 뽑히는 대상의 크기가 하나씩 줄어든다(item입력시 지역변수로 설정하고 매개변수로 넘기기)
*/
import java.util.ArrayList;
import java.util.Scanner;
//18532KB, 156ms, 725B
public class 에너지모으기_내풀이 {
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
		for(int i=1; i<items.size()-1; i++) {//첫 번째와 마지막  제외(1~N-1) -> 가변사이즈이므로 N대신 item.size()
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