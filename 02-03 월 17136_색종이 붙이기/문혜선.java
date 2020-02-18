//20732 KB, 196 ms, 1480 B
import java.util.Scanner;
public class Main {
	static int cntOne=0, resultMin=Integer.MAX_VALUE;
	static int[] papers = {0, 5, 5, 5, 5, 5};
	static int[][] grid = new int[10][10];
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++) {
				grid[i][j] = sc.nextInt();
				cntOne += grid[i][j];
			}
		sc.close();
		f(0, 0, 0);
		System.out.println(resultMin == Integer.MAX_VALUE ? -1 : resultMin);
	}
	static void f(int num, int removedOne, int usedPaper) {
		if(usedPaper >= resultMin) return ;
		if(cntOne == removedOne || num==100) {
			resultMin = Math.min(resultMin, usedPaper);
			return;
		}
		int r= num/10, c= num%10;
			if (grid[r][c] == 1) {	
			for(int size=5; size>0; size--) 
			{
				if(papers[size] <= 0) continue;
				if ( ! isAllOne(r, c, size)) continue;
				
				papers[size] += -1;
				setVisited(r, c, size);
				f(num + 1, removedOne + size*size, usedPaper+1);
				setVisited(r, c, size);
				papers[size] += 1;
			}
			}else
				f(num+1, removedOne, usedPaper);
	}

	static boolean isAllOne(int r, int c, int size) {
		if(r+size-1 >9 || c+size-1 >9) return false;//범위체크

		for (int i2 = 0; i2 < size; i2++) for (int j2 = 0; j2 < size; j2++)
				if (grid[r + i2][c + j2] == 0)
					return false;
		return true;
	}
	static void setVisited(int r, int c, int size) {
		for(int i=0; i<size; i++) for(int j=0; j<size; j++)
			grid[r+i][c+j] = grid[r+i][c+j]^1;
	}
}