#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>

using namespace std;

class Graph {
private:
    int V; // 顶点数
    vector<vector<int>> adjMatrix; // 邻接矩阵

public:
    Graph(int V) {
        this->V = V;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int v1, int v2) {
        adjMatrix[v1][v2] = 1;
        adjMatrix[v2][v1] = 1; // 无向图
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    int getV() {
        return V;
    }

    vector<vector<int>>& getAdjMatrix() {
        return adjMatrix;
    }
};

void BFS(Graph& graph, int startVertex) {
    vector<bool> visited(graph.getV(), false);
    queue<int> queue;

    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();

        cout << "Visited " << currentVertex << endl;

        for (int i = 0; i < graph.getV(); i++) {
            if (graph.getAdjMatrix()[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                queue.push(i);
            }
        }
    }
}

void DFS(Graph& graph, int vertex, vector<bool>& visited) {
    visited[vertex] = true;
    cout << "Visited " << vertex << endl;

    for (int i = 0; i < graph.getV(); i++) {
        if (graph.getAdjMatrix()[vertex][i] == 1 && !visited[i]) {
            DFS(graph, i, visited);
        }
    }
}

void Dijkstra(Graph& graph, int startVertex) {
    vector<int> dist(graph.getV(), INT_MAX);
    vector<bool> visited(graph.getV(), false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[startVertex] = 0;
    pq.push({ 0, startVertex });

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        int currentVertex = pq.top().second;
        pq.pop();

        if (visited[currentVertex]) continue;
        visited[currentVertex] = true;

        for (int i = 0; i < graph.getV(); i++) {
            if (graph.getAdjMatrix()[currentVertex][i] == 1 && !visited[i]) {
                int newDist = currentDistance + graph.getAdjMatrix()[currentVertex][i];
                if (newDist < dist[i]) {
                    dist[i] = newDist;
                    pq.push({ newDist, i });
                }
            }
        }
    }

    for (int i = 0; i < graph.getV(); i++) {
        if (dist[i] == INT_MAX) {
            cout << "Vertex " << i << " is not reachable from " << startVertex << endl;
        }
        else {
            cout << "Distance from " << startVertex << " to " << i << " is " << dist[i] << endl;
        }
    }
}

void Prim(Graph& graph) {
    vector<int> parent(graph.getV(), -1);
    vector<int> key(graph.getV(), INT_MAX);
    vector<bool> inMST(graph.getV(), false);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graph.getV() - 1; count++) {
        int u = -1;
        int minWeight = INT_MAX;

        for (int v = 0; v < graph.getV(); v++) {
            if (!inMST[v] && key[v] < minWeight) {
                minWeight = key[v];
                u = v;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < graph.getV(); v++) {
            if (graph.getAdjMatrix()[u][v] && !inMST[v] && graph.getAdjMatrix()[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph.getAdjMatrix()[u][v];
            }
        }
    }

    for (int i = 1; i < graph.getV(); i++) {
        cout << "Edge " << parent[i] << " - " << i << " \n";
    }
}

void testBFS() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    cout << "BFS starting from vertex 0:" << endl;
    BFS(g, 0);
}

void testDFS() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    vector<bool> visited(g.getV(), false);
    cout << "DFS starting from vertex 0:" << endl;
    DFS(g, 0, visited);
}

void testDijkstra() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    cout << "Dijkstra's algorithm starting from vertex 0:" << endl;
    Dijkstra(g, 0);
}

void testPrim() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    cout << "Prim's algorithm:" << endl;
    Prim(g);
}

int main() {
    testBFS();
    testDFS();
    testDijkstra();
    testPrim();
    return 0;
}

