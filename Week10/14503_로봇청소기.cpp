#include <iostream>
using namespace std;

int N, M, r, c, d, cnt = 0;
int room[50][50];
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} }; // 북 동 남 서

bool check() { // 현재 칸 4칸 중 청소되지 않은 빈칸이 있는지 확인
	for (int i = 0; i < 4; i++) {
		if (room[r + dir[i][0]][c + dir[i][1]] == 0)
			return true;
	}
	return false;
}

void rotate_and_go () { // 반시계방향으로 90도 회전 후 한칸 이동
	while (true) { // 아직 청소되지 않은 빈 칸을 찾을 때까지 반복
		d = (d - 1 >= 0) ? d - 1 : 3;
		if (room[r + dir[d][0]][c + dir[d][1]] == 0) {// 아직 청소되지 않은 빈 칸을 찾으면
			r += dir[d][0];	c += dir[d][1]; // 한 칸 전진
			return;
		}
	}
	
}

bool go_back() {
	if (room[r - dir[d][0]][c - dir[d][1]] != 1) { // 뒤가 벽이 아니면
		r -= dir[d][0]; c -= dir[d][1]; // 후진
		return true;
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	cin >> r >> c >> d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cin >> room[i][j];
	}

	while (true) {
		if (room[r][c] == 0) { // 현재 칸이 아직 청소되지 않은 경우
			room[r][c] = 2; // 청소
			cnt++;
		}
		if (check() == true)  // 주변에 청소되지 않은 빈칸이 있는 경우
			rotate_and_go();
	
		else { // 주변에 청소되지 않은 빈칸이 없는 경우
			if (go_back() == false)
				break;
		}
	}
	
	cout << cnt << "\n";

	return 0;
}
