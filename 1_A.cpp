#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>



class segment_tree {
private:
	std::vector<int> tree;
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
		neutral(0),
		initial_size(foliage.size()) {
		for (int j = 0; j < foliage.size() - 1; ++j)
		{
			tree[foliage.size() - 1 + j] = foliage[j];
		}
		for (int j = foliage.size() - 2; j >= 0; --j)
		{
			tree[j] = tree[2 * j + 1] + tree[2 * j + 2];
		}
	}


	int power(int left, int right) {
		left += initial_size - 2;
		right += initial_size - 2;
		int left_res = 0;
		int right_res = 0;
		while (left < right) {
			if (left == Right(Parent(left)))
				left_res = left_res + tree[left];
			left = Parent(left + 1);
			if (right == Left(Parent(right)))
				right_res = right_res + tree[right];
			right = Parent(right - 1);
		}
		if (left == right)
			left_res = left_res + tree[left];
		return left_res + right_res;
	}


	void update(int i, int new_value) {
		i += initial_size - 1;
		tree[i] = new_value;
		do {
			i = Parent(i);
			tree[i] = tree[Left(i)] + tree[Right(i)];
		} while (i != 0);
	}
};



int main()
{
	size_t n, q;
	int v = 1;
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
	std::vector<std::pair<int, int>> query_values(q);
	for (int i = 0; i < q; ++i)
	{
		std::cin >> query[i] >> query_values[i].first >> query_values[i].second;
	}

	for (int i = 0; i < q; ++i)
	{
		if (query[i] == 's')
			std::cout << st.power(query_values[i].first, query_values[i].second) << " ";
		if (query[i] == 'u') {
			if (query_values[i].second >= 0)
				st.update(query_values[i].first - 1, query_values[i].second);
		}
	}

	return 0;
}