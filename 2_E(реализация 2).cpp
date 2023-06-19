#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#include <vector>
#include <cmath>


template <typename T>
using matr = std::vector<std::vector<int>>;
const int INTMAX = std::numeric_limits<int>::max();


class Graph {
private:
    int n, m;
    std::vector<int> graph;
    std::vector<bool> used;
    std::vector<int> distances;


public:
    std::vector<std::vector<int>> adjacency;
    explicit Graph(int N, int M) : n(N), m(M), distances(n* m + 1, INTMAX),
        used(n* m + 1, false), graph(n* m + 1), adjacency(n* m + 1, std::vector<int>()) {
        //for (int i = 0; i <= n * m; ++i) {
        //    adjacency[i].resize(n * m + 1); 
        //}

        for (int i = 1; i <= n * m; ++i) {
            int value;
            std::cin >> value;
            graph[i] = value;
            if (value == 1) {
                adjacency[0].push_back(i);
            }
        }

        for (int j = 1; j <= n * m; ++j) {
            if (j % m != 0) {
                adjacency[j].push_back(j + 1);
            }
            if (j % m != 1) {
                adjacency[j].push_back(j - 1);
            }
            if (j <= m) {
                adjacency[j].push_back(j + m);
            }
            if (j >= adjacency.size() - m) {
                adjacency[j].push_back(j - m);
            }
            if (j > m&& j < adjacency.size() - m) {
                adjacency[j].push_back(j + m);
                adjacency[j].push_back(j - m);
            }
        }
    }

    void bfs(int start) {
        std::queue<int> bfs_neighnours;
        used[start] = true;
        distances[start] = 0;
        bfs_neighnours.push(start);

        while (!bfs_neighnours.empty()) {
            int vertex = bfs_neighnours.front();
            bfs_neighnours.pop();

            for (const auto& edge : adjacency[vertex]) {
                if (!used[edge]) {
                    used[edge] = true;
                    distances[edge] = distances[vertex] + 1;
                    bfs_neighnours.push(edge);
                }
            }
        }
    }

    void print() {
        int k = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                std::cout << distances[k] - 1 << " ";
                k++;
            }
            std::cout << std::endl;
        }
    }

};



int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m;
    Graph Maps(n, m);
    Maps.bfs(0);
    Maps.print();

    return 0;
}



