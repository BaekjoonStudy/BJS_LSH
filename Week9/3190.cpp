#include <iostream>
#include <vector>
using namespace std;

int N, K, L;
int board[100][100] = { 0 };
pair<pair<int, int>, pair<int, int>> sneak = { {0,0},{0,0} }; // 뱀 머리 좌표, 뱀 꼬리 좌표
vector<pair<int, char>> command;
int sneak_length = 0;

void change_dir(int& dir, char c) {
	if (c == 'L') { // 상->좌 하->우 좌->하 우->상
		if (dir == 0 || dir == 1) // 상->좌 하->우
			dir += 2;
		else if (dir == 2) // 좌->하
			dir = 1;
		else if (dir == 3) // 우->상
			dir = 0;
	}
	else if (c == 'D') { // 상->우 하->좌 좌->상 우->하
		if (dir == 2 || dir == 3) // 좌->상 우->하
			dir -= 2;
		else if (dir == 0) // 상->우
			dir = 3;
		else if (dir == 1) // 하->좌
			dir = 2;
	}
}

void tail(int idx, int dir, int cnt) {
	board[sneak.second.first][sneak.second.second] = 0;
	if (idx == 0) // 아직 진행 방향이 바뀌기 전이기 때문에 꼬리도 무조건 오른쪽 방향으로 움직임
		sneak.second.second++;
	else { // 꼬리와 머리의 진행 방향이 다를 수 있음, 꼬리는 항상 머리보다 총 길이만큼 늦게 방향을 바꿈
		if (cnt >= (command[idx - 1].first + sneak_length)) { // 머리가 방향을 바꾸고 총 길이만큼 시간이 더 지난 경우
			// 꼬리와 머리의 진행 방향이 같음
			if (dir == 0) // 상
				sneak.second.first--;
			else if (dir == 1) // 하
				sneak.second.first++;
			else if (dir == 2) // 좌
				sneak.second.second--;
			else if (dir == 3) // 우
				sneak.second.second++;
		}
		else { // 총 길이만큼 시간이 더 지나지 않아 꼬리와 머리의 진행 방향이 다른 경우
			char c = (command[idx - 1].second == 'L') ? 'D' : 'L'; // 이전 진행 방향으로 바꾸기 위함
			change_dir(dir, c); // 이전 진행 방향으로 바꾼 후
			tail(idx - 1, dir, cnt); // 재귀를 통해 꼬리 좌표 갱신
		}
	}
}

bool move_sneak(int idx, int dir, int& cnt) {
    int x = command[idx].first;
    if (idx == -1){
        x = cnt + N;
        idx = L;
    }

	while (cnt < x) {
		if (dir == 0) { // 상
			if (sneak.first.first - 1 >= 0) {
				if (board[sneak.first.first - 1][sneak.first.second] != 1) {
					if (board[sneak.first.first - 1][sneak.first.second] == 2) // 사과를 만나면
						sneak_length++;
					else // 사과가 아니면
						tail(idx, dir, cnt); // 꼬리 위치를 0으로 바꾸고 꼬리 좌표 갱신
					board[--sneak.first.first][sneak.first.second] = 1; // 머리 좌표 갱신 후 머리 위치를 1로 바꿈
				}
				else { // 자기 몸에 부딪힌 경우
					cnt++;
					return false;
				}
			}

			else { // 벽에 부딪힌 경우
				cnt++;
				return false;
			}
		}

		else if (dir == 1) { // 하
			if (sneak.first.first + 1 < N) {
				if (board[sneak.first.first + 1][sneak.first.second] != 1) {
					if (board[sneak.first.first + 1][sneak.first.second] == 2) // 사과를 만나면
						sneak_length++;
					else // 사과가 아니면
						tail(idx, dir, cnt); // 꼬리 위치를 0으로 바꾸고 꼬리 좌표 갱신
					board[++sneak.first.first][sneak.first.second] = 1; // 머리 좌표 갱신 후 머리 위치를 1로 바꿈
				}
				else { // 자기 몸에 부딪힌 경우
					cnt++;
					return false;
				}
			}

			else { // 벽에 부딪힌 경우
				cnt++;
				return false;
			}
		}

		else if (dir == 2) { // 좌
			if (sneak.first.second - 1 >= 0) {
				if (board[sneak.first.first][sneak.first.second - 1] != 1) {
					if (board[sneak.first.first][sneak.first.second - 1] == 2) // 사과를 만나면
						sneak_length++;
					else // 사과가 아니면
						tail(idx, dir, cnt); // 꼬리 위치를 0으로 바꾸고 꼬리 좌표 갱신
					board[sneak.first.first][--sneak.first.second] = 1; // 머리 좌표 갱신 후 머리 위치를 1로 바꿈
				}
				else { // 자기 몸에 부딪힌 경우
					cnt++;
					return false;
				}
			}

			else { // 벽에 부딪힌 경우
				cnt++;
				return false;
			}
		}

		else if (dir == 3) { // 우
			if (sneak.first.second + 1 < N) {
				if (board[sneak.first.first][sneak.first.second + 1] != 1) {
					if (board[sneak.first.first][sneak.first.second + 1] == 2) // 사과를 만나면
						sneak_length++;
					else // 사과가 아니면
						tail(idx, dir, cnt); // 꼬리 위치를 0으로 바꾸고 꼬리 좌표 갱신
					board[sneak.first.first][++sneak.first.second] = 1; // 머리 좌표 갱신 후 머리 위치를 1로 바꿈
				}
				else { // 자기 몸에 부딪힌 경우
					cnt++;
					return false;
				}
			}

			else { // 벽에 부딪힌 경우
				cnt++;
				return false;
			}
		}
		cnt++;
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	cin >> K;
	board[0][0] = 1; // 뱀 시작 위치
	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;
		board[x - 1][y - 1] = 2; 
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int x;
		char y;
		cin >> x >> y;
		command.push_back({ x, y });
	}

	int dir = 3; // 상하좌우 순
	int cnt = 0;
	bool isbool;
	for (int i = 0; i < L; i++) {
		isbool = move_sneak(i, dir, cnt);
		change_dir(dir, command[i].second);
		if (!isbool)
			break;
	}

	while (isbool) {
		isbool = move_sneak(-1, dir, cnt);
	}

	cout << cnt << "\n";
	
	return 0;
}
