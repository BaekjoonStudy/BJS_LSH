#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<pair<int, int>> V;
	int n, a, b, m = 1, count = 0;
	int length[100];

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);
		V.push_back({ a, b });
	}

	sort(V.begin(), V.end());

	for (int k = 0; k < n; k++) {
		length[k] = 1;
		for (int i = 0; i < k; i++) {
			if (V[i].second < V[k].second) {
				length[k] = max(length[k], length[i] + 1);
				if (m < length[k])
					m = length[k];
			}
		}
	}
	
	printf("%d\n", n - m);
	return 0;
}