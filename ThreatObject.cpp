#include "ThreatObject.h"

threatObject::threatObject() {

}

threatObject::~threatObject() {

}

void threatObject::handleMove(const double& elapsedTime) {
    int s = speed * elapsedTime;
    rect.x -= s * cos(angle); rect.y -= s * sin(angle);
    if (rect.x < 0) rect.x = SCREEN_WIDTH, rect.y = Rand(10, SCREEN_HEIGHT - 100);
}
 
void threatObject::scan(int x, int y) { 
    if (hasRadar) angle = - atan2(y - rect.y, rect.x - x);
}

void threatObject::initBullet() {
    std::chrono::system_clock::time_point curTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = curTime - lastBullet;
    if (elapsed_seconds.count() < duration) return;
    
    lastBullet = curTime; 
    bulletObject* bullet = new bulletObject();
    bullet->loadImage("data/image/sphere2.png");
    bullet->setType(bulletObject::SPHERE);
    bullet->setSpeed(-7);
    bullet->setAngle(angle);
    bullet->setRect(rect.x + rect.w / 2 - rect.w / 2 * cos(angle), rect.y + rect.h / 2 - rect.w / 2 * sin(angle));
    bullet->setIsMove(true);
    bulletList.push_back(bullet);
}

void threatObject::makeBullet(const double& elapsedTime) {
    for (int i = 0; i < bulletList.size(); ++i) {
        bulletObject* bullet = bulletList.at(i);
        if (bullet != NULL) {
            if (bullet->getIsMove()) {
                bullet->show();
                bullet->handleMove(elapsedTime);
            } else {
                if (bullet != NULL) {
                    bulletList.erase(bulletList.begin() + i);
                    delete bullet; bullet = NULL;
                }
            }
        }
    }
}

void threatObject::reborn() {
    rect.x = SCREEN_WIDTH, rect.y = Rand(10, SCREEN_HEIGHT - 100);
}