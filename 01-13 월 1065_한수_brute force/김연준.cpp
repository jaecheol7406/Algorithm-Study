#include <iostream> //한글 깨짐 테스트
#include <vector>
using namespace std;
void sol1(int N) {
	int result = 0;
	for (int i = 1; i <= N; i++) {
		if (1 <= i && i <= 99) { //한자리, 두자리인 경우
			result++;
		}
		else if (i == 1000) {
			break;
		}
		else {
			vector<int> list;
			int temp = i;
			while (temp != 0) {
				list.push_back(temp % 10);
				temp = temp / 10;
			}
			int sub1 = list[0] - list[1];
			int sub2 = list[1] - list[2];
			if (sub1 == sub2)
				result++;
		}

	}
	cout << result << endl;
}
/*void sol2(int N) {
	int result;
	for (int i = 1; i <= N; i++) {
		vector<int> list;
		int tmp = i;
		while (tmp != 0) {
			list.push_back(tmp % 10);
			tmp /= 10;
		}
		if (list.size() >= 3) {
			for(int i=0;i<list)
		}
		else {
			result++;
		}
	}
}*/
int main() {
	cout << "연준" << '\n';
	int N;
	cin >> N;
	sol1(N);

	return 0;
}