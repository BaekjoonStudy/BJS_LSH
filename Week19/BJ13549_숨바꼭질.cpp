#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, k, min_ans = 1e7;
int visit[100001];

void func(int s) { // bfs
	queue<pair<int, int>> q; // 위치, 시간
	q.push({ s,0 });
	visit[s] = 1;

	while (!q.empty()) {
		int cur = q.front().first;
		int time = q.front().second;
		q.pop();

		//cout << time << ":" << cur << "\n";
		if (cur == k) {
			cout << time << "\n";
			return;
		}

		if (cur != 0) {
			int tmp = cur;
			while (true) {
				if (tmp * 2 == k) {
					cout << time << "\n";
					return;
				}
				if (tmp > k || tmp * 2 > 100000)
					break;
				tmp *= 2;
				visit[tmp] = 1;
				q.push({ tmp,time });
				//cout << "{" << tmp << "," << time << "}\n";
			}
		}

		int tmp[2] = { cur + 1, cur - 1 };
		for (auto i : tmp) {
			if (i > 100000 || i < 0)
				continue;
			if (visit[i] == 1)
				continue;
			visit[i] = 1;
			q.push({ i,time + 1 });
			//cout << "{" << i << "," << time+1 << "}\n";
		}
	}
		
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie();

	cin >> n >> k;
	func(n);

	return 0;
}
