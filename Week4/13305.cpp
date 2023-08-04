#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, tmp, sum = 0;
	long long result = 0;
	vector<long long> Length, City;
	cin >> N;

	for (int i = 0; i < N - 1; i++) {
		cin >> tmp;
		sum += tmp;
		Length.push_back(sum);
		// �Է��� 2 3 1 �̸� [2, 5, 6]���� ����
	}

	for (int i = 0; i < N; i++) {
		cin >> tmp;
		City.push_back(tmp);
	}
	
	// Length[2,5,6] City[5,2,4,1]�� ��
	// i = 0, j = 1���� C[0] > C[1]�̱� ������ ���� while���� ����
	// result += C[0] * L[0] = 5 * 2 = 10
	// i = 1, j = 3���� j < 3 ������ �������� ���ϹǷ� ���� while���� ����
	// result += C[1] * (L[2] - L[0]) = 2 * (6 - 2) = 8 ==> 18
	int i = 0;
	while (i < N - 1) {
		int j = i + 1;
		while (j < N -1) {
			if (City[i] > City[j])
				break;
			else
				j++;
		}
		if (i == 0)
			result += (City[i] * Length[(j - 1)]);
		else
			result += (City[i] * (Length[(j - 1)] - Length[(i - 1)]));
		i = j;
	}
	cout << result << "\n";

	return 0;
}