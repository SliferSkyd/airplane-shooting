#ifndef THREAT_OBJECT__H
#define THREAT_OBJECT__H

#include "BaseObject.h"
#include "BulletObject.h"

using namespace std;

class threatObject: virtual public baseObject {
public:
    threatObject();
    ~threatObject();
    void handleMove(const double& elapsedTime);
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
    void makeBullet(const double& elapsedTime);
    void reborn();
    void setHasRadar(const bool& hasRadar) {
        this->hasRadar = hasRadar;
    }
    void scan(int x, int y);
protected: 
    std::vector<bulletObject*> bulletList;
    std::chrono::system_clock::time_point lastBullet; 
    double duration;
    bool hasRadar;
};

#endif