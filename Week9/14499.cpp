#include <iostream>
#include <vector>
using namespace std;

int N, M, x, y, K;
int map[20][20];
vector<int> command;
int dice[7] = { 0 };
//   2
// 4 1 3 
//   5
//   6
int bottom = 1, top = 6, front = 5, back = 2, west = 4, east = 3;

void dice_move(int d) {
	int tmp;
	if (d == 1) { // 동쪽
		tmp = bottom;
		bottom = east;
		east = top;
		top = west;
		west = tmp;
	}
	else if (d == 2) { // 서쪽
		tmp = bottom;
		bottom = west;
		west = top;
		top = east;
		east = tmp;
	}
	else if (d == 3) { // 북쪽
		tmp = bottom;
		bottom = back;
		back = top;
		top = front;
		front = tmp;
	}
	else if (d == 4) { // 남쪽
		tmp = bottom;
		bottom = front;
		front = top;
		top = back;
		back = tmp;
	}

	if (map[x][y] != 0) { // 지도의 칸이 0이 아니면
		dice[bottom] = map[x][y]; // 해당 칸의 수를 주사위의 바닥면에 복사함
		map[x][y] = 0; // 해당 칸의 수는 0이 됨
	}
	else // 지도의 칸이 0이면
		map[x][y] = dice[bottom];
	
	cout << dice[top] << "\n";
}

void func(int d) {
	if (d == 1) { // 동쪽
		if ((y + 1) < M) {
			y++;
			dice_move(d);
		}
	}
	else if (d == 2) { // 서쪽
		if ((y - 1) >= 0) {
			y--;
			dice_move(d);
		}
	}
	else if (d == 3) { // 북쪽
		if ((x - 1) >= 0) {
			x--;
			dice_move(d);
		}
	}
	else if (d == 4) { // 남쪽
		if ((x + 1) < N) {
			x++;
			dice_move(d);
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> x >> y >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cin >> map[i][j];
	}

	for (int i = 0; i < K; i++) {
		int tmp;
		cin >> tmp;
		command.push_back(tmp);
	}

	for (auto d : command)
		func(d);
	
	return 0;
}
