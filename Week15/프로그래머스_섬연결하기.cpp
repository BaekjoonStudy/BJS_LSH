#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int group[100];

bool comp(vector<int> x, vector<int> y) {
    return x[2] < y[2];
}

int find(int x) {
    if (group[x] == x)
        return x;
    return group[x] = find(group[x]);
}

bool is_diff_group(int x, int y) { // union
    int parent_x = find(x);
    int parent_y = find(y);
    
    if (parent_x == parent_y)
        return false;
    group[parent_x] = group[parent_y];
    return true;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    
    sort(costs.begin(), costs.end(), comp); // 비용에 대해 오름차순으로 정렬
    
    for (int i = 0; i < n; i++) {
        group[i] = i;
    }
    
    for (int i = 0; i < costs.size(); i++) {
        if (is_diff_group(costs[i][0], costs[i][1]))
            answer += costs[i][2];
    }
    
    return answer;
}
