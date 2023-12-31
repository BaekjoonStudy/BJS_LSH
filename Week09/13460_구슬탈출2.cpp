#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
char map[10][10];
queue<pair<int, pair<int, int>>> red_queue, blue_queue;

int move(int& y1, int& x1, int y2, int x2, int dir) { // y1,x1 : 움직일 구슬 좌표 / y2,x2 : 움직이지 않을 구슬 좌표
	if (dir == 0) { // 위쪽
		while (true) {
			if (map[y1 - 1][x1] == 'O') {// 구슬이 구멍에 들어갔다면 멈춤
				y1--;
				return 1;
			}
			if (map[y1 - 1][x1] == '#' || ((y1 - 1) == y2 && x1 == x2)) // 장애물을 만나거나 다른 구슬을 만나면 멈춤
				return 0;
			y1--;
		}
	}
	else if (dir == 1) { // 아래쪽
		while (true) {
			if (map[y1 + 1][x1] == 'O') {// 구슬이 구멍에 들어갔다면 멈춤
				y1++;
				return 1;
			}
			if (map[y1 + 1][x1] == '#' || ((y1 + 1) == y2 && x1 == x2)) // 장애물을 만나거나 다른 구슬을 만나면 멈춤
				return 0;
			y1++;
		}
	}
	else if (dir == 2) { // 왼쪽
		while (true) {
			if (map[y1][x1 - 1] == 'O') {// 구슬이 구멍에 들어갔다면 멈춤
				x1--;
				return 1;
			}
			if (map[y1][x1 - 1] == '#' || (y1 == y2 && (x1 - 1) == x2)) // 장애물을 만나거나 다른 구슬을 만나면 멈춤
				return 0;
			x1--;
		}
	}
	else if (dir == 3) { // 오른쪽
		while (true) {
			if (map[y1][x1 + 1] == 'O') {// 구슬이 구멍에 들어갔다면 멈춤
				x1--;
				return 1;
			}
			if (map[y1][x1 + 1] == '#' || (y1 == y2 && (x1 + 1) == x2)) // 장애물을 만나거나 다른 구슬을 만나면 멈춤
				return 0;
			x1++;
		}
	}
}

