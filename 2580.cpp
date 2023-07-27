#include <iostream>
#include <vector>
#include <string>
using namespace std;

int matrix[9][9], result[9][9];
vector<int> Z; // 0인 인덱스를 저장

bool find_row(int index, int num) {
	for (int i = 0; i < 9; i++) {
		if (matrix[index][i] == num)
			return true;
	}
	return false;
}

bool find_col(int index, int num) {
	for (int i = 0; i < 9; i++) {
		if (matrix[i][index] == num)
			return true;
	}
	return false;
}

bool find_box(int index1, int index2, int num) {
	index1 = (index1 / 3) * 3;
	index2 = (index2 / 3) * 3;
	for (int i = index1; i < index1 + 3; i++) {
		for (int j = index2; j < index2 + 3; j++) {
			if (matrix[i][j] == num)
				return true;
		}
	} 
	return false;
}

void func(int n) {
	if (n == Z.size()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 8; j++)
				cout << matrix[i][j] << " ";
			cout << matrix[i][8] << "\n";
		}
		return;
	}

	int row, col;

	row = Z[n] / 9;
	col = Z[n] % 9;
	for (int i = 1; i <= 9; i++) {
		if (!find_row(row, i) && !find_col(col, i) && !find_box(row, col, i)) {
			matrix[row][col] = i;
			func(n + 1);
			matrix[row][col] = 0;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	string str;
	vector<string> S;
	int row, col;

	for (int i = 0; i < 9; i++) {
		getline(cin, str);
		S.push_back(str);
	}

	for (int i = 0; i < 9; i++) {
		int j = 0;
		for (auto s : S[i]) {
			if (s != ' ') {
				matrix[i][j] = int(s - '0');
				if (s == '0')
					Z.push_back(i * 9 + j);
				j++;
			}
		}
	}

	func(0);
	return 0;
}