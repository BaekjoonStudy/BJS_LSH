#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int m, n;
vector<pair<int, pair<int, int>>> graph; // {거리, {x집, y집}}
int sum = 0;
int group[200001];

int find(int x) { // find
	if (group[x] == x)
		return x;
	else
		return group[x] = find(group[x]);
}

bool is_diff_group(int x, int y) { // union
	x = find(x);
	y = find(y);

	if (x == y)
		return false;

	group[x] = group[y];

	return true;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	while (cin >> m >> n) {
		// 초기화
		sum = 0;
		graph.clear();

		if (m == 0 && n == 0)
			break;
		while (n--) {
			int x, y, z;
			cin >> x >> y >> z;
			sum += z;
			graph.push_back({ z,{x,y} });
		}

		sort(graph.begin(), graph.end()); // 크루스칼을 위해 정렬
		
		for (int i = 0; i < m; i++) {
			group[i] = i;
		}

		int result = 0;
		for (int i = 0; i < graph.size(); i++) { // 크루스칼
			if (is_diff_group(graph[i].second.first, graph[i].second.second))
				result += graph[i].first;
		}
		cout << sum - result << "\n";
	}
	
	return 0;
}
