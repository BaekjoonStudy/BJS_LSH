#include <iostream>
#include <vector>
using namespace std;

int R, C, T, room[50][50], tmp_room[50][50];
vector<pair<int,int>> air_cleaner;
pair<int, int> dir[4] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

void spread_dust() {
	for (int x = 0; x < R; x++) {
		for (int y = 0; y < C; y++) {
			int num = room[x][y], cnt = 0;
			if (num > 0) { // 해당 칸에 미세먼지가 있다면
				for (int i = 0; i < 4; i++) { // 인접한 상하좌우 칸이
					int tx = x + dir[i].first, ty = y + dir[i].second;
					if (tx >= 0 && tx < R && ty >= 0 && ty < C) { // 방을 벗어나지 않고 
						if (room[tx][ty] != -1) { // 공기청정기가 아니라면
							cnt++;
							tmp_room[tx][ty] += num / 5; // 확산
						}
					}
				}
				tmp_room[x][y] -= num / 5 * cnt;
			}
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			room[i][j] += tmp_room[i][j];
			tmp_room[i][j] = 0;
		}
	}
}

void move_dust() {
	int x = air_cleaner[0].first, y = air_cleaner[0].second, d = 0; // 위쪽 공기청정기
	while (true) {
		int tx = x + dir[d].first, ty = y + dir[d].second;
		if (tx >= 0 && tx <= air_cleaner[0].first && ty >= 0 && ty < C) {
			if (room[x][y] == -1) {
				x = tx; y = ty;
				continue;
			}
			else if (room[tx][ty] == -1) {// 바람이 순환하여 다시 공기청정기로 돌아온 경우
				room[x][y] = 0;
				break;
			}
			else {
				room[x][y] = room[tx][ty];
				x = tx; y = ty;
			}
		}
		else {
			if (d == 0) d = 3;
			else if (d == 1) d = 2;
			else if (d == 3) d = 1;
		}
	}

	x = air_cleaner[1].first; y = air_cleaner[1].second, d = 1; // 아래쪽 공기청정기
	while (true) {
		int tx = x + dir[d].first, ty = y + dir[d].second;
		if (tx >= air_cleaner[1].first && tx < R && ty >= 0 && ty < C) {
			if (room[x][y] == -1) {
				x = tx; y = ty;
				continue;
			}
			else if (room[tx][ty] == -1) {// 바람이 순환하여 다시 공기청정기로 돌아온 경우
				room[x][y] = 0;
				break;
			}
			else {
				room[x][y] = room[tx][ty];
				x = tx; y = ty;
			}
		}
		else {
			if (d == 0) d = 2;
			else if (d == 1) d = 3;
			else if (d == 3) d = 0;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> R >> C >> T;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> room[i][j];
			if (room[i][j] == -1)
				air_cleaner.push_back({ i,j });
		}
	}

	while (T--) {
		spread_dust();
		move_dust();
	}

	int sum = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++)
			sum += room[i][j];
	}

	cout << sum + 2 << "\n";

	return 0;
}
