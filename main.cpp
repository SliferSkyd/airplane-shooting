#include <bits/stdc++.h>
#include "Level.h"
#include "Intro.h"

using namespace std;

int main(int argc, char ** argv) {
    srand(time(NULL));
    initSDL();
    intro menu;
    int option = menu.run();
    if (option == 1) {
        level test;
        test.init(0, 0, 2, 1, 300, 250);
        test.run();
        quitSDL();
    } else cout << "In building";
    
    return 0;
}