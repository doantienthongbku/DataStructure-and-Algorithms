#include<bits/stdc++.h> 
using namespace std;

int numberOfFriendGroups(vector<vector<int>>& friends) {
    int n = friends.size();
    vector<bool> visited(n, false);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            count++;
            queue<int> q;
            q.push(i);
            visited[i] = true;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : friends[u]) {
                    if (!visited[v]) {
                        q.push(v);
                        visited[v] = true;
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    vector<vector<int>> graph {
        {1},
        {0, 2},
        {1},
        {4},
        {3},
        {}
    };
    cout << numberOfFriendGroups(graph) << endl;    // result: 3

    return 0;
}