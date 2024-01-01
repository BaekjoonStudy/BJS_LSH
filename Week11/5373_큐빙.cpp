#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
using namespace std;

vector<pair<char, char>> command;
char cube[54];
int U[12] = { 9,10,11,45,46,47,35,34,33,36,37,38 }, u[8] = { 0,1,2,5,8,7,6,3 };
int D[12] = { 27,28,29,53,52,51,17,16,15,44,43,42 }, d[8] = { 18,19,20,23,26,25,24,21 };
int F[12] = { 18,19,20,51,48,45,8,7,6,38,41,44 }, f[8] = { 9,10,11,14,17,16,15,12 };
int B[12] = { 0,1,2,47,50,53,26,25,24,42,39,36 }, b[8] = { 27,28,29,32,35,34,33,30 };
int L[12] = { 24,21,18,15,12,9,6,3,0,33,30,27 }, l[8] = { 36,37,38,41,44,43,42,39 };
int R[12] = { 20,23,26,29,32,35,2,5,8,11,14,17 }, r[8] = { 45,46,47,50,53,52,51,48 };

void init_cube() {
	char color[6] = { 'w', 'r', 'y', 'o', 'g', 'b' }; // 윗면, 앞면, 아랫면, 뒷면, 왼쪽면, 오른쪽면 순
	for (int i = 0; i < 54; i++) {
		cube[i] = color[i / 9];
	}
}

void roll(int a[12], int b[8], char dir) {
	if (dir == '+') { // 시계방향
		// 주변
		char tmp1 = cube[a[0]], tmp2 = cube[a[1]], tmp3 = cube[a[2]];
		for (int i = 0; i < 9; i++)
			cube[a[i]] = cube[a[i + 3]];
		cube[a[9]] = tmp1;
		cube[a[10]] = tmp2;
		cube[a[11]] = tmp3;

		// 해당 면
		char tmp4 = cube[b[6]], tmp5 = cube[b[7]];
		for (int i = 7; i > 1; i--)
			cube[b[i]] = cube[b[i - 2]];
		cube[b[0]] = tmp4;
		cube[b[1]] = tmp5;
	}
	else { // 반시계방향
		// 주변
		char tmp1 = cube[a[9]], tmp2 = cube[a[10]], tmp3 = cube[a[11]];
		for (int i = 11; i > 2; i--)
			cube[a[i]] = cube[a[i - 3]];
		cube[a[0]] = tmp1;
		cube[a[1]] = tmp2;
		cube[a[2]] = tmp3;

		// 해당 면
		char tmp4 = cube[b[0]], tmp5 = cube[b[1]];
		for (int i = 0; i < 6; i++)
			cube[b[i]] = cube[b[i + 2]];
		cube[b[6]] = tmp4;
		cube[b[7]] = tmp5;
	}
}

void print_result() {
	for (int i = 0; i < 9; i++) {
		cout << cube[i];
		if (i % 3 == 2)
			cout << "\n";
	}
}

void func() {
	for (int i = 0; i < command.size(); i++) {
		if (command[i].first == 'U')
			roll(U, u, command[i].second);
		else if (command[i].first == 'D')
			roll(D, d, command[i].second);
		else if (command[i].first == 'F')
			roll(F, f, command[i].second);
		else if (command[i].first == 'B')
			roll(B, b, command[i].second);
		else if (command[i].first == 'L')
			roll(L, l, command[i].second);
		else if (command[i].first == 'R')
			roll(R, r, command[i].second);
	}
}



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T, n;
	cin >> T;
	while (T--) {
		init_cube();
		command.clear();
		cin >> n;
		while (n--) {
			char c1, c2;
			cin >> c1 >> c2;
			command.push_back({ c1,c2 });
		}
		func();
		print_result();
	}

	return 0;
}
