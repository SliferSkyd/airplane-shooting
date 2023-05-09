#ifndef BONUS_OBJECT__H
#define BONUS_OBJECT__H

#include "BaseObject.h"

using namespace std;
class bonusObject: public baseObject {
public:
    bonusObject();
    ~bonusObject();
    void handleMove(const double& elapsedTime);
    void setDuration(const double& duration) {
        this->duration = duration;
    }
    bool getIsMove() const {
        return isMove;
    }
    void setIsMove(const bool& isMove) {
        this->isMove = isMove;
        if (isMove == false) last = std::chrono::system_clock::now();
    }
private: 
    std::chrono::system_clock::time_point last; 
    double duration;
    bool isMove = false;
};

#endif