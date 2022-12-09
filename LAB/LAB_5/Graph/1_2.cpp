#include <iostream>
#include <list>
using namespace std;

class Adjacency {
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	void push(int data) {
		adjList.push_back(data);
		size++;
	}
	void print() {
		for (auto const &i : adjList)
			cout << " -> " << i;
	}
	void printArray() {
		for (auto const &i : adjList)
			cout << i << " ";
	}
	int getSize() { return adjList.size(); }
	int getElement(int idx) {
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};

class Graph {
private:
	int V;
	Adjacency *adj;

public:
	Graph(int V) {
		this->V = V;
		adj = new Adjacency[V];
	}
	
	void addEdge(int v, int w) {
		adj[v].push(w);
		adj[w].push(v);
	}
	
    void printGraph() {
		for (int v = 0; v < V; ++v) {
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}
	
	Adjacency *BFS(int v) {
        // Implement Depth-first search

        int visited[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;
        
        Adjacency* arr = new Adjacency(V);
        list<int> queue;
        visited[v] = true;
        queue.push_back(v);
        arr->push(v);

        while (!queue.empty()) {
            v = queue.front();
            queue.pop_front();

            for (int i = 0; i < adj[v].getSize(); i++) {
                int w = adj[v].getElement(i);
                if (!visited[w]) {
                    visited[w] = true;
                    queue.push_back(w);
                    arr->push(w);
                }
            }
        }
        return arr;
    }

    void DFSUtil(int v, int visited[], Adjacency* arr) {
        visited[v] = true;
        arr->push(v);

        for (int i = 0; i < adj[v].getSize(); i++) {
            int w = adj[v].getElement(i);
            if (!visited[w])
                DFSUtil(w, visited, arr);
        }
    }

    Adjacency *DFS(int v) {
        // v is a vertex we start DFS

        int visited[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;
        
        Adjacency* arr = new Adjacency(V);
        DFSUtil(v, visited, arr);
        return arr;
	}
};

int main() {
    int V = 8, visited = 0;

    Graph g(V);
    Adjacency *arr;
    int edge[][2] = {{0,1}, {0,2}, {0,3}, {0,4}, {1,2}, {2,5}, {2,6}, {4,6}, {6,7}};
    for(int i = 0; i < 9; i++) {
        g.addEdge(edge[i][0], edge[i][1]);
    }

    // g.printGraph();
    // cout << endl;
    arr = g.DFS(visited);
    arr->printArray();
    delete arr;
    // result: 0 1 2 5 6 4 7 3

    return 0;
}