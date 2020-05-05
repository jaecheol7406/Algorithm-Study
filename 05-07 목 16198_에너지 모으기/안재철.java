package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
/*
 * 16198_에너지 모으기
 * 
 * main -> dfs
 * 
 * 브루트포스(dfs)로 다 확인해봤다.
 */
public class Main {	
	static int max;
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		List<Integer> list = new ArrayList<>();
		String[] input = br.readLine().split(" ");
		for(int i = 0; i < N; i++)
			list.add(Integer.parseInt(input[i]));
		
		dfs(list, 0);
		System.out.println(max);
	}
	
	static void dfs(List<Integer> list, int energy) {
		if(list.size() == 2) {
			if(energy > max)
				max = energy;
			return;
		}
		
		for(int i = 1; i < list.size() - 1; i++) {
			List<Integer> temp = new ArrayList<>(list);
			int newEnergy = temp.get(i - 1) * temp.get(i + 1);
			temp.remove(i);
			dfs(temp, energy + newEnergy);
		}
	}
}