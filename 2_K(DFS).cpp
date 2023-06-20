#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>


class Graph {
private:
    struct Edge {
        int to;

        explicit Edge(int to) : to(to) {}
    };

    int vertex_size;
    int edges;
    int index = -1;
    std::vector<std::vector<Edge>> adj;
    std::vector<char> finish;
    std::vector<int> colors;
    std::vector<int> way;
    std::vector<int> answers;

public:
    explicit Graph(int N, int M) : vertex_size(N), edges(M), colors(N, 0), adj(N + 1, std::vector<Edge>()) {}

    void AddEdge(int from, int to) {
        adj[from].push_back(Edge(to));
    }

    void DFS() {
        for (int k = 0; k < vertex_size; ++k) {
            if (colors[k] == 0) {
                DFS_visit(k);
            }
        }
        if (finish.empty()) {
            std::cout << "NO";
        }
    }

    void DFS_visit(int k) {
        
            colors[k] = 1;
            way.push_back(k);
            index++;
            for (auto& edge : adj[k]) {
                if (finish.empty()) {
                    if (colors[edge.to] == 1) {
                        std::cout << "YES" << std::endl;
                        finish.push_back('YES');

                        while (way[index] != edge.to) {
                            answers.push_back(way[index]);
                            index--;
                        }

                        answers.push_back(edge.to);
                        std::reverse(answers.begin(), answers.end());
                        for (auto i = answers.begin(); i != answers.end(); ++i) {
                            std::cout << *i + 1 << " ";
                        }
                        break;
                    }

                    else if (colors[edge.to] == 0) {
                        DFS_visit(edge.to);
                    }
                }
            }
            way.pop_back();
            colors[k] = 2;
            index--;
        
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
            std::cout << "YES" << std::endl;
            std::cout << edges[i].first + 1;
            return 0;
        }
    }
    graph.DFS();
}


