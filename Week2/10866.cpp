#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int deque[10001];
int head = 5000, tail = 5000;

void push_front(int x) {
	deque[--head] = x; // 4999 인덱스부터 원소 넣어줌
}

void push_back(int x) {
	deque[tail++] = x; // 5000 인덱스부터 원소 넣어줌
}

void pop_front() {
	if (head == tail) // 덱에 정수가 없는 경우
		cout << -1 << "\n";
	else
		cout << deque[head++] << "\n";
}

void pop_back() {
	if (head == tail) // 덱에 정수가 없는 경우
		cout << -1 << "\n";
	else
		cout << deque[--tail] << "\n";
}

void size() {
	cout << tail - head << "\n";
}

void empty() {
	cout << ((tail - head) ? 0 : 1) << "\n";
}

void front() {
	if (head == tail) // 덱에 정수가 없는 경우
		cout << -1 << "\n";
	else
		cout << deque[head] << "\n";
}

void back() {
	if (head == tail) // 덱에 정수가 없는 경우
		cout << -1 << "\n";
	else
		cout << deque[tail - 1] << "\n";
}

vector<string> split(string input, string delimiter)
{
	vector<string> ret;
	int pos = 0;
	string token = "";
	while ((pos = input.find(delimiter)) != string::npos) // find : 찾는 문자열의 첫번째 인덱스 반환, 찾는 문자열이 없는 경우 npos 반환
	{
		token = input.substr(0, pos);
		ret.push_back(token);
		input.erase(0, pos + delimiter.length());
	}
	ret.push_back(input);
	return ret;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int N;
	cin >> N;
	string str;
	vector<string> command, C;
	for (int i = 0; i <= N; i++) {
		getline(cin, str);
		command.push_back(str);
	}

	for (int i = 1; i < command.size(); i++) { // 두번째 줄부터 시작하기 위함
		if (command[i] == "pop_front")
			pop_front();
		else if (command[i] == "pop_back")
			pop_back();
		else if (command[i] == "size")
			size();
		else if (command[i] == "empty")
			empty();
		else if (command[i] == "front")
			front();
		else if (command[i] == "back")
			back();
		else { // push_back, push_front
			C = split(command[i], " ");
			if (C[0] == "push_back")
				push_back(stoi(C[1])); // stoi : string to integer, string 라이브러리에 포함
			else
				push_front(stoi(C[1]));
		}
	}

	return 0;
}
