#ifndef BOSS_OBJECT__H
#define BOSS_OBJECT__H

#include "BaseObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"

using namespace std;

class bossObject: public threatObject, public explosionObject {
public:
    bossObject();
    ~bossObject();
    void handleMove(const double& elapsedTime);
    void transit();
    void initBullet();
    int shooted();
    void regen();
    int getHeartPoint() {
        return heartPoint;
    }
private:
    const double durationBurn = 0.0625;
    const double durationRegen = 7;
    std::chrono::system_clock::time_point lastTransition, lastRegen;
    const int hasRadar = 1;
    int heartPoint = 10;
};

#endif