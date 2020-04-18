 //0.13652s
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;
public class Solution {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int T;
		T=sc.nextInt();
		for(int test_case = 1; test_case <= T; test_case++)
		{
				int N=sc.nextInt(); int K=sc.nextInt(); sc.nextLine();
				char[] nums = sc.nextLine().toCharArray();
				
				int[] hexa = new int[N/4];
				hexa[0] = 1;
				int i=1; 
				while(i<N/4) {
					hexa[i] = 16*hexa[i-1];
					i++;
				}
				
				ArrayList<Integer> al = new ArrayList<>();
				for(int r=0; r<N/4; r++)
				{
					char[] nums2 = nums.clone();
					if(r!=0) {
						char t = nums[nums.length-1];
						for(int ii=1; ii<nums.length; ii++)
							nums2[ii] = nums[ii-1];
						nums2[0]=t;
					}
					
					for(int k=0; k<nums2.length; k+=N/4) {
						char[] subC = new char[N/4];
						for(int j=0; j<N/4; j++)
							subC[j] = nums2[j + k]; 
						int pw=0;
						for(int j=0; j<N/4; j++) {
							int n;
							if(subC[j] >=48 && subC[j] <58) n = subC[j] - 48;
							else
								n = subC[j] - 55;
							pw += n * hexa[N/4 -j -1];
						}
						if(! al.contains(pw))
							al.add(pw);
					}
					nums = nums2.clone();
				}
				al.sort(null);
				Collections.reverse(al);
				System.out.println("#" + test_case + " " + al.get(K-1));
		}
		sc.close();
	}
}