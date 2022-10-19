#include <iostream>
#include <vector>
#include <queue>
using namespace std;


void bfs(vector<vector<int>> graph, int start) {
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << cur << " ";
        for (int i = 0; i < graph[cur].size(); i++) {
            if (!visited[graph[cur][i]]) {
                q.push(graph[cur][i]);
                visited[graph[cur][i]] = true;
            }
        }
    }
}

int main() {
	int init_graph[10][10] = {  {0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
                                {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
                                {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
                                {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
                                {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                                {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
                                {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
                                {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
                                {1, 0, 1, 0, 1, 0, 0, 0, 1, 0} };
	int n = 10;
	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (init_graph[i][j]) graph[i].push_back(j);
		}
	}

    cout << "==========================" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << "==========================" << endl;

	bfs(graph, 0);

    return 0;
}