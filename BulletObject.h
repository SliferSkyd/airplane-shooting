#ifndef BULLET_OBJECT__H
#define BULLET_OBJECT__H

#include "BaseObject.h"

using namespace std;
class bulletObject: public baseObject {
public:
    enum type {
        NONE = 0, LASER = 1, SPHERE = 2, ROCKET = 3, FIRE = 4
    };
    bulletObject();
    ~bulletObject();
    void handleMove(const double& elapsedTime);
    int getType() const {
        return type;
    }
    void setType(const int& type) {
        this->type = type;
    }
    bool getIsMove() const {
        return isMove;
    }
    void setIsMove(const bool& isMove) {
        this->isMove = isMove;
    }
    void setWidthHeight(const int& width, const int& height) {
        rect.w = width, rect.h = height;
    }
private:
    int xVal, yVal;    
    bool isMove;
    int type;
};

#endif