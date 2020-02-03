import java.io.*;
public class 테트로미노_숏코딩_DFS {
		static int[][] map, move;
		static int n,m,score=0;
		static int[] dx = {0,0,1,-1};
		static int[] dy = {1,-1,0,0};
		public static void main(String args[]) throws IOException {
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			int i,j;
			String str = "";
			str = br.readLine();
			String[] arr = str.split(" ");
			n = Integer.parseInt(arr[0]);
			m = Integer.parseInt(arr[1]);
			map = new int[n][m];
			move = new int[n][m];
			for(i=0;i<n;i++) {
				str = br.readLine();
				arr = str.split(" ");
				for(j=0;j<m;j++) {
					map[i][j] = Integer.parseInt(arr[j]);
				}
			}
			for(i=0;i<n;i++) {
				for(j=0;j<m;j++) {
					move[i][j]=1;
					dfs(i,j,map[i][j],3);//한개는 이미 골랐으므로 3개만 더 고르면 된다
					move[i][j]=0;
				}
			}
			System.out.println(score);
		}

	static void dfs(int y, int x, int sum, int k) {
		if (k == 0) {
			score = Math.max(score, sum);
			for(int i=0; i<n; i++) for(int j=0; j<m; j++) {
				System.out.print(move[i][j]);
				if(j==m-1) System.out.println();
			}
			System.out.println();
			return;
		}
		for (int i=0; i<4; i++) {
			if (y+dy[i]<0 || y+dy[i]>=n || x+dx[i]<0 || x+dx[i]>=m) continue;
			if (move[y+dy[i]][x+dx[i]] == 1) continue;
			
			move[y+dy[i]][x+dx[i]] = 1;
				dfs(y + dy[i],  x + dx[i],  sum + map[y + dy[i]][x + dx[i]], k - 1);
			if (k == 2)//(y,x)는 k==3번째의 좌표다.. Parameter에 있는 (nx,ny)가  k==2인거고 k-1로 새로들어감
				dfs(y,			x, 			sum + map[y + dy[i]][x + dx[i]], k - 1);
			move[y+dy[i]][x+dx[i]] = 0;
		}
	}
	}

