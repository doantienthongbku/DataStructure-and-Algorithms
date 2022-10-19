#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isBipartite(vector<vector<int>> graph) {
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    vector<int> color(graph.size(), -1);
    q.push(0);
    visited[0] = true;
    color[0] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < graph[cur].size(); i++) {
            if (!visited[graph[cur][i]]) {
                q.push(graph[cur][i]);
                visited[graph[cur][i]] = true;
                color[graph[cur][i]] = 1 - color[cur];
            } else {
                if (color[graph[cur][i]] == color[cur]) return false;
            }
        }
    }
    return true;
}

int main() {
    int G[6][6] = { {0, 1, 0, 0, 0, 1},
                    {1, 0, 1, 0, 0, 0},
                    {0, 1, 0, 1, 0, 0},
                    {0, 0, 1, 0, 1, 0},
                    {0, 0, 0, 1, 0, 1},
                    {1, 0, 0, 0, 1, 0} };
    int n = 6;

    vector<vector<int>> graph(n, vector<int>());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (G[i][j]) graph[i].push_back(j);
            }
        }

    isBipartite(graph) ? cout << "Yes" : cout << "No";
    cout << endl;

    return 0;
}