void bfs() {
	int red_in_hole = 0, blue_in_hole = 0;
	while (true) {
		int red_init_y = red_queue.front().second.first;
		int red_init_x = red_queue.front().second.second;
		int blue_init_y = blue_queue.front().second.first;
		int blue_init_x = blue_queue.front().second.second;
		int red_cnt = red_queue.front().first;
		int blue_cnt = blue_queue.front().first;
		int red_y, red_x, blue_y, blue_x;

		red_queue.pop();
		blue_queue.pop();

		// 위쪽
		red_y = red_init_y; red_x = red_init_x; blue_y = blue_init_y; blue_x = blue_init_x;
		if (red_y < blue_y) { // 빨간 구슬부터
			red_in_hole = move(red_y, red_x, blue_y, blue_x, 0);
			blue_in_hole = move(blue_y, blue_x, red_y, red_x, 0);

			// 빨간 구슬의 위치가 변하지 않았거나 파란 구슬이 구멍에 들어가는 경우 queue에 push하지 않음
			if (blue_in_hole == 0) { // 파란 구슬이 구멍에 들어가지 않고
				if (red_in_hole == 1) { // 빨간 구슬이 구멍에 들어갔다면
					cout << red_cnt << "\n";
					break;
				}
				else if (red_init_y != red_y || red_init_x != red_x || blue_init_y != blue_y || blue_init_x != blue_x) {
					// 두 구슬 모두 구멍에 들어가지 않고 구슬의 위치가 변했다면
					red_queue.push({ red_cnt + 1, { red_y, red_x } });
					blue_queue.push({ blue_cnt + 1, { blue_y, blue_x } });
				}
			}
		}
		else { // 파란 구슬부터
			blue_in_hole = move(blue_y, blue_x, red_y, red_x, 0);
			red_in_hole = move(red_y, red_x, blue_y, blue_x, 0);

			// 빨간 구슬의 위치가 변하지 않았거나 파란 구슬이 구멍에 들어가는 경우 queue에 push하지 않음
			if (blue_in_hole == 0) { // 파란 구슬이 구멍에 들어가지 않고
				if (red_in_hole == 1) { // 빨간 구슬이 구멍에 들어갔다면
					cout << red_cnt << "\n";
					break;
				}
				else if (red_init_y != red_y || red_init_x != red_x || blue_init_y != blue_y || blue_init_x != blue_x) {
					// 두 구슬 모두 구멍에 들어가지 않고 구슬의 위치가 변했다면
					red_queue.push({ red_cnt + 1, { red_y, red_x } });
					blue_queue.push({ blue_cnt + 1, { blue_y, blue_x } });
				}
			}
		}
		// 아래쪽
		red_y = red_init_y; red_x = red_init_x; blue_y = blue_init_y; blue_x = blue_init_x;
		if (red_y > blue_y) { // 빨간 구슬부터
			red_in_hole = move(red_y, red_x, blue_y, blue_x, 1);
			blue_in_hole = move(blue_y, blue_x, red_y, red_x, 1);

			// 빨간 구슬의 위치가 변하지 않았거나 파란 구슬이 구멍에 들어가는 경우 queue에 push하지 않음
			if (blue_in_hole == 0) { // 파란 구슬이 구멍에 들어가지 않고
				if (red_in_hole == 1) { // 빨간 구슬이 구멍에 들어갔다면
					cout << red_cnt << "\n";
					break;
				}
				else if (red_init_y != red_y || red_init_x != red_x || blue_init_y != blue_y || blue_init_x != blue_x) {
					// 두 구슬 모두 구멍에 들어가지 않고 구슬의 위치가 변했다면
					red_queue.push({ red_cnt + 1, { red_y, red_x } });
					blue_queue.push({ blue_cnt + 1, { blue_y, blue_x } });
				}
			}
		}
		else { // 파란 구슬부터
			blue_in_hole = move(blue_y, blue_x, red_y, red_x, 1);
			red_in_hole = move(red_y, red_x, blue_y, blue_x, 1);

			// 빨간 구슬의 위치가 변하지 않았거나 파란 구슬이 구멍에 들어가는 경우 queue에 push하지 않음
			if (blue_in_hole == 0) { // 파란 구슬이 구멍에 들어가지 않고
				if (red_in_hole == 1) { // 빨간 구슬이 구멍에 들어갔다면
					cout << red_cnt << "\n";
					break;
				}
				else if (red_init_y != red_y || red_init_x != red_x || blue_init_y != blue_y || blue_init_x != blue_x) {
					// 두 구슬 모두 구멍에 들어가지 않고 구슬의 위치가 변했다면
					red_queue.push({ red_cnt + 1, { red_y, red_x } });
					blue_queue.push({ blue_cnt + 1, { blue_y, blue_x } });
				}
			}
		}
		// 왼쪽
		red_y = red_init_y; red_x = red_init_x; blue_y = blue_init_y; blue_x = blue_init_x;
		if (red_x < blue_x) { // 빨간 구슬부터
			red_in_hole = move(red_y, red_x, blue_y, blue_x, 2);
			blue_in_hole = move(blue_y, blue_x, red_y, red_x, 2);

			// 빨간 구슬의 위치가 변하지 않았거나 파란 구슬이 구멍에 들어가는 경우 queue에 push하지 않음
			if (blue_in_hole == 0) { // 파란 구슬이 구멍에 들어가지 않고
				if (red_in_hole == 1) { // 빨간 구슬이 구멍에 들어갔다면
					cout << red_cnt << "\n";
					break;
				}
				else if (red_init_y != red_y || red_init_x != red_x || blue_init_y != blue_y || blue_init_x != blue_x) {
					// 두 구슬 모두 구멍에 들어가지 않고 구슬의 위치가 변했다면
					red_queue.push({ red_cnt + 1, { red_y, red_x } });
					blue_queue.push({ blue_cnt + 1, { blue_y, blue_x } });
				}
			}
		}
		else { // 파란 구슬부터
			blue_in_hole = move(blue_y, blue_x, red_y, red_x, 2);
			red_in_hole = move(red_y, red_x, blue_y, blue_x, 2);

			// 빨간 구슬의 위치가 변하지 않았거나 파란 구슬이 구멍에 들어가는 경우 queue에 push하지 않음
			if (blue_in_hole == 0) { // 파란 구슬이 구멍에 들어가지 않고
				if (red_in_hole == 1) { // 빨간 구슬이 구멍에 들어갔다면
					cout << red_cnt << "\n";
					break;
				}
				else if (red_init_y != red_y || red_init_x != red_x || blue_init_y != blue_y || blue_init_x != blue_x) {
					// 두 구슬 모두 구멍에 들어가지 않고 구슬의 위치가 변했다면
					red_queue.push({ red_cnt + 1, { red_y, red_x } });
					blue_queue.push({ blue_cnt + 1, { blue_y, blue_x } });
				}
			}
		}
		// 오른쪽
		red_y = red_init_y; red_x = red_init_x; blue_y = blue_init_y; blue_x = blue_init_x;
		if (red_x > blue_x) { // 빨간 구슬부터
			red_in_hole = move(red_y, red_x, blue_y, blue_x, 3);
			blue_in_hole = move(blue_y, blue_x, red_y, red_x, 3);

			// 빨간 구슬의 위치가 변하지 않았거나 파란 구슬이 구멍에 들어가는 경우 queue에 push하지 않음
			if (blue_in_hole == 0) { // 파란 구슬이 구멍에 들어가지 않고
				if (red_in_hole == 1) { // 빨간 구슬이 구멍에 들어갔다면
					cout << red_cnt << "\n";
					break;
				}
				else if (red_init_y != red_y || red_init_x != red_x || blue_init_y != blue_y || blue_init_x != blue_x) {
					// 두 구슬 모두 구멍에 들어가지 않고 구슬의 위치가 변했다면
					red_queue.push({ red_cnt + 1, { red_y, red_x } });
					blue_queue.push({ blue_cnt + 1, { blue_y, blue_x } });
				}
			}
		}
		else { // 파란 구슬부터
			blue_in_hole = move(blue_y, blue_x, red_y, red_x, 3);
			red_in_hole = move(red_y, red_x, blue_y, blue_x, 3);

			// 빨간 구슬의 위치가 변하지 않았거나 파란 구슬이 구멍에 들어가는 경우 queue에 push하지 않음
			if (blue_in_hole == 0) { // 파란 구슬이 구멍에 들어가지 않고
				if (red_in_hole == 1) { // 빨간 구슬이 구멍에 들어갔다면
					cout << red_cnt << "\n";
					break;
				}
				else if (red_init_y != red_y || red_init_x != red_x || blue_init_y != blue_y || blue_init_x != blue_x) {
					// 두 구슬 모두 구멍에 들어가지 않고 구슬의 위치가 변했다면
					red_queue.push({ red_cnt + 1, { red_y, red_x } });
					blue_queue.push({ blue_cnt + 1, { blue_y, blue_x } });
				}
			}
		}

		if (red_cnt > 10 || red_queue.empty()) { // 10번 내에 구멍에 넣지 못하거나 red_queue가 비었다면
			cout << -1 << "\n";
			break;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'R')
				red_queue.push({ 1,{ i,j } });
			else if (map[i][j] == 'B')
				blue_queue.push({ 1,{ i,j } });
		}
	}
	bfs();

	return 0;
}
