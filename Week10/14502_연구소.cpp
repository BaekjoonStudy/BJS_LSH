#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
using namespace std;

int N, M, result = 0;
int map[8][8], visited[8][8];
queue<pair<int, int>> q;
vector<pair<int, int>> virus, safe_area;
int dir[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} }; // 상하좌우

void initialize() { // queue, visited 초기화
	for (auto x : virus)
		q.push(x);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			visited[i][j] = 0;
	}
}

int spread_virus() { // bfs
	int c = 3; // 새로생긴 벽 3개

	while (!q.empty()) {
		int row = q.front().first;
		int col = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) { // 상하좌우
			int row_tmp = row + dir[i][0];
			int col_tmp = col + dir[i][1];

			if (row_tmp >= 0 && row_tmp < N && col_tmp >= 0 && col_tmp < M) { // map을 벗어나지 않고
				if (map[row_tmp][col_tmp] == 0 && visited[row_tmp][col_tmp] == 0) { // 해당 좌표가 안전 영역이며 방문한적 없다면
					q.push({ row_tmp, col_tmp }); // 바이러스로
					visited[row_tmp][col_tmp] = 1;
					c++; // 카운팅
					//cout << i << " : " << row_tmp << "," << col_tmp << " " << c << "\n";
				}
			}

		}
	}
	return c; // 원래 안전 영역이었다가 벽 또는 바이러스가 퍼진 영역의 수
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0)
				safe_area.push_back({ i,j });
			if (map[i][j] == 2)
				virus.push_back({ i,j });
		}
	}

	initialize(); // queue, visited 배열 초기화
	// 방문했다고 표시함으로써 바이러스가 퍼지지 못하게함
	for (int i = 0; i < safe_area.size() - 2; i++) {
		for (int j = i + 1; j < safe_area.size() - 1; j++) {
			for (int k = j + 1; k < safe_area.size(); k++) {
				visited[safe_area[i].first][safe_area[i].second] = 1;
				visited[safe_area[j].first][safe_area[j].second] = 1;
				visited[safe_area[k].first][safe_area[k].second] = 1;
				int tmp = safe_area.size() - spread_virus();
				//cout << safe_area.size() << " " << tmp << "\n";
				result = (result > tmp) ? result : tmp;
				initialize(); // queue, visited 배열 초기화
			}
		}
	}

	cout << result << "\n";

	return 0;
}
