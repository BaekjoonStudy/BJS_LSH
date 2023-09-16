#include <iostream>
using namespace std;

int N, L, res = 0;
int map[100][100];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	}

	// row
	for (int i = 0; i < N; i++) {
		int cnt = 1; // 같은 수가 몇 번 반복되는지 카운팅하는 변수
		bool isDown = false, isBool = true; // isDown : 내려가는 경사로 필요한지  isBool : 길이 이어졌는지
		for (int j = 1; j < N; j++) {
			if (abs(map[i][j - 1] - map[i][j]) > 1) { // 높이 차이가 1보다 크다면
				isBool = false;
				break;
			}
			if (isDown == false) { // 내려가는 경사로 필요없다면
				if (map[i][j - 1] - map[i][j] == 0) // 숫자가 같다면
					cnt++;
				else if (map[i][j - 1] - map[i][j] == 1) { // 내려가는 경사로 필요
					cnt = 1;
					if (cnt == L) { // 내려가는 경사로 설치 가능
						isBool = true;
						cnt = 0;
					}
					else { // 내려가는 경사로 설치 불가능
						isBool = false;
						isDown = true;
					}
				}
				else if (map[i][j - 1] - map[i][j] == -1) { // 올라가는 경사로 필요
					if (cnt >= L) { // 올라가는 경사로 설치 가능
						isBool = true;
						cnt = 1;
					}
					else { // 올라가는 경사로 설치 불가능
						isBool = false;
						break;
					}
				}
			}

			else { // 내려가는 경사로 필요하다면
				if (map[i][j - 1] - map[i][j] == 0) { // 숫자가 같다면
					if (++cnt >= L) { // 내려가는 경사로 설치 가능
						isBool = true;
						isDown = false;
						cnt = 0;
					}
				}
				else { // 숫자가 다르다면
					isBool = false;
					break;
				}
			}
		}

		if (isBool == true) {
			res++;
			// cout << i << "\n";
		}
	}

	// col
	for (int j = 0; j < N; j++) {
		int cnt = 1; // 같은 수가 몇 번 반복되는지 카운팅하는 변수
		bool isDown = false, isBool = true; // isDown : 내려가는 경사로 필요한지  isBool : 길이 이어졌는지
		for (int i = 1; i < N; i++) {
			if (abs(map[i - 1][j] - map[i][j]) > 1) { // 높이 차이가 1보다 크다면
				isBool = false;
				break;
			}
			if (isDown == false) { // 내려가는 경사로 필요없다면
				if (map[i - 1][j] - map[i][j] == 0) // 숫자가 같다면
					cnt++;
				else if (map[i - 1][j] - map[i][j] == 1) { // 내려가는 경사로 필요
					cnt = 1;
					if (cnt == L) { // 내려가는 경사로 설치 가능
						isBool = true;
						cnt = 0;
					}
					else { // 내려가는 경사로 설치 불가능
						isBool = false;
						isDown = true;
					}
				}
				else if (map[i - 1][j] - map[i][j] == -1) { // 올라가는 경사로 필요
					if (cnt >= L) { // 올라가는 경사로 설치 가능
						isBool = true;
						cnt = 1;
					}
					else { // 올라가는 경사로 설치 불가능
						isBool = false;
						break;
					}
				}
			}

			else { // 내려가는 경사로 필요하다면
				if (map[i - 1][j] - map[i][j] == 0) { // 숫자가 같다면
					if (++cnt >= L) { // 내려가는 경사로 설치 가능
						isBool = true;
						isDown = false;
						cnt = 0;
					}
				}
				else { // 숫자가 다르다면
					isBool = false;
					break;
				}
			}
		}

		if (isBool == true) {
			res++;
			// cout << j << "\n";
		}
	}
	
	cout << res << "\n";

	return 0;
}
