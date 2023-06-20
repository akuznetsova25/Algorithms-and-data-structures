#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>



const int INF = std::numeric_limits<int>::max();

bool comp(std::pair<int, int> a, std::pair<int, int> b) {
    return a.second > b.second;
}


class Graph {
private:
    struct Edge {
        int to;

        explicit Edge(int to) : to(to) {}
    };

    int vertex_size;
    int edges;
    int dfs_timer = 0;
    std::vector<std::vector<Edge>> adj;
    std::vector<int> start;
    std::vector<int> finish;
    std::vector<int> colors;
    std::vector<std::vector<int>> parents;

public:
    explicit Graph(int N, int M) : vertex_size(N), edges(M), start(N, 0), finish(N, 0), colors(N, 0),
    parents(N, std::vector<int>()), adj(N + 1, std::vector<Edge>()) {}

    void AddEdge(int from, int to) {
        adj[from].push_back(Edge(to));
    }

    void DFS() {
        for (int k = 0; k < vertex_size; ++k) {
            if (colors[k] == 1) {
                std::cout << -1;
                return;
            }
            if (colors[k] == 0) {
                DFS_visit(k);
            }
        }

        std::vector<std::pair<int, int>> topsort;
        for (int i = 0; i < vertex_size; ++i) {
            topsort.push_back({ i, finish[i] });
        }

        std::sort(topsort.begin(), topsort.end(), comp);
        for (int i = 0; i < vertex_size; ++i) {
            std::cout << topsort[i].first + 1 << " ";
        }
    }

    void DFS_visit(int i) {
        dfs_timer++;
        start[i] = dfs_timer;
        colors[i] = 1;
        for (auto& edge : adj[i]) {
            if (colors[edge.to] == 1) {
                return;
            }
           
            if (colors[edge.to] == 0) {
                parents[edge.to].push_back(i);
                DFS_visit(edge.to);
            }
        }
        dfs_timer++;
        finish[i] = dfs_timer;
        colors[i] = 2;
    }
};



int main()
{
    int n, m;
    std::cin >> n >> m;
    Graph graph(n, m);
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int from, to;
        std::cin >> from >> to;
        edges.push_back({ from - 1, to - 1 });
    }
    
    for (int i = 0; i < m; ++i) {
        if (edges[i].first != edges[i].second) {
            graph.AddEdge(edges[i].first, edges[i].second);
        }
        if (edges[i].first == edges[i].second) {
            std::cout << -1;
            return 0;
        }
    }
    graph.DFS();
}

