#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int board[20][20] = { 0 };
vector<int> result;

void move_board(int dir) {
	if (dir == 0) { // 상
		for (int j = 0; j < N; j++) {
			int start = 0; // 두 수를 더한 값이 위치할 좌표
			int isbool = false; // 0이 아닌 수를 두 개 찾아야하기 때문에 이를 나타낼 bool 변수
			for (int i = 0; i < N; i++) {
				if (board[i][j] != 0) {
					if (isbool == false) { // 0이 아닌 수를 한 개 찾았을 때
						isbool = true;
						board[start][j] = board[i][j];
						if (start != i)
							board[i][j] = 0;
					}
					else if (board[start][j] == board[i][j]) { // 0이 아닌 수를 두 개 찾았고 그 수가 같을 때
						isbool = false;
						board[start][j] += board[i][j];
						board[i][j] = 0;
						start++;
					}
					else { // 0이 아닌 수를 두 개 찾았지만 그 두 수가 다를 때
						isbool = true;
						board[++start][j] = board[i][j];
						if (start != i)
							board[i][j] = 0;
					}
				}	
			}
		}
	}

	else if (dir == 1) { // 하
		for (int j = 0; j < N; j++) {
			int start = N - 1; // 두 수를 더한 값이 위치할 좌표
			int isbool = false; // 0이 아닌 수를 두 개 찾아야하기 때문에 이를 나타낼 bool 변수
			for (int i = N - 1; i >= 0; i--) {
				if (board[i][j] != 0) {
					if (isbool == false) { // 0이 아닌 수를 한 개 찾았을 때
						isbool = true;
						board[start][j] = board[i][j];
						if (start != i)
							board[i][j] = 0;
					}
					else if (board[start][j] == board[i][j]) { // 0이 아닌 수를 두 개 찾았고 그 수가 같을 때
						isbool = false;
						board[start][j] += board[i][j];
						board[i][j] = 0;
						start--;
					}
					else { // 0이 아닌 수를 두 개 찾았지만 그 두 수가 다를 때
						isbool = true;
						board[--start][j] = board[i][j];
						if (start != i)
							board[i][j] = 0;
					}
				}
			}
		}
	}

	else if (dir == 2) { // 좌
		for (int i = 0; i < N; i++) {
			int start = 0; // 두 수를 더한 값이 위치할 좌표
			int isbool = false; // 0이 아닌 수를 두 개 찾아야하기 때문에 이를 나타낼 bool 변수
			for (int j = 0; j < N; j++) {
				if (board[i][j] != 0) {
					if (isbool == false) { // 0이 아닌 수를 한 개 찾았을 때
						isbool = true;
						board[i][start] = board[i][j];
						if (start != j)
							board[i][j] = 0;
					}
					else if (board[i][start] == board[i][j]) { // 0이 아닌 수를 두 개 찾았고 그 수가 같을 때
						isbool = false;
						board[i][start] += board[i][j];
						board[i][j] = 0;
						start++;
					}
					else { // 0이 아닌 수를 두 개 찾았지만 그 두 수가 다를 때
						isbool = true;
						board[i][++start] = board[i][j];
						if (start != j)
							board[i][j] = 0;
					}
				}
			}
		}
	}

	else if (dir == 3) { // 우
		for (int i = 0; i < N; i++) {
			int start = N - 1; // 두 수를 더한 값이 위치할 좌표
			int isbool = false; // 0이 아닌 수를 두 개 찾아야하기 때문에 이를 나타낼 bool 변수
			for (int j = N - 1; j >= 0; j--) {
				if (board[i][j] != 0) {
					if (isbool == false) { // 0이 아닌 수를 한 개 찾았을 때
						isbool = true;
						board[i][start] = board[i][j];
						if (start != j)
							board[i][j] = 0;
					}
					else if (board[i][start] == board[i][j]) { // 0이 아닌 수를 두 개 찾았고 그 수가 같을 때
						isbool = false;
						board[i][start] += board[i][j];
						board[i][j] = 0;
						start--;
					}
					else { // 0이 아닌 수를 두 개 찾았지만 그 두 수가 다를 때
						isbool = true;
						board[i][--start] = board[i][j];
						if (start != j)
							board[i][j] = 0;
					}
				}
			}
		}
	}
}

void func(int k) {
	if (k == 5) {
		int max = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] > max)
					max = board[i][j];
			}
		}
		result.push_back(max);
		return;
	}
	int before_board[20][20];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			before_board[i][j] = board[i][j];
	}

	for (int n = 0; n < 4; n++) { // 상하좌우 4번 반복
		move_board(n);
		func(k + 1);
		// 바뀐 보드판을 다시 이전 상태로
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				board[i][j] = before_board[i][j];
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	func(0);

	cout << *max_element(result.begin(), result.end()) << "\n";

	return 0;
}
