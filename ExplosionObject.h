#ifndef EXPLOSION_OBJECT__H
#define EXPLOSION_OBJECT__H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "BaseObject.h"

using namespace std;

class explosionObject: public baseObject {
public:
    explosionObject();
    ~explosionObject();
    void setClip();
    void setFrame(const int& frame) {
        this->frame = frame;
    }
    SDL_Rect getClip(const int& i) const {
        return clip[i];
    }
    void show();
    void burn(baseObject* object);
private:
    int frame;
    SDL_Rect clip[4];
};

#endif