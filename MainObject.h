#ifndef MAIN_OBJECT__H
#define MAIN_OBJECT__H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "BaseObject.h"
#include "BulletObject.h"

using namespace std;

class mainObject: public baseObject {
public:
    mainObject();
    ~mainObject();
    void handleMove();
    void handleInputAction(SDL_Event events);
    void setBulletList(const std::vector<bulletObject*>& bulletList) {
        this->bulletList = bulletList;
    }
    std::vector<bulletObject*> getBulletList() const {
        return bulletList;
    }
    void makeAmo();
private:
    int xVal, yVal;    
    std::vector<bulletObject*> bulletList;
    std::chrono::system_clock::time_point lastBullet; 
};

#endif