#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "target.h"
#include "Level.h"

using namespace std;

int main(int argc, char ** argv) {
    srand(time(NULL));
    initSDL();
    level test;
    test.init(0, 2, 5, 4);
    test.run();
    quitSDL();
    return 0;
}