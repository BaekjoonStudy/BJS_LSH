#include <iostream>
#include <vector>
using namespace std;

int N, B, C;
vector<int> A;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		A.push_back(tmp);
	}
	cin >> B >> C;

	long long result = N; // 각 시험장에 총감독관은 한명은 있어야 함
	for (auto x : A) {
		x -= B; // 총감독관이 감시할 수 있는 학생 빼줌
		if (x > 0) {
			result += x / C; // 부감독관이 몇 명 필요한지
			if (x % C != 0) // 딱 나눠떨어지지 않으면
				result++; // 부감독관 한 명 더 필요
		}
	}
	cout << result << "\n";

	return 0;
}
