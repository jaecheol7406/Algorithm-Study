import java.util.ArrayList;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Scanner;
/*
 * 16235_나무 재테크
 * ※ 땅 하나를 Section 클래스로 나타냄. Section에는 나무들을 나타내는 trees, 양분을 나타내는 energy, 추가될 양분값인 added
 * ※ 나무 하나를 Tree 클래스로 나타냄. 위치를 나타내는 pos, 나이를 나타내는 age
 * ※ trees는 PriorityQueue 우선순위 큐로 저장, 크기 N인 Section 2차원 배열로 전체 땅을 나타냄 (land)
 * ※ treePosList에 나무가 있는 좌표값을 저장해놓음
 * 1. 봄, 여름을 같이 진행.
 * 	treePosList의 좌표값에 해당하는 Section의 trees에서 뽑아내면 age가 낮은 순으로 꺼내지니까 에너지보다 작거나 같을 때까지 꺼내다가 에너지 넘어가면 그 뒤에꺼는 죽임.
 * 2. 가을
 * 	조건대로 treePosList 순회해서 모든 나무들에 대해 번식 진행
 * 3. 겨울
 * 	Section의 added 값만큼 energy에 추가
 */
public class Main2 {
	public static final int[][] moveDir = new int[][]{{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
	
	static int N, M, K; // 땅 크기, 나무 개수, 년
	static Section[][] land;
	static ArrayList<Pos> treePosList = new ArrayList<>();
	static int treeCount;
	
	public static void main(String[] args) {
		input();
		solve();
		System.out.println(treeCount);
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		K = sc.nextInt();
		land = new Section[N][N];
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				land[i][j] = new Section(sc.nextInt());
			}
		}
		for(int i = 0; i < M; i++) {
			Pos pos = new Pos(sc.nextInt() - 1, sc.nextInt() - 1);
			int age = sc.nextInt();
			treePosList.add(pos);
			land[pos.x][pos.y].trees.add(new Tree(pos, age));
		}
		treeCount = M;
		sc.close();
	}
	
	static void solve() {
		for(int i = 0; i < K; i++) {
			springAndSummer();
			fall();
			winter();
		}
	}
	
	static void springAndSummer() {
		for(Pos pos : treePosList) {
			Section section = land[pos.x][pos.y];
			if(section.trees.isEmpty())
				continue;
			
			PriorityQueue<Tree> trees = section.trees;
			section.trees = new PriorityQueue<>();
			while(!trees.isEmpty()) {
				Tree tree = trees.poll();
				if(tree.age > section.energy) {
					treeCount -= (trees.size() + 1);
					
					section.energy += tree.age / 2;
					
					while(!trees.isEmpty()) {
						tree = trees.poll();
						section.energy += tree.age / 2;
					}
					break;
				}
				
				section.energy -= tree.age;
				tree.age++;
				section.trees.add(tree);
			}
		}
	}
	
	static void fall() {
		ArrayList<Pos> propagationPosList = new ArrayList<>();
		ArrayList<Integer> propCountList = new ArrayList<>();
		for(Pos pos : treePosList) {
			Section section = land[pos.x][pos.y];
			
			if(section.trees.isEmpty())
				continue;
			
			int count = 0;
			for(Tree tree : section.trees) {
				if(tree.age % 5 == 0)
					count++;
			}
			if(count > 0) {
				propagationPosList.add(pos);
				propCountList.add(count);
			}
		}
		
		for(int i = 0; i < propagationPosList.size(); i++) {
			Pos pos = propagationPosList.get(i);
			int count = propCountList.get(i);
			
			for(int j = 0; j < moveDir.length; j++) {
				int nextX = pos.x + moveDir[j][0];
				int nextY = pos.y + moveDir[j][1];
				
				if(!in(nextX, nextY))
					continue;
				
				treeCount += count;
				
				Pos nextPos = new Pos(nextX, nextY);
				if(!treePosList.contains(nextPos))
					treePosList.add(nextPos);
				
				for(int k = 0; k < count; k++)
					land[nextX][nextY].trees.add(new Tree(nextPos, 1));		
			}
		}
	}
	
	static boolean in(int x, int y) {
		if(0 <= x && x < N && 0 <= y && y < N)
			return true;
		return false;
	}
	
	static void winter() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				land[i][j].energy += land[i][j].added;
			}
		}
	}
}

class Section {
	PriorityQueue<Tree> trees = new PriorityQueue<>();
	int energy;
	int added;
	
	public Section(int added) {
		energy = 5;
		this.added = added;
	}
}

class Tree implements Comparable<Tree> {
	Pos pos;
	int age;
	
	public Tree(Pos pos, int age) {
		this.pos = pos;
		this.age = age;
	}

	@Override
	public int compareTo(Tree o) {
		return Integer.compare(this.age, o.age);
	}
}

class Pos{
	int x;
	int y;
	
	public Pos(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	@Override
	public boolean equals(Object o) {
		Pos ano = (Pos)o;
		if(this.x == ano.x && this.y == ano.y)
			return true;
		else
			return false;
	}

	@Override
	public int hashCode() {
		return Objects.hash(x, y);
	}
	
	@Override
	public String toString() {
		return "(" + x + ", " + y + ")";
	}
}