// 05.11_seminar.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>


struct Edge {
    int neighbour;
    int weight;
    Edge(int _weight, int _vertex): neighbour(_vertex), weight(_weight) {}
};


std::vector<std::vector<Edge>> Prim(std::vector<std::vector<int>> graph) {
    int size = graph.size();
    std::vector<bool> used(size, false);
    std::priority_queue<Edge, std::vector<Edge>, Compare>;
    std::vector<std::vector<Edge>> answer(size);
    int res = 0;
    int count_of_ver = 0;
    heap.push({0, 0});
    int cur_top;

    while (count_of_ver < size) {
        auto top = heap.top();
        auto next = top.neighbour;
        auto weight = top.weight;
        heap.pop();
        if (!used[next]) {
            used[next] = true;
            answer[cur_top].push_back(Edge(weight, next));
            res += weight;
            ++count_of_ver;
            cur_top = next;
            for (auto ver : graph[next]) {
                if (!used[ver.neighbour]) {
                    heap.push(ver);
                }
            }
        }
    }
}

struct Compare {
    bool operator()(Edge &first, Edge &second) {
        return first.weight > second.weight;
    }
};


class DSU {
    std::vector<int> predecessors_;
    std::vector<int> rank_;
public:
    DSU(int size);
    int FindSet(int x);
    void Union(int x, int y);
};


DSU::DSU(int size) : predecessors_(size), rank_(size, 0) {
    for (int i = 0; i < size; ++i) {
        predecessors_[i] = i;
    }
}

int DSU::FindSet(int x) {
    if (predecessors_[x] == x) {
        return x;
    }
    return predecessors_[x] = FindSet(predecessors_[x]);
}


void DSU::Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);
    if (ranks_[x] < ranks_[y]) {
        predecessors_[x] = y;
    }
    else if (ranks_[x] > ranks_[y]) {
        predecessors_[y] = x;
    }
    else {
        ++ranks_[x];
        predecessors_[y] = x;
    }
}


int Kruskal(std::vector<Edge> &graph, int size) {
    std::sort(graph.begin(), graph.end(), [](Edge first, Edge second) {
        return first.weight < second.weight;
        });
    DSU dsu(size);
    int counter = 0;
    for (int i = 0; i < size; ++i) {
        int from = graph[i].from;
        int to = graph[i].to;
        int weight = graph[i].weight;
    }
}


int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector <Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        graph[from - 1].push_back(Edge(weight, to - 1));
        graph[to - 1].push_back(Edge(weight, from - 1));
    }

    std::vector<std::vector<Edge>> ans = Prim(graph);
    int res = 0;
    for (int i = 0; i <) {

    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
