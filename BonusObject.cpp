#include "BonusObject.h"

bonusObject::bonusObject() {
    last = std::chrono::system_clock::now();
}

bonusObject::~bonusObject() {

}

void bonusObject::handleMove() {
    if (isMove == false) {
        std::chrono::system_clock::time_point curTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = curTime - last;
        if (elapsed_seconds.count() < duration) return;
        last = curTime;
        isMove = true;
        rect.x = SCREEN_WIDTH, rect.y = Rand(10, SCREEN_HEIGHT - 100);
    }
    rect.x -= speed * cos(angle); rect.y -= speed * sin(angle);
    if (rect.x < 0) setIsMove(false);
}
