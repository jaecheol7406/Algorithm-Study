/*
BOJ 2231��: ������
���� ���� : ���Ʈ����
���� Ǯ�� : ������ ��� ��, ������ ����ؾ��ϴ� ���� string���� ��ȯ�ϰ� �� �ڸ����� �����ش�.
			
			������, int�ڷ����� �����ϰ� ����ϴ� �� ���� �ξ� ������.
*/
#include <iostream>
#include <string>
using namespace std;
int N;
int answer = 0;
int main() {
	cin >> N;
	string tmp;
	int val;
	for (int i = 1; i < N; i++) {
		val = i;
		tmp = to_string(i);
		for (int j = 0; j < tmp.size(); j++) {
			val += tmp[j] - '0';
		}
		if (val == N) {
			answer = i;
			break;
		}


	}
	cout << answer << endl;
	return 0;
}