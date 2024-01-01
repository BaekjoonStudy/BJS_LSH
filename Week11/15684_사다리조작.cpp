#include <iostream>
#include <vector>
using namespace std;

int N, M, H, ladder[11][31] = { 0 };

bool check() { // i번 세로선의 결과가 i번인지 아닌지
	for (int i = 1; i <= N; i++) {
		int curr = i;
		for (int j = 1; j <= H; j++) {
			curr = ladder[curr][j] ? ladder[curr][j] : curr; // 0이 아니면, 즉 가로줄로 인해 세로선이 바뀌면 업데이트
		}
		if (i != curr)
			return false;
	}
	return true;
}

bool func(int k, int n, int idx) {
	if (k == n) {
		return check();
	}

	bool result;
	for (int i = idx; i < N; i++) { // 최대한 중복을 줄이기 위해 한번 봤던 세로선은 고려하지 않도록 idx부터 시작
		for (int j = 1; j <= H; j++) {
			if (ladder[i][j] == 0 && ladder[i + 1][j] == 0) {
				ladder[i][j] = i + 1;
				ladder[i + 1][j] = i;
				result = func(k + 1, n, i);
				ladder[i][j] = 0;
				ladder[i + 1][j] = 0;
				if (result == true)
					return true;
			}
		}
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> H;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		ladder[b][a] = b + 1; // a번 점선에서 b에서 b+1로
		ladder[b + 1][a] = b; // a번 점선에서 b+1에서 b로
	}

	if (check() == true) {
		cout << 0 << "\n";
	}
	else if (func(0, 1, 1) == true) {
		cout << 1 << "\n";
	}
	else if (func(0, 2, 1) == true) {
		cout << 2 << "\n";
	}
	else if (func(0, 3, 1) == true) {
		cout << 3 << "\n";
	}
	else {
		cout << -1 << "\n";
	}

	return 0;
}
