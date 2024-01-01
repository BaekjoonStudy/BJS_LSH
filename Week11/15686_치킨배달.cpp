#include <iostream>
#include <vector>
using namespace std;

int N, M, map[50][50], chicken_dist = 999999;
vector<pair<int, int>> house, chicken, selected_chicken;

void chicken_distance() {
	int sum = 0;
	for (auto a : house) {
		int min_dist = 100;
		for (auto b : selected_chicken) {
			int tmp = abs(a.first - b.first) + abs(a.second - b.second);
			min_dist = min(min_dist, tmp);
		}
		sum += min_dist;
	}
	chicken_dist = min(chicken_dist, sum);
}

void func(int k, int idx) {
	if (k == M) {
		chicken_distance();
		return;
	}

	for (int i = idx; i < chicken.size(); i++) {
		selected_chicken.push_back(chicken[i]);
		func(k + 1, i + 1);
		selected_chicken.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1)
				house.push_back({ i,j });
			else if (map[i][j] == 2)
				chicken.push_back({ i,j });
		}
	}
	func(0, 0);
	cout << chicken_dist << "\n";

	return 0;
}
