#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, C;
	int tmp;
	vector<int> V;
	cin >> N >> C;

	for (int i = 0; i < N; i++) {
		cin >> tmp;
		V.push_back(tmp);
	}
	sort(V.begin(), V.end());

	int start = 1;
	int end = V[N - 1] - V[0];
	int max = 0;
	if (C == 2)
		max = end;
	else {
		while (start <= end) {
			int mid = (end + start) / 2;
			int prev = 0, count = 1; // 첫번째 집에 공유기 설치

			for (int i = prev + 1; i < N; i++) {
				if ((V[i] - V[prev]) >= mid) { // mid보다 간격이 크거나 같은 
					count++;
					prev = i;
				}
			}
			if (count >= C) {
				max = (max > mid) ? max : mid;
				start = mid + 1;
			}
			else
				end = mid - 1;
		}
	}

	cout << max << "\n";

	return 0;
}