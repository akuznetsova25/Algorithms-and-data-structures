#include <queue>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>>

std::vector<int> Dijkstra(std::vector<std::vector<std::pair<int, int>>>& graph,
    int v) {
    const int INF = 2'000'000'000;
    const int size = graph.size();
    std::vector<int> distance(size, INF);
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

const int INF = 2'000'000'000;

struct Edge {
    int from;
    int to;
    int weight;
};


bool RelaxEdge(std::vector<int> distance, Edge &edge) {
    bool did_something;
    if (distance[edge.from] < INF) {
        if (distance[edge.to] > distance[edge.from] + edge.weight) {
            distance[edge.to] = distance[edge.from] + edge.weight;
            did_something = true;
        }
    }
    return did_something;
}


std::vector<int> FordBellman(std::vector<Edge> &graph, int start, int size) {
    std::vector<int> distance(size, INF);
    distance[start] = 0;
    for (int i = 0; i < size - 1; ++i) {
        bool did_something = false;
        for (Edge edge : graph) {
            if (RelaxEdge(distance, edge)) {
                did_something = true;
            }
        }
        if (!did_something) {
            break;
        }
    }
    return distance;
}



std::vector<int> SPFA(std::vector<std::vector<Edge>> &graph, int start) {
    const int size = graph.size();
    std::vector<int> distances(size, INF);
    std::vector<bool> used(size, false);
    distances[start] = 0;
    std::queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int ver = q.front();
        q.pop();
        for (Edge edge : graph[ver]) {
            if (distances[edge.from] < INF) {
                if (distances[edge.to] > distances[edge.from] + edge.weight) {
                    distances[edge.to] = distances[edge.from] + edge.weight;
                    if (!used[edge.to]) {
                        q.push(edge.to);
                        used[edge.to] = true;
                    }
                }
            }
        }
    }
    return distances;
}



int main()
{
    std::cout << "Hello World!\n";
}

