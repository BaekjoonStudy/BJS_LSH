#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
using namespace std;

int comb(int M, int N) {
	long long x = 1, y = 1;
	if (M == N)
		return 1;
	else if (N == 1)
		return M;
	else {
		if (N > (M / 2))
			N = M - N;
		for (int i = 0; i < N; i++)
			x *= (M - i); // M!/(M-N)!
		for (int i = 1; i <= N; i++) // N!
			y *= i;
		return x / y;
	}
}

int main()
{
	int T, n, m;
	vector<int> N, M;
	vector<long long> result;
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d %d", &n, &m);
		N.push_back(n);
		M.push_back(m);
	}

	for (int i = 0; i < T; i++)
		result.push_back(comb(M[i], N[i]));

	for (int i = 0; i < T; i++) {
		printf("%lld\n", result[i]);
	}
	return 0;
}
