#ifndef THREAT_OBJECT__H
#define THREAT_OBJECT__H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "BaseObject.h"
#include "BulletObject.h"

using namespace std;

class threatObject: public baseObject {
public:
    threatObject();
    ~threatObject();
    void handleMove();
    void initBullet();
    void setBulletList(const std::vector<bulletObject*>& bulletList) {
        this->bulletList = bulletList;
    }
    std::vector<bulletObject*> getBulletList() const {
        return bulletList;
    }
    void setDuration(const double& duration) {
        this->duration = duration;
    }
    void makeBullet();
    void reborn();
    void setHasRadar(const bool& hasRadar) {
        this->hasRadar = hasRadar;
    }
    void scan(int x, int y);
private: 
    std::vector<bulletObject*> bulletList;
    std::chrono::system_clock::time_point lastBullet; 
    double duration;
    bool hasRadar;
};

#endif