#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using graph = std::vector<std::vector<int>>;
enum class Color {
    NoColor,
    Red,
    Blue
};

enum class Answer {
    No,
    Yes
};

struct Contest {
    graph g;
    std::vector<Color> color;
    std::vector<Answer> answers;

    void check(int start) {
        std::queue<int> neighbours;
        neighbours.push(start);
        color[start] = Color::Red;

        bool flag = false;

        while (!neighbours.empty()) {
            int n = neighbours.front();
            neighbours.pop();

            for (int i : g[n]) {
                if (color[i] == Color::NoColor) {
                    color[i] = (color[n] == Color::Red) ? Color::Blue : Color::Red;
                    neighbours.push(i);
                }
                else {
                    if (color[n] == color[i]) {
                        flag = true;
                    }
                }
            }
        }

        Answer a = flag ? Answer::No : Answer::Yes;
        answers.push_back(a);
    }

    int getUncolored() {
        for (int i = 0; i < color.size(); ++i) {
            if (color[i] == Color::NoColor) {
                return i;
            }
        }
        return -1;
    }
};

int main() {
    int students, passes;
    std::cin >> students >> passes;

    Contest c;
    c.g.resize(students);
    c.color.resize(students, Color::NoColor);

    for (int i = 0; i < passes; ++i) {
        int studentA, studentB;
        std::cin >> studentA >> studentB;
        --studentA; --studentB;
        c.g[studentA].push_back(studentB);
        c.g[studentB].push_back(studentA);
    }

    int i;
    while ((i = c.getUncolored()) != -1) {
        c.check(i);
    }

    for (int i = 0; i < c.answers.size(); ++i) {
        if (c.answers[i] == Answer::No) {
            std::cout << "NO" << std::endl;
            return 0;
        }
    }
    std::cout << "YES" << std::endl;

    return 0;
}
