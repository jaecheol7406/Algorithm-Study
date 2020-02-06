import java.util.Scanner;

public class Main {
	static int n, m, maxLength=1;
	static int[][] map;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt(); m =sc.nextInt(); sc.nextLine();
		map = new int[n][m];
		for(int i=0; i<n; i++) 	{
			String input = sc.nextLine();
			for(int j=0; j<m; j++)
				map[i][j] = input.charAt(j) - 48;
		}sc.close();
	
		f();
		System.out.println(maxLength * maxLength);
	}
	static void f() {
		for(int i=1; i<n; i++)	for(int j=1; j<m; j++) 
		{
			if(map[i][j] == 0) continue;
			
			int min = Math.min(map[i-1][j], map[i][j-1]);
			min = Math.min(min, map[i-1][j-1]);
			
			map[i][j] = min + 1;
		}
			
		for(int i=1; i<n; i++)	for(int j=1; j<m; j++) 
			if(maxLength < map[i][j]) maxLength = map[i][j];
	}
}
