/*
BOJ 5397��: Ű�ΰ�
���� Ǯ�� : ��� ���ڿ��� ������ ans stack�� Ŀ�� �̵� �� ���ڿ��� �ӽ� ���� �ϴ� tmp stack�� ����Ѵ�.
			'<'�Է½� ans.top�� tmp�� �ű�
			'>'�Է½� tmp.top�� ans�� �ű�
			'-'�Է½� ans.top�� pop
			tmp�� ���ڿ��� �������� �� ������ ans�� �Űܼ� �Ųٷ� ����Ѵ�.

ó���� Ǯ���� Ʋ�� Ǯ�� : �� ���� ���͸� ����ؼ� erase�� insert�� ����ؼ� Ǯ���µ� �ð��ʰ� �߻�.
						  ������ erase�� insert�� �ð� ���⵵�� O(N)�̶�, O(N^2)�� �ð��� �ҿ�ǹǷ� �ð��ʰ�.

*/
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#define endl '\n'
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int N;
	cin >> N;
	while (N--) {
		stack<char> ans;
		stack<char> tmp;
		string input;
		cin >> input;
		for (int i = 0; i < input.size(); i++) {
			if (input[i] == '<') {
				if (ans.size() != 0) {
					tmp.push(ans.top());
					ans.pop();
				}
			}
			else if (input[i] == '>') {
				if (tmp.size() != 0) {
					ans.push(tmp.top());
					tmp.pop();
				}
			}
			else if(input[i]=='-'){
				if (ans.size() != 0) {
					ans.pop();
				}
			}
			else {
				ans.push(input[i]);
			}
		}
		string res = "";
		while (!tmp.empty()) {
			ans.push(tmp.top());
			tmp.pop();
		}
		while (!ans.empty()) {
			res += ans.top();
			ans.pop();
		}
		reverse(res.begin(), res.end());
		cout << res << endl;

	}

}