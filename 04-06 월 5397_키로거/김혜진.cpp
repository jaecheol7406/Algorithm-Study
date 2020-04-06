/*
function call: main �Լ� �ϳ�

���� �� ��(left, right)�� ����� Ŀ���� ������ left, Ŀ���� �������� right�� ��´�.
<�� �Է¹����� left�� �� �� ��Ҹ� right�� �� �ڿ� �ִ´�. (�� left.size() > 0 �� ��)
>�� �Է¹����� right�� �� �� ��Ҹ� left�� �� �ڿ� �ִ´�. (�� right.size() > 0 �� ��)
-�� �Է¹����� left�� �� �� ��Ҹ� �����Ѵ�. (�� left.size() > 0 �� ��)
����� ���� right ���͸� �Ųٷ� ������ ����, left�� right�� ������� ����Ѵ�.
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