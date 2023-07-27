#include <iostream>
using namespace std;

int main(void)
{
	ios::sync_with_stdio(0);
    	cin.tie(0);
    	cout.tie(0);
	
	int sugar, num;
	cin >> sugar;
	if (sugar % 5 == 0)
		num = sugar / 5;
	else if ((sugar % 5 == 1 || sugar % 5 == 3) && sugar >= 8) {
		num = sugar / 5 + 1;
		// 나머지가 1일때 : 11 = 5 + 3*2
		// 나머지가 3일때 : 13 = 5*2 + 3
	}
	else if (sugar % 5 == 2 && sugar >= 17)
		num = sugar / 5 + 2;
		// 나머지가 2일때 : 17 = 5 + 3*4
	else if (sugar % 5 == 4 && sugar >= 8) {
		num = sugar / 5 + 2;
		// 나머지가 4일때 : 14 = 5 + 3*3
	}
	else if (sugar % 3 == 0)
		num = sugar / 3;
	else
		num = -1;

	cout << num << endl;
}
