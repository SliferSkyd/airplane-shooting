#ifndef BUTTON_OBJECT__H
#define BUTTON_OBJECT__H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "BaseObject.h"

using namespace std;

class buttonObject: public baseObject {
public:
    buttonObject();
    ~buttonObject();
    void handleMove(SDL_Rect);
    void setPosition(const int& x, const int& y) {
        xVal = x, yVal = y;
    }
    bool isClicked(const SDL_Event& e);
    void show();
    void setSize(const int& w0, const int& h0, const int& w1, const int& h1) {
        w[0] = w0, h[0] = h0;
        w[1] = w1, h[1] = h1;
    }
private: 
    std::array<int, 2> w, h;
    int xVal, yVal;
};

#endif