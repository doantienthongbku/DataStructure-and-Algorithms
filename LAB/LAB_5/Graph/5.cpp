#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Adjacency
{
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	void push(int data)
	{
		adjList.push_back(data);
		size++;
	}
	void print()
	{
		for (auto const &i : adjList)
			cout << " -> " << i;
	}
	void printArray()
	{
		for (auto const &i : adjList)
			cout << i << " ";
	}
	int getSize() { return adjList.size(); }
	int getElement(int idx) 
	{
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};

class Graph {

    int V;
    Adjacency* adj;

public:
    Graph(int V){
        this->V = V;
        adj = new Adjacency[V];
    }
    void addEdge(int v, int w){
        adj[v].push(w);
    }
    
    //Heling functions
    void topologicalSortRec(int v, bool visited[], stack<int>& Stack) {
        visited[v] = true;
        for (int i = 0; i < adj[v].getSize(); i++) {
            int n = adj[v].getElement(i);
            if (!visited[n])
                topologicalSortRec(n, visited, Stack);
        }
        Stack.push(v);
    }
    
    void topologicalSort() {
        stack<int> Stack;
        bool* visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;
        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                topologicalSortRec(i, visited, Stack);
        while (Stack.empty() == false) {
            cout << Stack.top() << " ";
            Stack.pop();
        }
    }
};

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    g.topologicalSort();
    cout << endl;
    // result: 5 4 2 3 1 0 

    return 0;
}