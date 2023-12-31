#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
  	ios::sync_with_stdio(0);
  	cin.tie(0);
  	cout.tie(0);
    
	int N;
	vector<int> X, X_temp;
	int x;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x;
		X.push_back(x);
	}
	X_temp = X;
	sort(X_temp.begin(), X_temp.end());
	X_temp.erase(unique(X_temp.begin(), X_temp.end()), X_temp.end());
	//unique를 하면 중복되는 값을 벡터의 뒤로 이동시켜주고 중복되는 값이 시작되는 첫번째 위치를 반환

	for (int j = 0; j < N; j++)
		cout << lower_bound(X_temp.begin(), X_temp.end(), X[j]) - X_temp.begin() << " ";
}
