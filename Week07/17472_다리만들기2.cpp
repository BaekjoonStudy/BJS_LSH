#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int map[10][10] = { 0 }; 
int visited[10][10] = { 0 };
int island[10][10] = { 0 };
int island_count = 0;
vector<pair<int, int>> land; // <x좌표, y좌표>
queue<pair<int, int>> q; // <x좌표, y좌표>
vector<pair<int, pair<int, int>>> edge; // <거리, start island, end island>
int parent[7];

void make_island() { // bfs로 섬 만듦
	for (int i = 0; i < land.size(); i++) {
		int x = land[i].first;
		int y = land[i].second;
		if (visited[x][y] == 1)
			continue;

		q.push({ x,y });
		visited[x][y] = 1;
		island[x][y] = ++island_count;

		while (!q.empty()) {
			x = q.front().first;
			y = q.front().second;
			q.pop();

			// 상하좌우를 확인하여 땅이 있다면 같은 섬으로 묶음
			if ((y - 1) >= 0 && visited[x][y - 1] == 0 && map[x][y - 1] == 1) { // 상
				q.push({ x, y - 1 });
				visited[x][y - 1] = 1;
				island[x][y - 1] = island_count;
			}
			if ((y + 1) < M && visited[x][y + 1] == 0 && map[x][y + 1] == 1) { // 하
				q.push({ x, y + 1 });
				visited[x][y + 1] = 1;
				island[x][y + 1] = island_count;
			}
			if ((x - 1) >= 0 && visited[x - 1][y] == 0 && map[x - 1][y] == 1) { // 좌
				q.push({ x - 1, y });
				visited[x - 1][y] = 1;
				island[x - 1][y] = island_count;
			}
			if ((x + 1) < N && visited[x + 1][y] == 0 && map[x + 1][y] == 1) { // 우
				q.push({ x + 1, y });
				visited[x + 1][y] = 1;
				island[x + 1][y] = island_count;
			}
		}
	}
}

void make_edge(int x, int y, int dir) { 
	int len = 0;
	int start = island[x][y];

	while (true) {
		if (dir == 0) // 상
			y--;
		else if (dir == 1) // 하
			y++;
		else if (dir == 2) // 좌
			x--;
		else if (dir == 3) // 우
			x++;

		if (x >= 0 && x < N && y >= 0 && y < M) {
			if (map[x][y] == 0) // 바다라면
				len++;
			else if (map[x][y] == 1 && len >= 2 && start != island[x][y]) { // 다른 섬 땅에 도달했고 간선길이가 2 이상이라면
				edge.push_back({ len,{start,island[x][y]} });
				break;
			}
			else // 같은 섬 땅이거나 간선길이가 2보다 짧다면
				break;
		}
		else
			break;
	}
}

int find(int a)
{
	if (parent[a] == a)
		return a;
	return parent[a] = find(parent[a]);
}

bool is_diff_parent(int a, int b)
{
	a = find(a);
	b = find(b);
	if (a == b)
		return false;
	if (a < b) // 항상 작은 숫자의 parent로 union
		parent[b] = a;
	else
		parent[a] = b;

	return true;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1)
				land.push_back({ i,j });
		}
	}

	make_island(); // 섬을 만듦

	for (int i = 0; i < land.size(); i++) { // 모든 땅에 대해서
		for (int j = 0; j < 4; j++) { // 4방향으로 탐색
			make_edge(land[i].first, land[i].second, j);
		}
	}
	
	sort(edge.begin(), edge.end()); // 크루스칼 알고리즘을 위해 정렬

	for (int i = 1; i <= island_count; i++)
		parent[i] = i;

	int result = 0;
	for (int i = 0; i < edge.size(); i++) { // 모든 간선에 대해 탐색
		if (is_diff_parent(edge[i].second.first, edge[i].second.second)) // union-find
			result += edge[i].first;
	}

	for (int i = 1; i <= island_count; i++) // 항상 숫자가 작은 parent의 union 했으므로 모든 섬을 연결했다면 모든 섬의 parent는 1임.
	{
		if (find(i) != 1) {
			cout << -1 << "\n";
			return 0;
		}
	}
	cout << result << "\n";
}
