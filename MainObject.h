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
    void handleMove(const double& elapsedTime);
    void handleInputAction(SDL_Event events);
    void setBulletList(const std::vector<bulletObject*>& bulletList) {
        this->bulletList = bulletList;
    }
    std::vector<bulletObject*> getBulletList() const {
        return bulletList;
    }
    void loadShieldImage(const std::string& path);
    void makeBullet(const double& elapsedTime);
    void showShield();
    void activeShield();
    bool checkShield() {
        return hasShield;
    }
    void setWon() {
        won = true;
    }
private:    
    std::vector<bulletObject*> bulletList;
    std::chrono::system_clock::time_point lastBullet, lastShield; 
    baseObject *shield = new baseObject();
    bool hasShield = false;
    bool won = false;
};

#endif