#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>
using namespace std;

void func(vector<int> matrix)
{
	int n = pow(matrix.size(), 0.5);
	vector<int> m1, m2, m3, m4;
	if (accumulate(matrix.begin(), matrix.end(), 0) == 0)
		cout << "0";
	else if (accumulate(matrix.begin(), matrix.end(), 0) == matrix.size())
		cout << "1";
	else {
		cout << "(";
		for (int i = 0; i < matrix.size(); i++) {
			int row = i / n;
			int col = i % n;
			if (row < (n / 2) && col < (n / 2))
				m1.push_back(matrix[i]);
			else if (row < (n / 2) && col >= (n / 2))
				m2.push_back(matrix[i]);
			else if (row >= (n / 2) && col < (n / 2))
				m3.push_back(matrix[i]);
			else if (row >= (n / 2) && col >= (n / 2))
				m4.push_back(matrix[i]);
		}
		func(m1); // 좌상단
		func(m2); // 우상단
		func(m3); // 좌하단
		func(m4); // 우하단
		cout << ")";
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N;
	char tmp;
	vector<int> matrix;
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> tmp;
			matrix.push_back(int(tmp - '0'));
		}
	}

	func(matrix);
	cout << "\n";

	return 0;
}