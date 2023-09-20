#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
using namespace std;

int N, L, R, map[50][50], visited[50][50];
pair<int, int> dir[4] = { {0,-1},{0,1},{-1,0},{1,0} };
vector<pair<int, int>> group;

void bfs(int i, int j) {
	group.clear();
	visited[i][j] = 1;
	queue<pair<int, int>> q;
	q.push({ i,j });
	group.push_back({ i,j });

	while (!q.empty()) {
		int i = q.front().first;
		int j = q.front().second;
		q.pop();
		for (int k = 0; k < 4; k++) {
			if (i + dir[k].first < N && j + dir[k].second < N && i + dir[k].first >= 0 && j + dir[k].second >= 0) { // 범위를 벗어나지 않고
				int diff = abs(map[i][j] - map[i + dir[k].first][j + dir[k].second]);
				if (diff >= L && diff <= R && visited[i + dir[k].first][j + dir[k].second] == 0) { // 조건을 만족하며 방문한적도 없을 때
					q.push({ i + dir[k].first,j + dir[k].second });
					group.push_back({ i + dir[k].first,j + dir[k].second });
					visited[i + dir[k].first][j + dir[k].second] = 1;
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	int day = 0;
	while (true) {
		bool isbool = false;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				visited[i][j] = 0;
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j] != 0)
					continue;
				bfs(i, j);
				if (group.size() > 1) {
					int num = 0;
					for (auto a : group) {
						//cout << a.first << "," << a.second << " : " << map[a.first][a.second] << " ";
						num += map[a.first][a.second];
					}
					num /= group.size();
					for (auto a : group)
						map[a.first][a.second] = num;
					isbool = true; // 인구 이동이 있었는지 
					/*
					cout << "\n";
					for (int i = 0; i < N; i++) {
						for (int j = 0; j < N; j++) {
							cout << map[i][j] << " ";
						}
						cout << "\n";
					}
					*/
				}
			}
		}

		if (isbool == false) { // 인구 이동이 없었다면
			cout << day << "\n";
			break;
		}
		day++;
	}


	return 0;
}
