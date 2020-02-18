#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> len;
vector<int> answer;
int sum;

void Input() {
	for (int i = 0; i < 9; i++) {
		int tmp = 0;
		scanf("%d\n", &tmp);
		len.push_back(tmp);
		sum += tmp;
	}
}

int main() {
	Input();

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (i == j) continue;

			if (sum - (len[i] + len[j]) == 100) {
				for (int z = 0; z < len.size(); z++) {
					if (z == i || z == j) continue;
					answer.push_back(len[z]);
				}

				sort(answer.begin(), answer.end());
				for (int z = 0; z < answer.size(); z++) {
					cout << answer[z] << endl;
				}
				return 0;
			}
		}
	}
	return 0;
}