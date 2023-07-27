#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int deque[100001];
int head = 0, tail = 0;

void push_back(int x) {
	deque[tail++] = x; // 0번째 인덱스부터 원소 넣어줌
}

void pop_front() {
	cout << deque[head++];
}

void pop_back() {
	cout << deque[--tail];
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T, n, error, rev;
	cin >> T;
	string order, str, saveNum;

	for (int i = 0; i < T; i++) {
		cin >> order;
		cin >> n;
		cin >> str;
		head = 0;
		tail = 0;

		for (int j = 1; j < str.length(); j++) {
			if (n != 0) {
				if (str[j] == ',' || str[j] == ']') {
					push_back(stoi(saveNum));
					saveNum = "";
				}
				else {
					saveNum = saveNum + str[j];
				}
			}
		}
		error = 0;
		rev = 1;

		for (int j = 0; j < order.length(); j++) {
			if (order[j] == 'R')
				rev *= -1;
			else {
				if (head != tail) { // 덱이 비어있지 않을 때
					if (rev == -1)
						tail--;
					else
						head++;
				}
				else { // 덱이 비어있을 때
					error = 1;
					break;
				}
			}
		}

		if (error == 1)
			cout << "error\n";
		else {
			cout << "[";
			if (head == tail)
				cout << "]\n";
			else {
				if (rev == -1) { // 뒤집어졌을때
					for (int j = tail - 1; j > head; j--)
						cout << deque[j] << ",";
					cout << deque[head] << "]\n";
				}
				else {
					for (int j = head; j < tail - 1; j++)
						cout << deque[j] << ",";
					cout << deque[tail - 1] << "]\n";
				}
			}
		}
	}
	return 0;
}
