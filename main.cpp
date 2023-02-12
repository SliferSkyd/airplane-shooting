#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "target.h"

using namespace std;

const int NUM_THREATS = 2;
const int WAIT_TIME = 200;

void gameOver() {
    messageBox("Ga vcl");
    quitSDL();
    exit(1);
}

int main(int argc, char ** argv) {
    srand(time(NULL));
    initSDL();
    SDL_Texture* background = loadTexture("data/image/bg4800.png");

    mainObject* plane = new mainObject();
    plane->loadImage("data/image/plane.png");
    plane->setRect(10, Rand(10, SCREEN_HEIGHT - 100));
    std::vector<threatObject*> enemies;
    
    for (int i = 0; i < NUM_THREATS; ++i) {
        threatObject* enemy = new threatObject();
        enemy->setRect(SCREEN_WIDTH - 50 + WAIT_TIME * i, Rand(10, SCREEN_HEIGHT - 100));
        enemy->loadImage("data/image/enemy.png");
        enemy->setSpeed(4);
        enemy->setDuration(2);
        enemy->setHasRadar(Rand(0, 1));
        enemies.push_back(enemy);
    }
    target aim;
    aim.loadImage("data/image/target.png");
    explosionObject* expMain = new explosionObject();
    expMain->loadImage("data/image/exp_main.png");
    expMain->setClip();
    SDL_Event e;
    bool quit = false;
    int bkg = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
            plane->handleInputAction(e);
            aim.handleInputAction(e);
        }
        clrscr();
        applyTexture(background, bkg, 0, SCREEN_WIDTH);
        plane->handleMove();
        plane->show();
        plane->makeAmo();
        aim.show();
        for (int i = 0; i < enemies.size(); ++i) {
            threatObject* enemy = enemies.at(i);
            enemy->scan(plane->getRect().x, plane->getRect().y);
            enemy->initBullet();
            enemy->handleMove();
            enemy->show();
            enemy->makeBullet();
            std::vector<bulletObject*> bulletList = plane->getBulletList();
            bool destroyed = false;
            for (int j = 0; j < bulletList.size(); ++j) {
                bulletObject* bullet = bulletList.at(j);
                if (checkCollision(bullet->getRect(), enemy->getRect())) {
                    playExplosionSound(0);
                    for (int k = 0; k < 4; ++k) {
                        int x = enemy->getRect().x + enemy->getRect().w / 2 - expMain->getClip(k).w / 2;
                        int y = enemy->getRect().y + enemy->getRect().h / 2 - expMain->getClip(k).h / 2;
                        expMain->setFrame(k);
                        expMain->setRect(x, y);
                        expMain->show();       
                        show();         
                    }
                    if (bkg < MAX_LEN - SCREEN_WIDTH) enemy->reborn();
                    else enemies.erase(enemies.begin() + i);
                    bulletList.erase(bulletList.begin() + j);
                    destroyed = true;
                    break;
                }
            }
            plane->setBulletList(bulletList);
            if (destroyed) continue;
            if (checkCollision(enemy->getRect(), plane->getRect())) {
                playExplosionSound(1);
                for (int j = 0; j < 4; ++j) {
                    int x = plane->getRect().x + plane->getRect().w / 2 - expMain->getClip(j).w / 2;
                    int y = plane->getRect().y + plane->getRect().h / 2 - expMain->getClip(j).h / 2;
                    expMain->setFrame(j);
                    expMain->setRect(x, y);
                    expMain->show();   
                    show();      
                }
                gameOver();
            }
            bulletList = enemy->getBulletList();
            for (int j = 0; j < bulletList.size(); ++j) {
                bulletObject* bullet = bulletList.at(j);
                if (checkCollision(bullet->getRect(), plane->getRect())) {
                    playExplosionSound(1);
                    for (int k = 0; k < 4; ++k) {
                        int x = plane->getRect().x + plane->getRect().w / 2 - expMain->getClip(k).w / 2;
                        int y = plane->getRect().y + plane->getRect().h / 2 - expMain->getClip(k).h / 2;
                        expMain->setFrame(k);
                        expMain->setRect(x, y);
                        expMain->show();   
                        show();      
                    }
                    bulletList.erase(bulletList.begin() + j);
                    gameOver();
                }
            }
            enemy->setBulletList(bulletList);
            enemies[i] = enemy;
        }
        show();
        if (bkg < MAX_LEN - SCREEN_WIDTH) ++bkg;
    }
    quitSDL();
    return 0;
}