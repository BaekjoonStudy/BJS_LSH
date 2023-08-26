#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

vector<pair<long long, long long>> v;

long long CCW(pair<long long, long long> A, pair<long long, long long> B, pair<long long, long long> C)
{
	long long ccw = (A.first * B.second + B.first * C.second + C.first * A.second) - (B.first * A.second + C.first * B.second + A.first * C.second);

	if (ccw > 0)
		return 1; // 반시계
	else if (ccw == 0)
		return 0; // 일직선
	else if (ccw < 0)
		return -1; // 시계방향
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	long long x, y;
	for (int i = 0; i < 4; i++)
	{
		cin >> x >> y;
		v.push_back({ x,y });
	}

	long long ccw1 = CCW(v[0], v[1], v[2]) * CCW(v[0], v[1], v[3]);
	long long ccw2 = CCW(v[2], v[3], v[0]) * CCW(v[2], v[3], v[1]);

	if (ccw1 == 0 && ccw2 == 0) // 일직선
	{
		// 대소비교. 첫번째 인자가 같다면 두번째 인자 비교
		if (v[0] > v[1]) swap(v[0], v[1]);
		if (v[2] > v[3]) swap(v[2], v[3]);
		if (v[0] <= v[3] && v[1] >= v[2])
			cout << 1 << "\n";
		else 
			cout << 0 << "\n";
	}
	else
	{
		if (ccw1 <= 0 && ccw2 <= 0)
			cout << 1 << "\n";
		else
			cout << 0 << "\n";
	}
}
