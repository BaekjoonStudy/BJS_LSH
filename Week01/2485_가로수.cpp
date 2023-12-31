#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b)
{
	int c;
	while (b != 0)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);
  	cout.tie(0);

	int N, x, interval, sum = 0;
	vector<int> V, I, temp;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x;
		V.push_back(x);
	}

	sort(V.begin(), V.end());
	for (int i = 1; i < N; i++) {
		I.push_back(V[i] - V[i - 1]);
	}

	sort(I.begin(), I.end());
	temp = I;
	temp.erase(unique(temp.begin(), temp.end()), temp.end());
	interval = temp[0];
	for (int i = 1; i < temp.size(); i++) {
		interval = gcd(temp[i], interval);
	}

	int j = 0;
	while (j < I.size() && I[j] % interval == 0) {
		sum += (I[j] / interval - 1);
		j++;
	}

	if (j != I.size())
		sum = V[V.size() - 1] - V[0] - N + 1;

	cout << sum << endl;
}
