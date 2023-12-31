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
	int result = 0;

	if (C == 2)
		result = end;
	else {
		while (start <= end) {
			int mid = (end + start) / 2; // 비교 간격
			int prev = 0, count = 1; // 첫번째 집에 공유기 설치

			for (int i = prev + 1; i < N; i++) {
				if ((V[i] - V[prev]) >= mid) { // mid보다 간격이 크거나 같다면
					count++; // i번째 집에 공유기 설치
					prev = i; // prev를 i번째로 바꿈
				}
			}
			if (count >= C) { // C와 같거나 많은 수의 공유기를 설치했다면
				result = mid; // result 값 업데이트
				start = mid + 1; // 비교 간격을 키우기 위해 start를 키움
			}
			else // C보다 적은 수의 공유기를 설치했다면
				end = mid - 1; // 비교 간격을 줄이기 위해 end를 줄임
		}
	}

	cout << result << "\n";

	return 0;
}
