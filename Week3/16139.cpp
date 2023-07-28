#include <iostream>
#include <string>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	string str, s;
	int q, l, r, idx, check = 0;
	int S[200000][26] = { 0 };
	char a;

	cin >> str >> q;
	while (q--) {
		cin >> a >> l >> r;

		if (!check) {
			// ex : [a,a,b,a,b]
			// S = [(1,0), (2,0), (2,1), (3,1), (3,2)]
			// 만약 l=2, r=4 구간에서 'a' 개수를 알고싶으면
			// S[4][0] - S[1][0] = 3 - 2 = 1 해주면 됨
			for (int i = 0; i < str.length(); i++) {
				idx = int(str[i] - 'a');
				S[i][idx]++;
				if (i != str.length() - 1) {
					for (int j = 0; j < 26; j++)
						S[i + 1][j] = S[i][j]; // S[i + 1][j]++
				}			
			}
			check = 1;
		}

		idx = int(a - 'a');
		if (l == 0)
			cout << S[r][idx] << "\n";
		else
			cout << S[r][idx] - S[l - 1][idx] << "\n";
	}
	return 0;
}
