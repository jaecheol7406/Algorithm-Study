/*
BOJ 1107 : ������


Step1. 0~1000000 �� ä���� ����Ž���Ѵ�.(N�� �ִ밪�� 500000������, 499999�� ��� 9,8�� 0�� ���峵���� 477777���� +��ư�� ������ ��(22222)���� 511111���� -��ư�� �����°�(11111) ������ ����
Step2. �� ä�ο� ���ؼ� �ش� ��ȣ�� �ٷ� �̵� �����ϴٸ� ��ȣ�� ������ �̵��� Ƚ����, 100���� +-�� ������ �̵��� Ƚ���� ���Ͽ� min���� ���Ѵ�.
Step3. �ش� ä�ο��� ��ǥä�α��� ���̸� Step2�� ����� ���Ѵ�.
Step4. ����Ž���� �ϸ鼭 �ּҰ��� ����!!
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, M;
vector<int> broken;
vector<int>::iterator iter;
const int INF = 987654321;
int result = INF;
void Input() {
	cin >> N >> M;
	int num;
	for (int i = 0; i < M; i++) {
		cin >> num;
		broken.push_back(num);
	}
}
int IsPossiblePress(int num) { 
	if (num == 0) {
		iter = find(broken.begin(), broken.end(), 0);
		if (iter == broken.end()) {
			return 1;
		}
		else {
			return -1;
		}
	}
	int cnt = 0;
	while (num != 0) {
		cnt++;
		iter = find(broken.begin(), broken.end(), num%10);
		if (iter != broken.end()) { //���峭 ��ư�� �̶��.
			return -1;
		}
		num /= 10;
	}
	return cnt;
}
int getChannel(int num) {
	int cnt = IsPossiblePress(num);
	if (cnt == -1) { //���峭 ��ư�� ���ԵǾ������Ƿ� ������ +-�θ� ������.
		return abs(num - 100);
	}
	else { //���峭 ��ư�� ���ԵǾ����������Ƿ� ä�ι�ȣ�� ������ ���°Ͱ� +-�� ���°��� ��.
		return min(cnt, abs(num - 100));
	}
}
void Solution() {
	for (int i = 0; i <= 1000000; i++) {
		int move = getChannel(i) + abs(i - N);
		if (result > move)
			result = move;
	}
	cout << result << endl;

}
void Solve() {
	Input();
	Solution();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	
	return 0;
}