#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int board[500][500];
int visited[500][500] = { 0 };
vector<int> result;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

void func(int k, int sum, int x, int y) {
	visited[x][y] = 1;
	sum += board[x][y];
	if (k == 4) {
		result.push_back(sum);
		return;
	}

	for (int i = 0; i < 4; i++) { // 상하좌우 4 방향 따져줌
		int x_new = x + dir[i][0];
		int y_new = y + dir[i][1];
		if (x_new >= 0 && x_new < N && y_new >= 0 && y_new < M && visited[x_new][y_new] == 0) {
			func(k + 1, sum, x_new, y_new);
			visited[x_new][y_new] = 0;
		}
	}
}

void cross(int i, int j) {
	if ((i - 1) >= 0 && (j - 1) >= 0 && (j + 1) < M) // ㅗ
		result.push_back(board[i][j] + board[i - 1][j] + board[i][j - 1] + board[i][j + 1]);
	if ((i - 1) >= 0 && (i + 1) < N && (j + 1) < M) // ㅏ
		result.push_back(board[i][j] + board[i - 1][j] + board[i + 1][j] + board[i][j + 1]);
	if ((j - 1) >= 0 && (i + 1) < N && (j + 1) < M) // ㅜ
		result.push_back(board[i][j] + board[i][j - 1] + board[i + 1][j] + board[i][j + 1]);
	if ((i - 1) >= 0 && (i + 1) < N && (j - 1) >= 0) // ㅓ
		result.push_back(board[i][j] + board[i - 1][j] + board[i + 1][j] + board[i][j - 1]);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cin >> board[i][j];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			func(1, 0, i, j);
			cross(i, j);
			visited[i][j] = 0;
		}
	}
	
	cout << *max_element(result.begin(), result.end()) << "\n";

	return 0;
}
