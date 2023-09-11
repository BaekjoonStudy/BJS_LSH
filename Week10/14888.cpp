#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
vector<int> num, result;
int oper[4];

void func(int k, int res) {
	if (k == N) {
		result.push_back(res);
		return;
	}

	for (int i = 0; i < 4; i++) { // 사칙연산
		if (oper[i] > 0) {
			oper[i]--;
			if (i == 0) // 덧셈
				func(k + 1, res + num[k]);
			else if (i == 1) // 뺄셈
				func(k + 1, res - num[k]);
			else if (i == 2) // 곱셈
				func(k + 1, res * num[k]);
			else if (i == 3) // 나눗셈
				func(k + 1, res / num[k]);
			oper[i]++;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		num.push_back(tmp);
	}

	for (int i = 0; i < 4; i++)
		cin >> oper[i];

	func(1, num[0]);
	
	cout << *max_element(result.begin(), result.end()) << "\n";
	cout << *min_element(result.begin(), result.end()) << "\n";

	return 0;
}
