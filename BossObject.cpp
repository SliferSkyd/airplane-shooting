#include "BossObject.h"

bossObject::bossObject() {

}

bossObject::~bossObject() {

}

void bossObject::handleMove(const double& elapsedTime) {
    rect.x = SCREEN_WIDTH - rect.w / numFrames - 50;
    int s = speed * elapsedTime;
    rect.y -= s * sin(angle);
}

void bossObject::initBullet() {
    const double GAP = 0.1;

    for (int i = -2; i <= 2; ++i) {
        bulletObject* bullet = new bulletObject();
        bullet->loadImage("data/image/boss_bullet.png");
        bullet->setSpeed(-15);
        bullet->setAngle(angle + GAP * i);
        bullet->setRect(rect.x - rect.w / numFrames / 2 * cos(angle), rect.y + rect.h * 3 / 4 - rect.w / numFrames / 2 * sin(angle));
        bullet->setIsMove(true);
        bulletList.push_back(bullet);
    }
}

void bossObject::transit() {
    std::chrono::system_clock::time_point curTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = curTime - lastTransition;
    if (elapsed_seconds.count() < durationBurn) return;
    lastTransition = curTime;
    ++frame; if (frame >= clip.size()) frame = 0;
    if (frame == 20) initBullet();
}

int bossObject::shooted() {
    --heartPoint;
    return (heartPoint == 0);
}

void bossObject::regen() {
    std::chrono::system_clock::time_point curTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = curTime - lastRegen;
    if (elapsed_seconds.count() < durationRegen) return;
    lastRegen = curTime;
    ++heartPoint;
    if (heartPoint > 10) heartPoint = 10;
}