#include "MainObject.h"

mainObject::mainObject() {
    shield = new baseObject();
    hasShield = false;
    won = false; safe = false;
    heartPoint = 5; currentType = 0; nuclear = 0;
}

mainObject::~mainObject() {
    while (bulletList.size()) {
        bulletObject* bullet = bulletList.at(0);
        clear(bullet); bullet = nullptr;
        bulletList.erase(bulletList.begin());
    }
}

void mainObject::handleMove(const double& elapsedTime) {
    int s = speed * elapsedTime;
    if (won) {
        rect.x += s;
        return;
    }
    int x, y;
    SDL_GetMouseState(&x, &y);
    y -= rect.h / 2;
    if (rect.y < y) rect.y += min(s, y - rect.h);
    else rect.y -= min(s, rect.y - y);

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
            playSound(laser);
            bullet->setSpeed(20);
            bullet->setAngle(angle);
            bullet->setRect(rect.x + rect.w / 2 + rect.w / 2 * cos(angle), rect.y + rect.h / 2 + rect.w / 2 * sin(angle));
            bullet->setIsMove(true);
            bulletList.push_back(bullet);
        } else if (events.button.button == SDL_BUTTON_RIGHT) {
            bullet->loadImage("data/image/sphere.png");
            bullet->setType(bulletObject::SPHERE);
            playSound(sphere);
            bullet->setSpeed(20);
            bullet->setAngle(angle);
            bullet->setRect(rect.x + rect.w / 2 + rect.w / 2 * cos(angle), rect.y + rect.h / 2 + rect.w / 2 * sin(angle));
            bullet->setIsMove(true);
            bulletList.push_back(bullet);
        } else {
            if (!safe && !nuclear) return;
            const double GAP = 0.1;
            for (int i = -2; i <= 2; ++i) {
                bulletObject* bullet = new bulletObject();
                bullet->loadImage("data/image/rocket.png");
                bullet->setType(bulletObject::ROCKET);
                bullet->setSpeed(20);
                bullet->setAngle(angle + GAP * i);
                bullet->setRect(rect.x + rect.w / 2 + rect.w / 2 * cos(angle), rect.y + rect.h / 2 + rect.w / 2 * sin(angle));
                bullet->setIsMove(true);
                bulletList.push_back(bullet);
            }
            if (!safe) --nuclear;
        }
    }
}

void mainObject::makeBullet(const double& elapsedTime) {
    for (int i = 0; i < bulletList.size(); ++i) {
        bulletObject* bullet = bulletList.at(i);
        if (bullet != NULL) {
            if (bullet->getIsMove()) {
                bullet->show();
                bullet->handleMove(elapsedTime);
            } else {
                if (bullet != NULL) {
                    bulletList.erase(bulletList.begin() + i);
                    clear(bullet); bullet = NULL;
                }
            }
        }
    }
}

void mainObject::loadShieldImage(const std::string& path) {
    shield->loadImage(path);
}

void mainObject::showShield() {
    if (!hasShield && !safe) return;
    int x = rect.x + rect.w / 2 - shield->getRect().w / 2;
    int y = rect.y + rect.h / 2 - shield->getRect().h / 2;
    shield->setRect(x, y);
    shield->show();
    std::chrono::system_clock::time_point curTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = curTime - lastShield;
    if (elapsed_seconds.count() > 5) {
        hasShield = 0;
        return;
    }
}

void mainObject::activeShield() {
    hasShield = true;
    lastShield = std::chrono::system_clock::now();
}

int mainObject::shooted() {
    --heartPoint;
    return (heartPoint <= 0);
}

void mainObject::regen() {
    ++heartPoint;
    if (heartPoint > 5) heartPoint = 5;
}