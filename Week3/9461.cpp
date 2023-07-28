#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

long long result[100] = { 1,1,1,2,2,3,4,5,7,9 };

long long func(int n) {
	if (result[n - 1] != 0)
		return result[n - 1];
	else {
		result[n - 1] = func(n - 1) + func(n - 5);
		return result[n - 1];
	}
}

int main()
{

	int T, N;
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &N);
		printf("%lld\n", func(N));
	}

	return 0;
}
