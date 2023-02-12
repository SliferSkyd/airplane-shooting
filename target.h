#ifndef TARGET__H
#define TARGET__H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "BaseObject.h"

using namespace std;

class target: public baseObject {
public:
    target();
    ~target();
    void handleInputAction(SDL_Event events);
};

#endif