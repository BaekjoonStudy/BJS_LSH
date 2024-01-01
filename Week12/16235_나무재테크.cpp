#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K, land[10][10], food[10][10]; // land : 땅에 저장된 양분, food : 겨울에 추가할 양분 양
vector<int> age[10][10]; // 나무 나이
vector<pair<int, pair<int, int>>> dead_tree; // 나이, x좌표, y좌표
vector<pair<int, int>> tree5; // 나이가 5의 배수인 나무 좌표
pair<int, int> dir[8] = { {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1} };

void spring() {
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			if (age[x][y].size() == 1) {
				if (age[x][y][0] <= land[x][y]) { // 양분을 먹을 수 있으면
					land[x][y] -= age[x][y][0]; // 양분 먹고
					age[x][y][0]++; // 나이 먹음
					if (age[x][y][0] % 5 == 0) // 나이가 5의 배수이면
						tree5.push_back({ x,y }); // 추가
				}
				else { // 양분을 먹지 못하면
					dead_tree.push_back({ age[x][y][0], {x, y} }); // 죽었다고 표시하고
					age[x][y].clear(); // age 벡터에서 제거
				}
			}
			else if (age[x][y].size() > 1) {
				sort(age[x][y].begin(), age[x][y].end()); // 나이가 어린 나무부터 양분을 먹기 위해 sorting
				vector<int> tmp;
				for (int i = 0; i < age[x][y].size(); i++) {
					if (age[x][y][i] <= land[x][y]) { // 양분을 먹을 수 있으면
						land[x][y] -= age[x][y][i]; // 양분 먹고
						tmp.push_back(++age[x][y][i]); // 나이먹음
						if (age[x][y][i] % 5 == 0) // 나이가 5의 배수이면
							tree5.push_back({ x,y }); // 추가
					}
					else {
						dead_tree.push_back({ age[x][y][i], {x, y} }); // 죽었다고 표시하고
					}
				}
				// age 벡터에서 죽은 나무 제거
				age[x][y].clear();
				for (int j = 0; j < tmp.size(); j++) {
					age[x][y].push_back(tmp[j]);
				}
			}
		}
	}
}

void summer() {
	for (int i = 0; i < dead_tree.size(); i++) {
		int n = dead_tree[i].first, x = dead_tree[i].second.first, y = dead_tree[i].second.second;
		land[x][y] += (n / 2); // 양분 업데이트
	}
	dead_tree.clear();
}

void autumn() {
	for (int i = 0; i < tree5.size(); i++) {
		for (int j = 0; j < 8; j++) {
			int tx = tree5[i].first + dir[j].first, ty = tree5[i].second + dir[j].second;
			if (tx >= 0 && tx < N && ty >= 0 && ty < N) { // 땅을 벗어나지 않으면
				age[tx][ty].push_back(1); // 나무 나이 업데이트
			}
		}
	}
	tree5.clear();
}

void winter() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			land[i][j] += food[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			land[i][j] = 5;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> food[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		age[x - 1][y - 1].push_back(z); // 0,0부터 시작하기위함
	}

	while (K--) {
		spring();
		summer();
		autumn();
		winter();
	}

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cnt += age[i][j].size();
		}
	}
	cout << cnt << "\n";

	return 0;
}
