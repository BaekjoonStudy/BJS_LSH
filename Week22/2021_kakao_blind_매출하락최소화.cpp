#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<int> s;
vector<vector<int>> team;
vector<vector<int>> team_level; // 임출력 예 1) team_level[0] = 0 [1] = 8,4 [2] = 9
vector<vector<int>> dp; // dp[0] = {1,2} => 0번 팀원이 참석하지 않는 경우 1원, 참석하는 경우 2원

int find_level() {
    int level;
    queue<pair<int,int>> q; // 회원번호, level
    q.push({0,0});
    
    while (!q.empty()) {
        int cur = q.front().first;
        level = q.front().second;
        team_level[level].push_back(cur);
        q.pop();
        
        for (auto t : team[cur]) {
            if (team[t].size() == 0)
                continue;
            q.push({t, level+1});
        }
    }
    return level;
}

void func(int level) {
    // level : 현재 레벨
    if (level == -1)
        return;
    
    for (auto leader : team_level[level]) {
        int tmp = 0; int member_min = 1e9; int isbool = 0;
        for (auto member : team[leader]) {
            if (team[member].size() == 0) {
                dp[member][0] = 0;
                dp[member][1] = s[member];
            }
            else {
                if (dp[member][1] <= dp[member][0]) // 팀장이면서 팀원인 사원이 선택됨
                    isbool = 1;
            }
            tmp += min(dp[member][0], dp[member][1]);
        }
        for (auto member : team[leader]) {
            if (team[member].size() == 0) {
                dp[member][1] += tmp;
            }
            else {
                dp[member][1] += (tmp - min(dp[member][0], dp[member][1]));
            }
            member_min = min(member_min, dp[member][1]);
        }
        
        if (isbool == 0) // 팀원들 중 무조건 한명은 선택해야됨
            dp[leader][0] = member_min;
        else // 팀장이면서 팀원인 사원이 이미 선택되었음
            dp[leader][0] = tmp;
        dp[leader][1] = tmp + s[leader];
        // cout << leader << ";" << dp[leader][0] << "," << dp[leader][1] << "\n";
    }
    func(level-1);
}

int solution(vector<int> sales, vector<vector<int>> links) {
    int answer = 0;
    
    s = sales;
    team.resize(sales.size());
    team_level.resize(links.size());
    dp.resize(sales.size(), vector<int>(2));
    
    for (auto l : links)
        team[l[0]-1].push_back(l[1]-1);

    int level = find_level();
    // cout << level << "\n";
    func(level);
    answer = min(dp[0][0],dp[0][1]);
    return answer;
}
