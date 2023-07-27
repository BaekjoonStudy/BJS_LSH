#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int func(int n) {
	if (n <= 3) {
		return 1;
	}
	else if (n <= 5) {
		return 2;
	}
		
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int T, N;
	cin >> T;

	while (T--) {
		cin >> N;
		func(N);
	}
	
	return 0;
}
