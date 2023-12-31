#include <iostream>
#include <vector>
using namespace std;

vector<int> V, index, result;

int binary_search(int start, int end, int value) {
	int mid;
	while (start < end) {
		mid = (start + end) / 2;
		if (result[mid] < value)
			start = mid + 1;
		else
			end = mid;
	}
	return end;
}

int main()
{
	ios::sync_with_stdio;
	cin.tie(0);
	
	int N, idx;
	cin >> N;

	while (N--) {
		int tmp;
		cin >> tmp;
		V.push_back(tmp);
		index.push_back(0);
	}
	// 10 20 1 30 2 50
	// result = 1 2 30 50
	// index = 0 1 0 2 1 3
	for (int i = 0; i < V.size(); i++) {
		if (result.size() == 0 || result[result.size() - 1] < V[i]) {
			result.push_back(V[i]);
			index[i] = result.size() - 1;
		}
		else {
			idx = binary_search(0, result.size() - 1, V[i]);
			result[idx] = V[i];
			index[i] = idx;
		}
	}

	N = result.size() - 1;
	result.clear();
	cout << N + 1 << "\n";
	// 10 20 1 30 2 50
	// N = 3
	// index = 0 1 0 2 1 3
	// result = 50 30 20 10
	for (int i = index.size() - 1; i >= 0; i--)
	{
		if (index[i] == N)
		{
			N--;
			result.push_back(V[i]);
		}
	}
	for (int i = result.size() - 1; i >= 0; i--)
		cout << result[i] << " ";
	cout << "\n";

	return 0;
}
