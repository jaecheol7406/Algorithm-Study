import java.util.Scanner;
/*
 * 14890_경사로
 * 
 * 건너갈 수 있는지 확인 하는 함수를 cango로 정의
 * 행은 map[i] 그대로 cango에 넣어서 확인하고 열은 arr를 새로 만들어서 cango에 넣어서 확인
 * 
 * ※cango 함수
 * 배열 모든 값 순회하면서
 * before, now 선언해서 이전 높이와 비교해가는데, 같은 수(높이)가 반복되면(before == now) 그 개수를 저장해가고(sameCount),
 * 이전값들보다 큰 값이 나오면서(before < now) sameCount가 L보다 크거나 같고 높이가 1 차이나면 그대로 진행
 * 이전값들보다 작은 값이 나오면서(before > now) L 크기만큼 경사로 놓고 진행, L크기만큼 못놓으면 return false;
 * 끝까지 가면 return true;
 */
public class Main3 {
	static int N, L;
	static int[][] map;
	static int count;
	
	public static void main(String[] args) {
		input();
		solve();
		System.out.println(count);
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		L = sc.nextInt();
		map = new int[N][N];
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				map[i][j] = sc.nextInt();
		sc.close();
	}
	
	static void solve() {
		for(int i = 0; i < N; i++) {
			if(cango(map[i]))
				count++;
			
			int[] arr = new int[N];
			for(int j = 0; j < N; j++) {
				arr[j] = map[j][i];
			}
			if(cango(arr))
				count++;
		}
	}
	
	static boolean cango(int[] arr) {
		int before = arr[0];
		int sameCount = 1;
		
		for(int i = 1; i < N; i++) {
			int now = arr[i];
			if(sameCount == 0) {
				if(now > before)
					return false;
				
				sameCount = 1;
				before = now;
				continue;
			}
			
			if(now == before) {
				sameCount++;
				continue;
			}
			
			if(now > before) {
				if(sameCount >= L && now - before == 1) {
					sameCount = 1;
					before = now;
					continue;
				} else
					return false;
			} else {
				if(before - now != 1)
					return false;
				
				before = now;
				sameCount = 1;
				if(L == 1) {
					sameCount = 0;
					continue;
				}
					
				i++;
				while(i < N) {
					now = arr[i];
					if(now != before)
						return false;
					
					sameCount++;
					if(sameCount == L) {
						sameCount = 0;
						break;
					}
					i++;
				}
				if(i == N)
					return false;
			}
		}
		return true;
	}
}