import java.util.Arrays;
import java.util.Scanner;

/*
	순서 main - isRight() - bruteFoce()
	
	알고
 	isRight(int[][] A)
	사다리가 i열출발 i열도착인지 검사
	i하나라도 안맞으면 return false, 끝까지 모두 탐색한뒤에 다 맞으면 return true
	
	사다리 추가
	1) 사다리가 0~3개 추가되는경우를 loop으로 만든다
	2) 사다리 추가전에 검사 - 0개추가는 초기값을 isRight(2차원배열)에 넣어서 return값 확인
	3) 최적위치를 알수가없으므로 brute force로 모든개수의 경우로 테스트한다
	주의할 조건
	1) 가로선이 연속X, 중복X, 반드시 점선 위 O
	2) 2차원 배열시작이 (1,1)
	3) 헷갈리는H의미(세로선마다 가로선을 놓을 수 있는 위치의 개수) 교점이외에 새로운 가로선을 추가할 수 있다는 말인가?
 */		
public class 사다리조작_내풀이2 {
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
		boolean flag=false;//사다리 0개에서 조건만족여부
		if(isRight(existM)) //맨처음에는 초기값으로 조건확인검사  : 사다리 0개인경우
			flag=true;
		
		loop : 
		for (int n= 1; n < 4 ; n++) {//사다리가 1~3개 추가되는 경우
			if(flag) break;
			int[][] C = new int[M][N];
//			for (int i = 0; i < M; i++) C[i] = existM[i].clone(); 초기화부분은 existM을 보고 사다리둘곳만 c에 저장한다  
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
	사다리가 i열출발 i열도착인지 검사
	i하나라도 안맞으면 return false, 끝까지 모두 탐색한뒤에 다 맞으면 return true
*/	
	static boolean isRight(int[][] Pa) {
		int exitNum = -1;
		for(int j=0; j<N ; j++) {
			int r=0,c=j;
			
			while(r<M) {
				if (Pa[r][c] == 1) {
					if (c-1 >= 0 && Pa[r][c-1] == 1)// 왼쪽으로 좌표이동
						c--;
					else if (c+1 < N && Pa[r][c+1] == 1)//오른쪽으로 좌표이동
						c++;
				}
				r++;
			}
			exitNum=c;
//			System.out.println(j+"열의 결과값은" + exitNum);
   			if( exitNum == j-1) continue;
			return false;
//			if(j==N-1) return true;//맨마지막줄에 두어서 가능한경우라고 표시하기
		}
//		System.out.println("모듈에서 여기까지오면 코드를 잘못작성함");
		return true;
	}

}
