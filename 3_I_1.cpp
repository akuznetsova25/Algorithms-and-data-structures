#include <iostream>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>


const int kIntmax = 30000;


bool RelaxEdge(std::vector<int> &distance, int from, int to, int weight) {
    bool did_something = false;
    if (distance[from] < kIntmax) {
        if (distance[to] > distance[from] + weight) {
            distance[to] = distance[from] + weight;
            did_something = true;
        }
    }
    return did_something;
}


std::vector<int> FordBellman(std::vector<std::vector<int>> &graph, int start, int size) {
    std::vector<int> distance(size, kIntmax);
    distance[start] = 0;
    for (int i = 0; i < size - 1; ++i) {
        bool did_something = false;
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                if (graph[j][k] == 0) {
                    continue;
                }
                if (RelaxEdge(distance, j, k, graph[j][k])) {
                    did_something = true;
                }
            }
        }
        if (!did_something) {
            break;
        }
    }
    return distance;
}



int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> edges(n);
    std::vector<int> final_distance;

    for (int i = 0; i < n; ++i) {
        edges[i].resize(n);
        for (int j = 0; j < n; ++j) {
            edges[i][j] = 0;
        }
    }

    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        if ((from != to) && (edges[from][to] == 0)) {
            edges[from - 1][to - 1] = weight;
        }
    }

    final_distance = FordBellman(edges, 0, n);
    for (int i = 0; i < n; ++i) {
        std::cout << final_distance[i] << " ";
    }

    return 0;
}


