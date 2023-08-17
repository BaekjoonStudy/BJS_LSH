#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> base, acid;

int main()
{
	ios::sync_with_stdio;
	cin.tie(0);
	
	int N;
	cin >> N;

	int isBase = 0, isAcid = 0;
	while (N--) {
		long long tmp;
		cin >> tmp;
		if (tmp < 0) {
			base.push_back(tmp);
			isBase = 1;
		}
		else {
			acid.push_back(tmp);
			isAcid = 1;
		}
	}

	sort(base.begin(), base.end());
	sort(acid.begin(), acid.end());

	if (isBase == 1 && isAcid == 0) // 염기성 용액만 있을 경우
		cout << base[base.size() - 2] << " " << base[base.size() - 1] << "\n";

	else if (isBase == 0 && isAcid == 1) // 산성 용액만 있을 경우
		cout << acid[0] << " " << acid[1] << "\n";

	else {
		int result1 = 0, result2 = 0;
		long long sum = 999999999;

		if (base.size() >= 2) { // 염기성 용액끼리만 혼합
			sum = -(base[base.size() - 2] + base[base.size() - 1]);
			result1 = base[base.size() - 2];
			result2 = base[base.size() - 1];
		}
			
		if (acid.size() >= 2) { // 산성 용액끼리만 혼합
			if (sum > (acid[0] + acid[1])) { // 염기성 용액끼리만 혼합한 경우와 비교하여 갱신
				sum = acid[0] + acid[1];
				result1 = acid[0];
				result2 = acid[1];
			}
		}

		for (int i = 0; i < base.size(); i++) { 
			int start = 0, end = acid.size() - 1;
			int mid = 0, prev_mid;
			int value = -base[i];
			int isSame = 0;
			while (start <= end) { // 이분탐색
				prev_mid = mid;
				mid = (start + end) / 2;
				if (acid[mid] == value) {
					isSame = 1;
					break;
				}
				else if (acid[mid] > value)
					end = mid - 1;
				else
					start = mid + 1;
			}

			if (isSame == 1) {
				result1 = base[i];
				result2 = acid[mid];
				break;
			}

			// [10, 30, 40] value = 25 일 때 이분탐색 후 mid가 10을 가리키는 경우가 발생함.
			// 때문에 prev_mid를 선언해 30을 가리키게 한 후 mid와 prev_mid 중 value와의 차가 더 작은 인덱스를 j에 저장하도록 함.
			int diff1 = (acid[prev_mid] > value) ? acid[prev_mid] - value : value - acid[prev_mid];
			int diff2 = (acid[mid] > value) ? acid[mid] - value : value - acid[mid];
			int j = (diff1 > diff2) ? j = mid : j = prev_mid;

			long long sum_tmp = (base[i] + acid[j]) > 0 ? base[i] + acid[j] : -(base[i] + acid[j]);
			if (sum_tmp < sum) {
				result1 = base[i];
				result2 = acid[j];
				sum = sum_tmp;
			}
		}
		cout << result1 << " " << result2 << "\n";
	}
	
	return 0;
}
