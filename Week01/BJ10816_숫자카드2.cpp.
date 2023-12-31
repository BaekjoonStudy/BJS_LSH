#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);
  	cout.tie(0);

	int N1, N2, x, index1, index2, index3;
	vector<pair<int, int>> V;
	vector<int> V1, V2;

	cin >> N1;
	for (int i = 0; i < N1; i++) {
		cin >> x;
		V.push_back({ x,0 });
		V1.push_back(x);
	}
	sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()), V.end());

	cin >> N2;
	for (int i = 0; i < N2; i++) {
		cin >> x;
		V2.push_back(x);
	}

	sort(V1.begin(), V1.end());
	int j = 0;
	for (int i = 0; i < V.size(); i++) {
		index1 = lower_bound(V1.begin(), V1.end(), V1[j]) - V1.begin();
		index2 = upper_bound(V1.begin(), V1.end(), V1[j]) - V1.begin();
		V[i].second = index2 - index1;
		j = index2;
	}

	V1.erase(unique(V1.begin(), V1.end()), V1.end());
	for (int i = 0; i < N2; i++) {
		index3 = lower_bound(V1.begin(), V1.end(), V2[i]) - V1.begin();
		if (V[index3].first == V2[i])
			cout << V[index3].second << " ";
		else
			cout << 0 << " ";
	}
	cout << endl;
}
