#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

void bfs(int A, int B, int visited[]) {
	queue<pair<int, string>> queue;
	queue.push({ A, "" });
	visited[A] = 1;

	while (!queue.empty()) {
		int num = queue.front().first;
		string command = queue.front().second;
		queue.pop();

		if (num == B) {
			cout << command << "\n";
			return;
		}

		int tmp;
		// D 명령어
		tmp = (num * 2) % 10000;
		if (visited[tmp] == 0) {
			visited[tmp] = 1;
			queue.push({ tmp, command + "D" });
		}
		// S 명령어
		tmp = (num - 1) < 0 ? 9999 : num - 1;
		if (visited[tmp] == 0) {
			visited[tmp] = 1;
			queue.push({ tmp, command + "S" });
		}
		// L 명령어
		tmp = (num % 1000) * 10 + num / 1000;
		if (visited[tmp] == 0) {
			visited[tmp] = 1;
			queue.push({ tmp, command + "L" });
		}
		// R 명령어
		tmp = (num % 10) * 1000 + num / 10;
		if (visited[tmp] == 0) {
			visited[tmp] = 1;
			queue.push({ tmp, command + "R" });
		}
	}
}
int main()
{
	ios::sync_with_stdio;
	cin.tie(0);
	
	int T;
	cin >> T;

	while (T--) {
		int A, B;
		cin >> A >> B;
		int visited[10000] = { 0 };
		bfs(A, B, visited);
	}

	return 0;
}
