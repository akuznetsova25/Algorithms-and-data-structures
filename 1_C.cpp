#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>



class segment_tree {
private:
	std::vector<int> tree;
	std::vector<int> promise;
	int neutral;
	int initial_size;

	int Left(int index) {
		return 2 * index + 1;
	}

	int Right(int index) {
		return 2 * index + 2;
	}

	int Parent(int index) {
		return (index - 1) / 2;
	}



public:
	segment_tree(std::vector<int>& foliage) :
		tree(2 * foliage.size() - 1),
		promise(2 * foliage.size() - 1),
		neutral(0),
		initial_size(foliage.size()) {
		for (int j = 0; j < foliage.size() - 1; ++j)
		{
			tree[foliage.size() - 1 + j] = foliage[j];
		}
		for (int j = foliage.size() - 2; j >= 0; --j)
		{
			tree[j] = std::min(tree[2 * j + 1], tree[2 * j + 2]);
		}
	}

	void push(int node)
	{
		promise[Left(node)] += promise[node];
		promise[Right(node)] += promise[node];
		tree[node] += promise[node];
		promise[node] = 0;
	}

	void update(int node, int a, int b, int left, int right, int delta)
	{
		if (b < left || right < a)
			return;
		if (left <= a && right >= b) {
			promise[node] += delta;
			return;
		}
		push(node);
		int m = (a + b) / 2;
		update(Left(node), a, m, left, right, delta);
		update(Right(node), m + 1, b, left, right, delta);
		tree[node] = std::min(tree[Left(node)] + promise[Left(node)], tree[Right(node)] + promise[Right(node)]);
	}


	int get(int v, int tl, int tr, int pos) {
		if (tl == tr)
			return tree[v];
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			return promise[v * 2 + 1] + get(v * 2 + 1, tl, tm, pos);
		else
			return promise[v * 2 + 2] + get(v * 2 + 2, tm + 1, tr, pos);
	}
};



int main()
{
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);

	size_t n, q;
	int pow = 0;
	int size_arr = std::pow(2, pow);
	int neutral = 0;

	std::cin >> n;
	while (size_arr < n)
	{
		size_arr = std::pow(2, ++pow);
	}

	std::vector<int> arr(size_arr);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> arr[i];
	}

	for (int i = n; i < size_arr; ++i)
	{
		arr[i] = neutral;
	}


	segment_tree st{ arr };

	std::cin >> q;
	std::vector<char> query(q);
	std::vector query_values(q, std::vector<int>(3));

	for (int i = 0; i < q; ++i)
	{
		std::cin >> query[i];
		if (query[i] == 'a')
		{
			std::cin >> query_values[i][0] >> query_values[i][1] >> query_values[i][2];
		}
		else
		{
			std::cin >> query_values[i][0];
		}
	}

	for (int i = 0; i < q; ++i)
	{
		if (query[i] == 'g')
			std::cout << st.get(0, 0, size_arr - 1, query_values[i][0] - 1) << std::endl;
		if (query[i] == 'a') {
			st.update(0, 0, size_arr - 1, query_values[i][0] - 1, query_values[i][1] - 1, query_values[i][2]);
		}
	}

	return 0;
}
