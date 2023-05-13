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
    void heal();
    int gethealthPoint() {
        return healthPoint;
    }
private:
    const double durationBurn = 0.03125;
    const double durationHeal = 7;
    std::chrono::system_clock::time_point lastTransition, lastHeal;
    int healthPoint = 10;
};

#endif