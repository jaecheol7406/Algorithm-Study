#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;

int N, K;
int inputs[50];
int nums[4][20]; // 각 변의 숫자를 담음
vector<int> cands;

void Init() {
	memset(inputs, 0, 50);
	for (int i = 0; i < 4; i++) {
		memset(nums[i], 0, 10);
	}
	cands.clear();
}

void Input() {
	scanf("%d %d\n", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%1x", &inputs[i]);
	}
}

bool cmp(int a, int b) {
	return a > b;
}

void Print() {
	for (int i = 0; i < N; i++) {
		printf("%d ", inputs[i]);
	}
	cout << endl;
}

int main() {
	int T;
	scanf("%d\n", &T);

	for (int t_case = 1; t_case <= T; t_case++) {
		printf("#%d ", t_case);

		Init();
		Input();
		
		for (int c = 0; c < N/4; c++) {
			// 섞어주기
			inputs[N + c] = inputs[c];
			inputs[c] = 0;

			/*cout << "숫자들: ";
			for (int i = c + 1; i < N + c + 1; i++) {
				cout << inputs[i] << " ";
			}
			cout << endl;*/

			int idx = c + 1;
			for (int j = 0; j < 4; j++) {
				int colIdx = 0;
				
				for (int i = 0; i < N/4; i++) {
					nums[j][i] = inputs[idx];
					// printf("nums[%d][%d] = inputs[%d]\n", j, i, idx);
					idx++;
				}
			}

			/*for (int i = 0; i < 4; i++) {
				for (int j = 0; j < N / 4; j++) {
					cout << nums[i][j] << " ";
				}
				cout << endl;
			}*/
			

			// 16진수 -> 10진수 계산해 cands 벡터에 넣고 내림차순 정렬
			for (int i = 0; i < 4; i++) {
				int bojeong = 1;
				int tmp = 0;
				for (int j = (N / 4) - 1; j >= 0; j--) {
					tmp += nums[i][j] * bojeong;
					// cout << bojeong << "*" << nums[i][j] << "를 더한다" << endl;
					bojeong *= 16;
				}
				cands.push_back(tmp);
			}
		}
		sort(cands.begin(), cands.end(), cmp);

		/*cout << "최종 숫자들: ";
		for (int i = 0; i < cands.size(); i++) {
			cout << cands[i] << " ";
		}
		cout << endl;*/

		int answer;
		int rank = 1;

		int i = 1;
		while (rank != K) {
			answer = cands[i - 1];
			// cout << rank << "번째로 큰 수: " << answer << endl;

			if (cands[i - 1] != cands[i]) {
				// cout << cands[i - 1] << " != " << cands[i] << endl;
				rank++;
			}
			
			i++;
		}
		answer = cands[i - 1];
		
		cout << answer << endl;

	}

	return 0;
}