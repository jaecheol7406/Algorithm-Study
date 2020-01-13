/*
BOJ 2309 일곱 난쟁이
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> height_list;
int height_sum = 0;
void input() {
	for (int i = 0; i < 9; i++) {
		int height;
		cin >> height;
		height_list.push_back(height);
		height_sum += height;
	}
}
void solve() {
	for (int i = 0; i < height_list.size() - 1; i++) {
		for (int j = i + 1; j < height_list.size(); j++) {
			if (height_sum - (height_list[i] + height_list[j]) == 100) {
				height_list[i] = -1;
				height_list[j] = -1;
				return;
			}
		}
	}
	return;
}
void print() {
	sort(height_list.begin(), height_list.end());
	for (int i = 2; i < height_list.size(); i++) {
		cout << height_list[i] << endl;
	}
}
int main() {
	input();
	solve();
	print();


	return 0;
}