import java.util.Scanner;
/*
 * 16917_앙념 반 후라이드 반
 */
public class Main2 {
	static int a,b,c,x,y;
	public static void main(String[] args) {
		input();
		solve();
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		a = sc.nextInt();
		b = sc.nextInt();
		c = sc.nextInt();
		x = sc.nextInt();
		y = sc.nextInt();
		sc.close();
	}
	
	static void solve() {
		int price = 0;
		
		int bundleCount = Integer.min(x, y); // 양념 1개, 후라이드 1개 묶음 개수
		price = Integer.min(a + b, c * 2) * bundleCount; // 양념 1개 후라이드 1개로 묶은 것과 반반 2개로 묶은 것 중 가격 낮은 것으로 묶음 결정
		
		if(x < y) { // 후라이드가 남아있으면
			int remain = y - bundleCount;
			price += remain * Integer.min(b, c * 2); // 남아있는 후라이드 개수만큼 구매하는데, 후라이드1마리짜리로 살건지 반반2개짜리 중 적은 걸로 구매
		}
		else if (x > y) { // 양념이 남아있으면
			int remain = x - bundleCount;
			price += remain * Integer.min(a, c * 2); // 마찬가지
		}
		// 둘다 안남아있으면 끝
		
		System.out.println(price); // 출력
	}
}