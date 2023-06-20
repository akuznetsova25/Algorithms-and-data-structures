#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>



template <typename T>
using matr = std::vector<std::vector<T>>;



class Chess {
private:
    int size;

public:
    Chess(int n) : size(n) {}
    struct Checkerboard {
        int x;
        int y;
        int dist;

        Checkerboard(int x, int y, int dist = 0) : x(x), y(y), dist(dist) {}
    };

    int bfs(Checkerboard start, Checkerboard finish) {

        std::queue<Checkerboard> neighbours;
        int dx[] = {-2, -2, -1, 1, 2, 2, 1, -1};
        int dy[] = {-1, 1, 2, 2, 1, -1, -2, -2};

        std::set<Checkerboard> visited;
        
        neighbours.push(start);
        while (!neighbours.empty()) {
            Checkerboard n = neighbours.front();
            neighbours.pop();

            int x = n.x;
            int y = n.y;
            int dist = n.dist;
            if (x == finish.x && y == finish.y) {
                return dist;
            }

            else if (!visited.count(n)) {
                visited.insert(n);
                for (int i = 0; i < 8; ++i) {
                    int x_1 = x + dx[i];
                    int y_1 = y + dy[i];

                    if (valid(x_1, y_1)) {
                        neighbours.push({ x_1, y_1, dist + 1 });
                    }
                }
            }
        }
    }

    bool valid(int x, int y) {
        if (x < 0 || y < 0 || x >= size || y >= size)
            return false;

        return true;
    }
};



int main()
{
    int n;
    std::cin >> n;
    Chess knight(n);
    
    return 0;
}

