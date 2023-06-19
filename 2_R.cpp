#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <set>

const int INF = std::numeric_limits<int>::max();

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
    std::vector<int> color;
    std::vector<int> fup;
    std::set<int> artic_points;
    
public:
    explicit Graph(int N, int M) : vertex_size(N), edges(M), color(N + 1, 0), start(N + 1, 0), fup(N + 1, INF),
        adj(N + 1, std::vector<Edge>()) {}

    void AddEdge(int from, int to) {
        adj[from].push_back(Edge(to));
        adj[to].push_back(Edge(from));
    }

    void DFS() {
        for (int i = 1; i <= vertex_size; ++i) {
            DFS_visit(i, -1);
        }
    }

    void DFS_visit(int u, int parent) {
        dfs_timer++;
        start[u] = dfs_timer;
        color[u] = 1;
        fup[u] = start[u];
        int counter = 0;

        for (auto& edge : adj[u])
        {
            if (edge.to == parent) {
                continue;
            }

            if (color[edge.to] == 0) {
                DFS_visit(edge.to, u);
                fup[u] = std::min(fup[u], fup[edge.to]);
                if (parent != -1 && fup[u] >= start[u]) {
                    artic_points.insert(u);
                }
                counter++;
            }

            if (color[edge.to] == 1) {
                fup[u] = std::min(fup[u], start[edge.to]);
            }
        }
        if (parent == -1) {
            if (counter > 1) {
                artic_points.insert(u);
            }
        }
    }

    void print() {
        std::set <int>::iterator it;
        for (it = artic_points.begin(); it != artic_points.end(); ++it)
        {
            std::cout << *it;
            std::cout << std::endl;
        }
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
        edges.push_back({ from, to });
    }

    for (int i = 0; i < m; ++i) {
        if (edges[i].first != edges[i].second) {
            graph.AddEdge(edges[i].first, edges[i].second);
        }

        if (edges[i].first == edges[i].second) {
            continue;
        }
    }
    graph.DFS();
    graph.print();

    return 0;
}

