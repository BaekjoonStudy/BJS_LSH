#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int alp, int cop, vector<vector<int>> problems) {
    int answer = 0;
    int alp_max = 0, cop_max = 0;
    
    for (auto p : problems) {
        alp_max = max(alp_max, p[0]);
        cop_max = max(cop_max, p[1]);
    }

    if (alp_max <= alp && cop_max <= cop) {
        return 0;
    }
    vector<vector<int>> dp(alp_max + 1, vector<int>(cop_max + 1, 1e9)); // 벡터 동적 할당
    if (alp > alp_max) {
        alp = alp_max;
    }
    if (cop > cop_max) {
        cop = cop_max;
    }
    dp[alp][cop] = 0;
    for (int i = alp; i <= alp_max; i++) {
        for (int j = cop; j <= cop_max; j++) {
            if (i + 1 <= alp_max) 
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
            if (j + 1 <= cop_max) 
                dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);
            for (auto p : problems) {
                if (i >= p[0] && j >= p[1]) { // 요구사항을 만족한다면
                    dp[min(i + p[2], alp_max)][min(j + p[3], cop_max)] = min(dp[min(i + p[2], alp_max)][min(j + p[3], cop_max)], dp[i][j] + p[4]);
                }
            }
        }
    }
    
    answer = dp[alp_max][cop_max];
    return answer;
}
