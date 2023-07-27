#include <iostream>
#include <vector>
using namespace std;

vector<int> A, B;

int hanoi(int start, int end, int n) {
	if (n == 1) {
		A.push_back(start);
		B.push_back(end);
		return 1;
	}
	else
		return hanoi(start, 6 - start - end, n - 1) + hanoi(start, end, 1) + hanoi(6 - start - end, end, n - 1);
	// 6 - start - end �� �׻� start�� end�� �ƴ� �������� ��ȯ��
	// ex) start = 1, end = 2�̸� 6-start-end�� 3
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int N, K;

	cin >> N;
	cout << hanoi(1, 3, N) << "\n";

	for (int i = 0; i < A.size(); i++)
		cout << A[i] << " " << B[i] << "\n";

	return 0;
}