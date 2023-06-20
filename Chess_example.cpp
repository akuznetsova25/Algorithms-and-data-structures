#include <iostream>
#include <set>
#include <queue>
#include <climits>
using namespace std;

static const int N = INT_MAX / 2;

// все 8 возможных движений
// для шахматного коня
int row[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int col[] = { -1, 1, 1, -1, 2, -2, 2, -2 };

// Проверяем, верны ли (x, y) координаты шахматной доски
bool valid(int x, int y)
{
    if (x < 0 || y < 0 || x >= N || y >= N)
        return false;

    return true;
}

// алгоритм BFS
struct Node
{
    // (x, y) координаты шахматной доски
    // dist - минимальное расстояние из предварительной точки к финальной
    int x, y, dist;

    // Node конструктор
    Node(int x, int y, int dist = 0) : x(x), y(y), dist(dist) {}


    // оператор перегрузки < operator
    bool operator<(const Node& o) const
    {
        return x < o.x || (x == o.x && y < o.y);
    }
};

// Находим минимальное количество шагов, предпринятых конем
// из предварительной точки к финальной, используем BFS
int BFS(Node src, Node dest)
{
    // проверяем была ли посещена ячейка матрицы или нет
    set<Node> visited;

    // создаем очередь и ставим в очередь первый узел
    queue<Node> q;
    q.push(src);

    // запустить до тех пор, пока очередь не станет пустой
    while (!q.empty())
    {
        // извлекаем передний узел из очереди и обрабатываем его
        Node node = q.front();
        q.pop();

        int x = node.x;
        int y = node.y;
        int dist = node.dist;

        // если пункт назначения достигнут, вернуть dist
        if (x == dest.x && y == dest.y)
            return dist;

        // пропускаем, если местоположение посещалось раньше
        if (!visited.count(node))
        {
            // пометим текущий узел как посещенный
            visited.insert(node);

            // проверяем все 8 возможных движений коня
            // и ставим каждое правильное движение в очередь
            for (int i = 0; i < 8; ++i)
            {
                // Получить новую действительную позицию коня из текущей
                // позиция на шахматной доске и поставить ее в очередь,
                // очередь с расстоянием +1
                int x1 = x + row[i];
                int y1 = y + col[i];

                if (valid(x1, y1))
                    q.push({ x1, y1, dist + 1 });
            }
        }
    }

    // вернуть бесконечность, если путь не возможен
    return INT_MAX;
}


int main()
{
    // исходные координаты
    Node src = { 1, 1 };

    // координаты пункта назначения
    Node dest = { 4, 6 };

    cout << "Минимальное количество шагов :" << BFS(src, dest);

    return 0;
}