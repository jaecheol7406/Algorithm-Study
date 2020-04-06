/*
function call: main 함수 하나

벡터 두 개(left, right)를 만들어 커서의 왼쪽은 left, 커서의 오른쪽은 right에 담는다.
<를 입력받으면 left의 맨 뒤 요소를 right의 맨 뒤에 넣는다. (단 left.size() > 0 일 때)
>를 입력받으면 right의 맨 뒤 요소를 left의 맨 뒤에 넣는다. (단 right.size() > 0 일 때)
-를 입력받으면 left의 맨 뒤 요소를 삭제한다. (단 left.size() > 0 일 때)
출력할 때는 right 벡터를 거꾸로 뒤집은 다음, left와 right를 순서대로 출력한다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector<char> leftVec;
vector<char> rightVec;

int main() {

	int N;
	scanf("%d\n", &N);

	string input;
	for (int i = 0; i < N; i++) {
		cin >> input;
		leftVec.clear();
		rightVec.clear();

		for (int j = 0; j < input.length(); j++) {
			if (input[j] == '<') {
				if (leftVec.size() > 0) {
					rightVec.push_back(leftVec[leftVec.size() - 1]);
					leftVec.erase(leftVec.begin() + leftVec.size() - 1);
				}
			}
			else if (input[j] == '>') {
				if (rightVec.size() > 0) {
					leftVec.push_back(rightVec[rightVec.size() - 1]);
					rightVec.erase(rightVec.begin() + rightVec.size() - 1);
				}
			}
			else if (input[j] == '-') {
				if (leftVec.size() > 0) {
					leftVec.erase(leftVec.begin() + leftVec.size() - 1);
				}
			}
			else {
				leftVec.push_back(input[j]);
			}
		}
		
		for (int j = 0; j < leftVec.size(); j++) {
			cout << leftVec[j];
		}
		reverse(rightVec.begin(), rightVec.end());
		for (int j = 0; j < rightVec.size(); j++) {
			cout << rightVec[j];
		}
		cout << endl;
	}

	return 0;
}