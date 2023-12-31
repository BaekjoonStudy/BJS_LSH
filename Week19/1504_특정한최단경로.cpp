#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, e, v1, v2;
vector<pair<int, int>> graph[801];
vector<int> table(801, 1e7), table_s(801, 1e7), table_v1(801, 1e7), table_v2(801, 1e7);
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void func(int s) { // 다익스트라
	pq = priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>();
	table[s] = 0;
	pq.push({ 0,s });

	while (!pq.empty()) {
		int cur = pq.top().second;
		int weight = pq.top().first;
		pq.pop();

		if (table[cur] != weight)
			continue;

		for (auto next : graph[cur]) {
			if (table[cur] + next.first >= table[next.second])
				continue;
			table[next.second] = table[cur] + next.first;
			pq.push({ table[next.second],next.second });
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie();

	cin >> n >> e;
	for (int i = 0; i < e; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({ c,b });
		graph[b].push_back({ c,a });
	}
	cin >> v1 >> v2;

	func(1);
	table_s = table;
	fill(&table[1], &table[1] + n, 1e7);
	/*
	for (int i = 1; i <= n; i++) {
		cout << table_s[i] << " ";
	}
	cout << "\n";
	*/

	func(v1);
	table_v1 = table;
	fill(&table[1], &table[1] + n, 1e7);
	/*
	for (int i = 1; i <= n; i++) {
		cout << table_v1[i] << " ";
	}
	cout << "\n";
	*/

	func(v2);
	table_v2 = table;
	/*
	for (int i = 1; i <= n; i++) {
		cout << table[i] << " ";
	}
	cout << "\n";
	*/
	
	if (table_s[v1] == 1e7 || table_s[v2] == 1e7 || table_v1[v2] == 1e7 || table_v1[n] == 1e7 || table_v2[n] == 1e7) {
		// 1번 노드가 v1 or v2와 연결안된경우
		// v1, v2 서로가 연결안된경우
		// n번 노드가 v1 or v2와 연결안된경우
		cout << -1 << "\n";
		return 0;
	}

	int tmp1 = table_s[v1] + table_v1[v2] + table_v2[n]; // 1 - v1 - v2 - n
	int tmp2 = table_s[v2] + table_v2[v1] + table_v1[n]; // 1 - v2 - v1 - n
	cout << min(tmp1, tmp2) << "\n";

	return 0;
}
