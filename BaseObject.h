#ifndef BASE_OBJECT__H
#define BASE_OBJECT__H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_utils.h"

using namespace std;

class baseObject {
public:
    baseObject();
    ~baseObject();
    void show();
    bool loadImage(const std::string& path);
    void setRect(const int& x, const int& y) {
        rect.x = x, rect.y = y;
    }
    void setAngle(const double& angle) {
        this->angle = angle;
    }
    SDL_Rect getRect() const {
        return rect;
    }
    SDL_Texture* getObject() {
        return texture;
    }
    void setSpeed(const double& speed) {
        this->speed = speed;
    }
protected:
    SDL_Rect rect;
    SDL_Texture* texture; 
    double angle, speed;
};

#endif