#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<pair<int, int>> V[2001]; // 간선들을 저장하기 위한 벡터, V[1] = [ { 3, 5 }, { 1, 2 } ] 라면 1번 정점은 2번, 5번 정점과 연결되어있으며 거리는 각각 1, 3
int D_s[2001], D_g[2001], D_h[2001]; // 각각 s, g, h 정점으로부터의 최단 거리를 저장하기 위한 배열

void dijkstra(int start, int d[]) {
	priority_queue<pair<int, int>> pq; // 시간복잡도를 줄이기 위해 우선순위큐를 사용하여 구현한다고함
	pq.push({ 0, start }); // 거리, 정점
	d[start] = 0;

	while (pq.empty() == 0) {
		auto cur = pq.top();
		pq.pop();

		if (d[cur.second] != cur.first)
			continue;
		for (auto next : V[cur.second]) { 
			if (d[next.second] > next.first + d[cur.second]) {
				d[next.second] = next.first + d[cur.second];
				pq.push({ d[next.second], next.second });
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T, n, m, t, s, g, h;
	cin >> T;

	vector<int> destination;
	while (T--) {
		for (int i = 0; i < 2001; i++) {
			V[i].clear();
			D_s[i] = 1e9;
			D_g[i] = 1e9;
			D_h[i] = 1e9;
		}
		destination.clear();

		cin >> n >> m >> t;
		cin >> s >> g >> h;
		while (m--) {
			int a, b, c;
			cin >> a >> b >> c;
			V[a].push_back({ c, b }); 
			V[b].push_back({ c, a });
		}
		while (t--) {
			int x;
			cin >> x;
			destination.push_back(x);
		}
		dijkstra(s, D_s); // s 정점으로부터 다른 정점까지 최단 거리
		dijkstra(g, D_g); // g 정점으로부터 다른 정점까지 최단 거리
		dijkstra(h, D_h); // h 정점으로부터 다른 정점까지 최단 거리
		sort(destination.begin(), destination.end()); // 오름차순으로 출력하기 위함
		for (auto x : destination) {
			if (D_s[x] == D_s[g] + D_g[h] + D_h[x]) // s - g - h - x 
				cout << x << " ";
			else if (D_s[x] == D_s[h] + D_h[g] + D_g[x]) // s - h - g - x 
				cout << x << " ";
		}
		cout << "\n";
	}
	return 0;
}
