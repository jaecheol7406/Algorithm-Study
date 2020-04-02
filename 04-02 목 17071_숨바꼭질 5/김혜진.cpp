#include <iostream>
#include <queue>
using namespace std;

struct Info {
	int n;
	int k;
	int t;
};

int n, k;
queue<Info> q;
int tmpN, tmpK, tmpT;

int main() {

	scanf("%d %d", &n, &k);
	q.push(Info{ n, k, 0 });

	int result = 500000;
	while (!q.empty()) {
		Info thisInfo = q.front();
		q.pop();
		// cout << thisInfo.n << ", " << thisInfo.k << ", " << thisInfo.t << endl;

		if (thisInfo.n == thisInfo.k) {
			result = thisInfo.t;
			break;
		}

		if (thisInfo.n > 500000 || thisInfo.k > 500000) break;

		tmpK = thisInfo.k + (thisInfo.t + 1);
		tmpT = thisInfo.t + 1;

		tmpN = thisInfo.n - 1;
		if (tmpN >= 0) {
			q.push(Info{ tmpN, tmpK, tmpT });
		}
		
		tmpN = thisInfo.n + 1;
		q.push(Info{ tmpN, tmpK, tmpT });

		tmpN = thisInfo.n * 2;
		q.push(Info{ tmpN, tmpK, tmpT });

	}
	if (result == 500000) cout << -1;
	else cout << result;

	return 0;
}