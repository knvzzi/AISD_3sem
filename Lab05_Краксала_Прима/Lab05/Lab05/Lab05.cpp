#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int V = 8; // Количество вершин

// Функция для нахождения минимального остовного дерева с использованием алгоритма Прима
void primMST(const vector<vector<int>>& graph) {

    vector<int> used;
    used.push_back(0); // стартовая вершина - 1

    struct Edge { int from, weight, to; };
    vector<Edge> result;

    for (size_t i{}; i < graph.size(); i++) {

        Edge minEdge{ -1, 0x7f, -1 };
        for (size_t row{}; row < graph.size(); row++) {
            if (find(used.begin(), used.end(), row) == used.end()) 
                continue; 

            for (size_t col{}; col < graph[row].size(); col++) {
                if (find(used.begin(), used.end(), col) != used.end())
                    continue;

                if (graph[row][col] == 0)
                    continue;

                if (minEdge.weight > graph[row][col]) {
                    minEdge.from = row;
                    minEdge.to = col;
                    minEdge.weight = graph[row][col];
                }
            }
            
        }

        if (minEdge.from != -1) {

            used.push_back(minEdge.to);
            result.push_back(minEdge);
        }

    }
    
    cout << "Алгоритм Прима (минимальное остовное дерево):" << endl;
    for (auto edge : result)
        cout << "Ребро: " << edge.from + 1 << " - " << edge.to + 1 << "  Вес: " << edge.weight << endl;

}

// Функция для нахождения минимального остовного дерева с использованием алгоритма Краскала
void kruskalMST(const vector<vector<int>>& graph) {
    
    struct Edge {
        int src, dest, weight;
    };

    vector<Edge> edges; 

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != 0) {
                edges.push_back({ i, j, graph[i][j] });
            }
        }
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
        });

    vector<int> parent(V, -1); 

    cout << "Алгоритм Краскала:" << endl;
    for (const Edge& edge : edges) {
        int x = edge.src;
        int y = edge.dest;

        while (parent[x] != -1) {
            x = parent[x];
        }
        while (parent[y] != -1) {
            y = parent[y];
        }

        if (x != y) {
            cout << "Ребро: " << edge.src+1 << " - " << edge.dest+1 << "  Вес: " << edge.weight << endl;
            parent[x] = y;
        }
    }
}

int main() {
    setlocale(LC_CTYPE, "rus");
    vector<vector<int>> graph = {
        {0, 2, 0, 8, 2, 0, 0, 0},
        {2, 0, 3, 10, 5, 0, 0, 0},
        {0, 3, 0, 0, 12, 0, 0, 7},
        {8, 10, 0, 0, 14, 3, 1, 0},
        {2, 5, 12, 14, 0, 11, 4, 8},
        {0, 0, 0, 3, 11, 0, 6, 0},
        {0, 0, 0, 1, 4, 6, 0, 9},
        {0, 0, 7, 0, 8, 0, 9, 0}
    };

    primMST(graph);
    kruskalMST(graph);

    return 0;
}
