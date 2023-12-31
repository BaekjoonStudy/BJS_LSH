#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int v, e, k;
vector<pair<int, int>> graph[20001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 가중치, 노드 순
int table[20001];

void func(int k) { // 다익스트라
	table[k] = 0;
	pq.push({ 0, k });

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
			pq.push({ table[next.second], next.second });
		}
	}
	 
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie();

	cin >> v >> e;
	cin >> k;
	for (int i = 0; i < e; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		graph[u].push_back({ w,v });
		// graph[v].push_back({ w,u });
	}

	 fill(&table[1], &table[1] + v, 1e7);

	func(k);

	for (int i = 1; i <= v; i++) {
		if (table[i] == 1e7)
			cout << "INF\n";
		else
			cout << table[i] << "\n";
	}
	

	return 0;
}
