#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int n, m;
vector<vector<int>> board;
vector<vector<vector<int>>> visit;
pair<int, int> dir[4] = { {-1,0},{1,0},{0,-1},{0,1} };

bool check(int row, int col, int wall) {
	if (row >= 0 && col >= 0 && row < n && col < m && visit[row][col][wall] == 0)
		return true;
	return false;
}

int bfs() {
	queue<pair<int, pair<int, pair<int, int>>>> q; // 이동횟수, {벽부순갯수, {좌표}}
	q.push({ 1,{0,{0,0}} });

	while (!q.empty()) {
		int cnt = q.front().first;
		int wall = q.front().second.first;
		int row = q.front().second.second.first;
		int col = q.front().second.second.second;
		q.pop();

		if (row == n - 1 && col == m - 1)
			return cnt;

		for (int i = 0; i < 4; i++) {
			int new_row = row + dir[i].first;
			int new_col = col + dir[i].second;
			if (!check(new_row, new_col, wall)) {
				continue;
			}
				
			if (board[new_row][new_col] == 1 && wall == 1) {
				continue;
			}
			if (board[new_row][new_col] == 1) {
				q.push({ cnt + 1,{1, {new_row, new_col}} });
				visit[new_row][new_col][1] = 1;
			}
				
			else {
				q.push({ cnt + 1,{wall, {new_row, new_col}} });
				visit[new_row][new_col][wall] = 1;
			}
		}
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	board.resize(n, vector<int>(m));
	visit.resize(n, vector<vector<int>>(m,vector<int>(2)));
	
	string str;
	getline(cin, str);
	for (int i = 0; i < n; i++) {
		getline(cin, str);
		for (int j = 0; j < m; j++) {
			board[i][j] = int(str[j] - '0');
		}
	}

	cout << bfs() << "\n";


	return 0;
}
