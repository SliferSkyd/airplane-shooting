#include "BonusObject.h"

bonusObject::bonusObject() {
    last = std::chrono::system_clock::now();
}

bonusObject::~bonusObject() {

}

void bonusObject::handleMove(const double& elapsedTime) {
    if (isMove == false) {
        std::chrono::system_clock::time_point curTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = curTime - last;
        if (elapsed_seconds.count() < duration) return;
        last = curTime;
        isMove = true;
        rect.x = SCREEN_WIDTH, rect.y = Rand(10, SCREEN_HEIGHT - 100);
    }
    int s = speed * elapsedTime;
    rect.x -= s * cos(angle); rect.y -= s * sin(angle);
    if (rect.x < 0) setIsMove(false);
}
