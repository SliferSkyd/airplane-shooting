#ifndef TEXT_OBJECT__H
#define TEXT_OBJECT__H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "BaseObject.h"

using namespace std;

class textObject: public baseObject {
public:
    enum textColor {
        BLACK = 0, RED = 1, BLUE = 2, GREEN = 3, WHITE = 4
    };
    textObject();
    ~textObject();

    void setText(const std::string& text) {
        this->text = text;
    }
    void setColor(const int& type);
    void show(const int& x, const int& y);
    void loadFont(const std::string& path, const int& size);
private: 
    std::string text;
    SDL_Color color;
    TTF_Font* font = NULL;
};

#endif