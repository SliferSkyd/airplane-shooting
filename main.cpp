#include <bits/stdc++.h>
#include "Level.h"

using namespace std;

int main(int argc, char ** argv) {
    srand(time(NULL));
    initSDL();
    level test;
    test.init(0, 0, 2, 1, 300, 250);
    test.run();
    quitSDL();
    return 0;
}