#ifndef BULLET_OBJECT__H
#define BULLET_OBJECT__H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "BaseObject.h"

using namespace std;

class bulletObject: public baseObject {
public:
    enum type {
        NONE = 0, LASER = 1, SPHERE = 2
    };
    bulletObject();
    ~bulletObject();
    void handleMove();
    void handleInputAction(SDL_Event events);

    int getType() const {
        return type;
    }
    void setType(const int& type) {
        this->type = type;
    }
    bool getIsMove() const {
        return isMove;
    }
    void setIsMove(const bool& isMove) {
        this->isMove = isMove;
    }
    void setWidthHeight(const int& width, const int& height) {
        rect.w = width, rect.h = height;
    }
private:
    int xVal, yVal;    
    bool isMove;
    int type;
};

#endif