//https://www.acmicpc.net/problem/2309
import java.util.Arrays;
import java.util.Scanner;

public class Main_2309_dwarf_mhs {
	static int dwarfs[] = new int[9];
	static int rlt[] = new int[7];
	public static void main(String[] args) {// 100 : 제약조건
		Scanner sc = new Scanner(System.in);
		for(int i=0; i<9; i++) 
			dwarfs[i] = sc.nextInt();
		sc.close();
		
		Combination_9C7(0, 0, 0, 7);
		Sub_doubleLoop();
		
	}
//	14372 KB, 112ms, 698B
	static int Combination_9C7(int idxN, int idxR, int sum, int r) {
		if(r==0) {
			if(sum ==100) {
				Arrays.sort(rlt);
				for(int rr : rlt)
					System.out.println(rr);
				return 1;
			}
			return 0;
		}
		for(int n=idxN; n<dwarfs.length; n++) 
		{
			rlt[idxR] = dwarfs[n];
			if(Combination_9C7(idxN+1, idxR+1, sum + dwarfs[n], r-1) == 1)
				return 1;//경우으수 중 답1개라서 flag변수처럼 끝까지안가고 탈출
		}
		return 0;//함수 마지막줄인데 안쓰면 오류발생한다
	}
//	14288KB, 108ms, 662B
	static void Sub_doubleLoop() {//9C2 -> 2개뽑으므로 이중for문 사용
		int total=0;
		for(int m : dwarfs)
			total += m;
		
		Arrays.sort(dwarfs);
		for(int i=0; i<dwarfs.length - 1; i++) 
			for(int j=i+1; j<dwarfs.length; j++) 
				if (total == (100 + dwarfs[i] + dwarfs[j])) {
					for (int k = 0; k < dwarfs.length; k++) {
						if(k==i || k==j) continue;
						System.out.println(dwarfs[k]);
					}
					return;//Eclipse에서는 return없어도 돌아가는데 백준에서 위치 잘못넣으면 틀림으로나옴
				}
	}
}
