#include <bits/stdc++.h>
#include "Level.h"
#include "Intro.h"

using namespace std;

int main(int argc, char ** argv) {
    srand(time(NULL));
    initSDL();
    playSound(8, -1);
    intro menu;
    int option = menu.run();
    std::vector<std::pair<int, int>> s = {{1, 1}, {2, 1}, {3, 1}};
    haltSound(8);
    if (option == 1) {
        int score = 0;
        for (int i = 0; i < s.size(); ++i) {
            level currentLevel;
            currentLevel.init(score, i, s[i].first, s[i].second, 300, 250);
            score = currentLevel.run();
        }
    } else cout << "In building";
    quitSDL();
    return 0;
}