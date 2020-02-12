import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;
import java.util.Queue;
import java.util.Scanner;
/* 
 * 17472_다리 만들기 2
 */
public class Main {
	public static final int[][] moveDir = new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // 동, 서, 남, 북
	
	static int N, M;
	static int[][] map;
	static boolean[][] visit;
	static List<List<Pos>> islands = new ArrayList<>();
	
	static int r = 2;
	static List<Relation> relations = new ArrayList<>();
	
	static int resultMin = Integer.MAX_VALUE;
	
	public static void main(String[] args) {
		input();
		solve();
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		map = new int[N][M];
		visit = new boolean[N][M];
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++)
				map[i][j] = sc.nextInt();
		}
		sc.close();
	}
	
	static void solve() {
		findIsland();
		findRelation();
		calcResultMin();
		// printRelation();

		if(resultMin == Integer.MAX_VALUE)
			resultMin = -1;
		
		System.out.println(resultMin);
	}
	
	static void findIsland() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				if(!visit[i][j] && map[i][j] == 1)
					bfsForIsland(i, j); // 섬 1개
			}
		}
	}
	
	static void bfsForIsland(int x, int y) {
		List<Pos> poss = new ArrayList<>();
		
		Queue<Pos> q = new LinkedList<>();
		q.add(new Pos(x, y));
		
		while(!q.isEmpty()) {
			Pos now = q.poll();
			visit[now.x][now.y] = true;
			poss.add(now);
			
			for(int i = 0; i < 4; i++) {
				int nextX = now.x + moveDir[i][0];
				int nextY = now.y + moveDir[i][1];
				Pos next = new Pos(nextX, nextY);
				
				if(!(0 <= nextX && nextX < N && 0 <= nextY && nextY < M))
					continue;
				
				if(visit[nextX][nextY] || map[nextX][nextY] == 0)
					continue;
				
				visit[nextX][nextY] = true;
				q.add(next);
			}
		}
		
		islands.add(poss);
	}
	
	static void findRelation() {
		dfsForRelation(new boolean[islands.size()], new int[2], 0, 0);
	}
	
	static void dfsForRelation(boolean[] check, int[] re, int start, int idx) {
		if(idx == 2) {
			int bridgeLen = calcBridgeLen(re[0], re[1]);
			if(bridgeLen != -1)
				relations.add(new Relation(re[0], re[1], bridgeLen));
			return;
		}
		
		for(int i = start; i < islands.size(); i++) {
			if(!check[i]) {
				check[i] = true;
				re[idx] = i;
				dfsForRelation(check, re, i + 1, idx + 1);
				check[i] = false;
			}
		}
	}
	
	// 두 섬 사이의 최소 다리 길이 return, 다리 세울 수 없으면 -1 return
	static int calcBridgeLen(int island1, int island2) {
		int minLen = Integer.max(N, M);
		List<Pos> land1 = islands.get(island1);
		List<Pos> land2 = islands.get(island2);
		for(Pos pos1 : land1) {
			for(Pos pos2 : land2) {
				int bridge = makeBridge(pos1, pos2);
				if(bridge == 0)
					continue;
				
				if(bridge < minLen)
					minLen = bridge;
			}
		}
		
		if(minLen == Integer.max(N, M))
			minLen = -1;
		
		return minLen;
	}
	
	static int makeBridge(Pos pos1, Pos pos2) {
		int len = 0;
		
		if(pos1.x == pos2.x) {
			if(Math.abs(pos1.y - pos2.y) <= 2)
				return 0;
			
			int x = pos1.x;
			int start = 0, end = 0;
			
			if(pos1.y < pos2.y) {
				start = pos1.y;
				end = pos2.y;
			} else {
				start = pos2.y;
				end = pos1.y;
			}
			
			while(++start != end) {
				len++;
				if(map[x][start] != 0)
					return 0;
			}
			
			return len;
			
		} else if(pos1.y == pos2.y) {
			if(Math.abs(pos1.x - pos2.x) <= 2)
				return 0;
			
			int y = pos1.y;
			int start = 0, end = 0;
			
			if(pos1.x < pos2.x) {
				start = pos1.x;
				end = pos2.x;
			} else {
				start = pos2.x;
				end = pos1.x;
			}
			
			while(++start != end) {
				len++;
				if(map[start][y] != 0)
					return 0;
			}
			
			return len;
			
		} else
			return 0;
	}
	
	static void calcResultMin() {
		for(int r = 0; r <= relations.size() / 2; r++) {
			dfsForResult(new boolean[relations.size()], new int[r], 0, 0, r);
		}
	}
	
	static void dfsForResult(boolean[] check, int[] re, int start, int idx, int r) {
		if(idx == r) {
			int[] re2 = new int[relations.size() - r];
			int re2Idx = 0;
			for(int i = 0; i < relations.size(); i++) {
				if(!check[i])
					re2[re2Idx++] = i;
			}
			
			int len = totalLen(re);
			int len2 = totalLen(re2);
			if(len != 0)
				resultMin = Integer.min(resultMin, len);
			if(relations.size() != r * 2 && len2 != 0)
				resultMin = Integer.min(resultMin, len2);
			
			return;
		}
		
		for(int i = start; i < relations.size(); i++) {
			if(!check[i]) {
				check[i] = true;
				re[idx] = i;
				dfsForResult(check, re, i + 1, idx + 1, r);
				check[i] = false;
			}
		}
	}
	
	static int totalLen(int[] relationIdxs) {
		boolean[] check = new boolean[islands.size()];
		boolean ok = false;
		for(int i = 0; i < relationIdxs.length; i++) {
			Relation re1 = relations.get(relationIdxs[i]);
			check[re1.island1] = true;
			check[re1.island2] = true;

			ok = false;
			for(int j = 0; j < relationIdxs.length; j++) {
				if(i == j)
					continue;
				Relation re2 = relations.get(relationIdxs[j]);
				if(re1.island1 == re2.island1 || re1.island1 == re2.island2 
						|| re1.island2 == re2.island1 || re1.island2 == re2.island2) {
					ok = true;
					break;
				}
			}
			
			if(!ok)
				break;
		}
		
		if(ok && allIncluded(check) || !ok && allIncluded(check) && relationIdxs.length == 1) {
			int len = 0;
			for(int i = 0; i < relationIdxs.length; i++)
				len += relations.get(relationIdxs[i]).bridgeLen;
			return len;
		}
		
		return 0;
	}
	static boolean allIncluded(boolean[] check) {
		for(int i = 0; i < check.length; i++) {
			if(!check[i])
				return false;
		}
		return true;
	}
	
	static void printIsland() {
		for(List<Pos> poss : islands) {
			for(Pos pos : poss)
				System.out.println(pos.x + " " + pos.y);
			System.out.println();
		}
	}
	
	static void printRelation() {
		for(int i = 0; i < relations.size(); i++) {
			Relation re = relations.get(i);
			System.out.println(re.island1 + " " + re.island2 + " " + re.bridgeLen);
		}
	}
}

class Relation {
	int island1;
	int island2;
	int bridgeLen;
	
	public Relation(int island1, int island2, int bridgeLen) {
		this.island1 = island1;
		this.island2 = island2;
		this.bridgeLen = bridgeLen;
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
}