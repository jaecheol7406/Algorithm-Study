/*
BOJ 5397번: 키로거
문제 풀이 : 결과 문자열을 저장할 ans stack과 커서 이동 시 문자열을 임시 저장 하는 tmp stack을 사용한다.
			'<'입력시 ans.top을 tmp에 옮김
			'>'입력시 tmp.top을 ans에 옮김
			'-'입력시 ans.top을 pop
			tmp에 문자열이 남아있을 수 있으니 ans에 옮겨서 거꾸로 출력한다.

처음에 풀었던 틀린 풀이 : 한 개의 벡터를 사용해서 erase와 insert를 사용해서 풀었는데 시간초과 발생.
						  벡터의 erase와 insert의 시간 복잡도는 O(N)이라서, O(N^2)의 시간이 소요되므로 시간초과.

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