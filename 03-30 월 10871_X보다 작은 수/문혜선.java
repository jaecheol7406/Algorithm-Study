/*
 * 알고리즘 : A[i]입력받자마자 x보다 작은 수인지 검사하여 맞으면 바로 출력을한다
 * 순서 : 배열생성 - 배열값 입력받으면서  x값과 비교하여 출력
 * 개선할점
 *  int[] A -> int a 
 *  값을 1번비교만 (배열값 재사용X)하므로 메모리효율을 위해 배열대입보다 단순변수 대입으로 처리
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
//16444KB, 188ms, 625B
public class x보다작은수_내풀이 {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int n=Integer.parseInt(st.nextToken());
		int x=Integer.parseInt(st.nextToken());
		int[] A = new int[n];
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<n; i++) {
			A[i] = Integer.parseInt(st.nextToken());
			if(A[i] < x)//x보다 작은 수 인지 검사하여맞으면 바로 출력한다
				System.out.print(A[i] +" ");
		}
	}
}
