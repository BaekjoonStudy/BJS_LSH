#include <iostream>
#include <vector>

using namespace std;

int N, x, y, d, g, map[101][101] = { 0 }, min_y = 100, min_x = 100, max_y = 0, max_x = 0;
pair<int, int> dir[4] = { {0,1},{-1,0},{0,-1},{1,0} };

void check() { // 크기가 1×1인 정사각형의 네 꼭짓점이 모두 드래곤 커브의 일부인 정사각형의 개수 리턴
	int cnt = 0;
	for (int i = min_y; i < max_y; i++) {
		for (int j = min_x; j < max_x; j++) {
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1)
				cnt++;
		}
	}

	cout << cnt << "\n";
}

// 우 상 좌 하 순
// 우 -> 상, 상 -> 좌, 좌 -> 하, 하 -> 우
void dragon(int y, int x, int d, int g) {
	vector<int> curve;
	pair<int, int> last = { y,x };
	map[y][x] = 1;
	min_y = min(min_y, y), max_y = max(max_y, y), min_x = min(min_x, x), max_x = max(max_x, x);
	for (int i = 0; i <= g; i++) {
		if (i == 0) {
			curve.push_back(d);
			last = { last.first + dir[d].first, last.second + dir[d].second };
			map[last.first][last.second] = 1;
			min_y = min(min_y, last.first), max_y = max(max_y, last.first), min_x = min(min_x, last.second), max_x = max(max_x, last.second);
		}
		else {
			for (int j = curve.size() - 1; j >= 0; j--) {
				d = (curve[j] + 1 > 3) ? 0 : curve[j] + 1;
				curve.push_back(d);
				last = { last.first + dir[d].first, last.second + dir[d].second };
				map[last.first][last.second] = 1;
				min_y = min(min_y, last.first), max_y = max(max_y, last.first), min_x = min(min_x, last.second), max_x = max(max_x, last.second);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> d >> g;
		dragon(y, x, d, g);
	}
	check();

	return 0;
}
