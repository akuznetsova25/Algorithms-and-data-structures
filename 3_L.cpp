#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>

const int kInf = 2009000999;


std::vector<int> Dijkstra(std::vector<std::vector<std::pair<int, int>>>& graph, int start) {

    const int size = graph.size();
    std::vector<int> distance(size, kInf);
    distance[start] = 0;
    std::set<std::pair<int, int>> s;
    s.insert({ distance[start], start });

    while (!s.empty()) {
        int from = s.begin()->second;
        s.erase(s.begin());

        for (int i = 0; i < graph[from].size(); ++i) {

            int next = graph[from][i].first;
            int weight = graph[from][i].second;

            if (distance[next] > distance[from] + weight) {
                s.erase({ distance[next], next });
                distance[next] = distance[from] + weight;
                s.insert({ distance[next], next });
            }
        }
    }
    return distance;
};



int main()
{
    int num;
    std::cin >> num;
    int k = 0;
    std::vector<std::vector<int>> general_distance(num);

    while (k < num) {
        int n, m, vertex;
        std::cin >> n >> m;
        std::vector<std::vector<std::pair<int, int>>> initial_graph(n);
        std::vector<int> final_distance;

        for (int i = 0; i < m; ++i) {
            int from, to, weight;
            std::cin >> from >> to >> weight;
            if (from != to) {
                initial_graph[from].push_back({ to, weight });
                initial_graph[to].push_back({ from, weight });
            }
        }
        std::cin >> vertex;

        final_distance = Dijkstra(initial_graph, vertex);
        general_distance[k] = final_distance;
        k++;
    }

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < general_distance[i].size(); ++j) {
            std::cout << general_distance[i][j] << " "; 
        }
        std::cout << std::endl;
    }

    return 0;
}
