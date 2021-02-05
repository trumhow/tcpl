#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (auto& num : nums) freq[num]++;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        for (auto& it : freq) {
            if (pq.size() == k) {
                if (it.second > pq.top().first) {
                    pq.pop();
                    pq.push(make_pair(it.second, it.first));
                }
            }
            else {
                pq.push(make_pair(it.second, it.first));
            }
        }

        vector<int> ans;
        while (!pq.empty()) {
            ans.push_back(pq.top().second);
            pq.pop();
        }

        return ans;
    }
};
