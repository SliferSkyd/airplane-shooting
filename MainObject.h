#ifndef MAIN_OBJECT__H
#define MAIN_OBJECT__H

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
    int shot();
    void heal();
    int getHealthPoint() {
        return healthPoint;
    }
    void setSafe(const bool& safe) {
        this->safe = safe;
    }
    void nextType() {
        currentType = (currentType + 1) % numTypes;
        loadImage(("data/image/plane" + to_string(currentType) + ".png").c_str());
    }
    void gainNuclear() {
        ++nuclear;
    }
    int getNuclear() {
        return nuclear;
    }
    void setNuclear(int nuclear) {
        this->nuclear = nuclear;
    }
private:    
    std::vector<bulletObject*> bulletList;
    std::chrono::system_clock::time_point lastBullet, lastShield; 
    baseObject *shield;
    bool hasShield, won, safe;
    int healthPoint, nuclear;
    int currentType;
    const int numTypes = 2;
};

#endif