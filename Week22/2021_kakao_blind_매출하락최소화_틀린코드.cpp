#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<vector<int>> group;
vector<vector<int>> group_cost; // 팀장 cost, 팀 내 최소 cost
vector<vector<int>> group_level;
vector<int> team_leader; // team_leader[10] = 5 => 자기자신의 팀장을 저장
vector<int> attend;

int solution(vector<int> sales, vector<vector<int>> links) {
    int answer = 0;
    
    group.resize(sales.size());
    group_cost.resize(sales.size(), vector<int>(2, 1e9));
    group_level.resize(links.size());
    team_leader.resize(sales.size());
    attend.resize(sales.size());
    
    for (auto l : links) {
        group[l[0]-1].push_back(l[1]-1);
        group_cost[l[0]-1][0] = sales[l[0]-1];
        group_cost[l[0]-1][1] = min(sales[l[0]-1], group_cost[l[0]-1][1]);
        group_cost[l[0]-1][1] = min(sales[l[1]-1], group_cost[l[0]-1][1]);
        team_leader[l[1]-1] = l[0]-1;
    }
    
    group_level[0].push_back(0); // CEO
    
    int max_level = 0;
    queue<pair<int,int>> q;
    q.push({0,0});
    while (!q.empty()) {
        int leader = q.front().first;
        int level = q.front().second;
        max_level = max(level, max_level);
        q.pop();
        
        for (int member : group[leader]) {
            if (group[member].size() == 0) // 팀장이 아니면
                continue;
            group_level[level+1].push_back(member);
            q.push({member, level+1});
        }
    }
    // for (int i = 0; i <= max_level; i++) {
    //     cout << i << " : ";
    //     for (int j : group_level[i]) {
    //         cout << j << " ";
    //     }
    //     cout << "\n";
    // }
    
    // for (int i = 0; i <= max_level; i++) {
    //     for (int j : group_level[i]) {
    //         cout << j << " : " << group_cost[j][0] << "," << group_cost[j][1] << "\n";
    //     }
    // }
    
    for (int i = max_level; i > 0; i--) {
        for (int j : group_level[i]) {
            if (attend[j] == 1) // 참석할 직원 선정 완료
                continue;
            int leader_cost = group_cost[j][0]; int min_cost1 = group_cost[j][1];
            int leader_leader = team_leader[j];
            int leader_cost2 = group_cost[leader_leader][0]; int min_cost2 = group_cost[leader_leader][1];
            if (attend[leader_leader] == 1) {
                leader_cost2 = 1; min_cost2 = 0;
            }
            
            if (leader_cost < min_cost1 + min_cost2) {
                answer += leader_cost;
                attend[j] = 1;
                attend[leader_leader] = 1;
            }
            else {
                answer += (min_cost1 + min_cost2);
                attend[j] = 1;
                attend[leader_leader] = 1;
                if (leader_cost2 == min_cost2 && leader_leader != 0) { // 상위 팀의 최소 cost가 상위 팀 팀장일 경우
                    // 상위 팀의 상위 팀까지 참석할 직원 선정 완료 표시
                    attend[team_leader[leader_leader]] = 1;
                }
            }
        }
    }
    
    if (attend[0] == 0) { // CEO가 속한 팀이 아직 직원 선정을 못했다면
        answer += group_cost[0][1];
    }
    
    return answer;
}
