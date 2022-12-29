// Question Link: https://leetcode.com/problems/single-threaded-cpu/description/

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        vector<array<int, 3>> sortedTasks;
        for (int i = 0; i < tasks.size(); i++) {
            sortedTasks.push_back({tasks[i][0], tasks[i][1], i});
        }
        sort(sortedTasks.begin(), sortedTasks.end());

        int i = 0, currTime = 0;
        vector<int> solution;
        while (i < tasks.size()) {
            if (pq.empty() && currTime < sortedTasks[i][0]) {
                currTime = sortedTasks[i][0];
            }

            if (sortedTasks[i][0] <= currTime) {
                pq.push({sortedTasks[i][1], sortedTasks[i][2]});
                i++;
                continue;
            }

            solution.push_back(pq.top().second);
            currTime += pq.top().first;

            pq.pop();
        }

        while(!pq.empty()) {
            solution.push_back(pq.top().second);
            pq.pop();
        }

        return solution;
    }
};