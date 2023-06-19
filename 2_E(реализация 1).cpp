#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <utility>



template <typename T>
using matr = std::vector<std::vector<T>>;



class Graph {
private:
	matr<int> result;

public:
	matr<int> map;
	Graph(int N, int M) : map{ N }, result{ N } {
		for (int i = 0; i < N; ++i) {
			map[i].resize(M);
			result[i].resize(M);
		}

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				int value;
				std::cin >> value;
				if (value == 1 || value == 0) {
					map[i][j] = value;
				}
				result[i][j] = -1;
			}
		}
	}


	void bfs(std::pair<int, int> start)
	{
		std::queue<std::pair<int, int>> neighbours;

		int lenght = result.size();
		int width = result[0].size();

		matr<bool> visited(lenght);
		for (int i = 0; i < lenght; ++i) {
			visited[i].resize(width, false);
		}

		int dx[] = { 1, 0, -1, 0 };
		int dy[] = { 0, 1, 0, -1 };

		neighbours.push(start);
		visited[start.first][start.second] = true;
		result[start.first][start.second] = 0;

		while (!neighbours.empty()) {
			auto n = neighbours.front();
			neighbours.pop();

			for (int i = 0; i < 4; ++i) {
				std::pair next{n.first + dx[i], n.second + dy[i]};

				if (next.first < 0 || next.first >= lenght || next.second < 0 || next.second >= width)
					continue;

				else if (visited[next.first][next.second])
					continue;

				else {
					neighbours.push(next);
					visited[next.first][next.second] = true;
					int distance = result[n.first][n.second] + 1;

					if (result[next.first][next.second] == -1) {
						result[next.first][next.second] = distance;
					}

					else if (result[next.first][next.second] > distance) {
						result[next.first][next.second] = distance;
					}
				}
			}
		}
	}


	void print() 
	{
		for (int i = 0; i < result.size(); ++i) {
			for (int j = 0; j < result[0].size(); ++j) {
				std::cout << result[i][j] << " ";
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
	matr<int> result(n);
	for (int i = 0; i < n; ++i)
	{
		result[i].resize(m, -1);
	}

	Graph district(n, m);

	std::vector <std::pair<int, int>> subways;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (district.map[i][j] == 1) {
				subways.push_back(std::pair{i, j});
			}
		}
	}

	for (int i = 0; i < subways.size(); ++i) {
		district.bfs(subways[i]);
	}
	district.print();

	return 0;
}


