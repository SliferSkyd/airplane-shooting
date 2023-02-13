#include "MainObject.h"

mainObject::mainObject() {

}

mainObject::~mainObject() {

}

void mainObject::handleMove() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    y -= rect.h / 2;
    if (rect.y < y) rect.y += min(speed, y - rect.h);
    else rect.y -= min(speed, rect.y - y);

    rect.y = max(rect.y, 10);
    rect.y = min(rect.y, SCREEN_HEIGHT - rect.h - 100);
}
 
void mainObject::handleInputAction(SDL_Event events) {
    if (events.type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        angle = - atan2(rect.y - y, x - rect.x);
    } else if (events.type == SDL_MOUSEBUTTONDOWN) {
        std::chrono::system_clock::time_point curTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = curTime - lastBullet;
        if (elapsed_seconds.count() < 0.5) return;

        lastBullet = curTime; 
        bulletObject* bullet = new bulletObject();
        if (events.button.button == SDL_BUTTON_LEFT) {
            bullet->loadImage("data/image/laser.png");
            bullet->setType(bulletObject::LASER);
            playSound(0);
        } else {
            bullet->loadImage("data/image/sphere.png");
            bullet->setType(bulletObject::SPHERE);
            playSound(1);
        }
        bullet->setSpeed(20);
        bullet->setAngle(angle);
        bullet->setRect(rect.x + rect.w / 2 + rect.w / 2 * cos(angle), rect.y + rect.h / 2 + rect.w / 2 * sin(angle));
        bullet->setIsMove(true);
        bulletList.push_back(bullet);
    }
}

void mainObject::makeAmo() {
    for (int i = 0; i < bulletList.size(); ++i) {
        bulletObject* bullet = bulletList.at(i);
        if (bullet != NULL) {
            if (bullet->getIsMove()) {
                bullet->show();
                bullet->handleMove();
            } else {
                if (bullet != NULL) {
                    bulletList.erase(bulletList.begin() + i);
                    delete bullet; bullet = NULL;
                }
            }
        }
    }
}