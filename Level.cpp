#include "Level.h"

void level::init(int idLevel, int numThreat, int speedMain, int speedThreat) {
    background = loadTexture("data/image/bg4800.png");
    plane->loadImage("data/image/plane.png");
    plane->setRect(10, Rand(10, SCREEN_HEIGHT - 100));
    plane->setSpeed(speedMain);
    int waitDistance = SCREEN_WIDTH / numThreat;
    for (int i = 0; i < numThreat; ++i) {
        threatObject* enemy = new threatObject();
        enemy->setRect(SCREEN_WIDTH - 50 + waitDistance * i, Rand(10, SCREEN_HEIGHT - 100));
        enemy->loadImage("data/image/enemy.png");
        enemy->setSpeed(speedThreat);
        enemy->setDuration(2);
        enemy->setHasRadar(Rand(0, 1));
        enemies.push_back(enemy);
    }
    expMain->loadImage("data/image/exp_main.png");
    expMain->setClip();
    expThreat->loadImage("data/image/exp_threat.png");
    expThreat->setClip();
    aim->loadImage("data/image/target.png");    
}

void level::gameOver() {
    playSound(5);
    messageBox("Ga vcl");
    quitSDL();
    exit(1);
}

void level::run() {
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
            aim->handleInputAction(e);
        }
        clrscr();
        applyTexture(background, bkg, 0, SCREEN_WIDTH);
        plane->handleMove();
        plane->show();
        plane->makeAmo();
        aim->show();
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
                    playSound(2);
                    for (int k = 0; k < 4; ++k) {
                        expThreat->setFrame(k);
                        expThreat->burn(enemy);  
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
                playSound(3);
                for (int j = 0; j < 4; ++j) {
                    expMain->setFrame(j);
                    expMain->burn(plane);
                    show();      
                }
                gameOver();
            }
            bulletList = enemy->getBulletList();
            for (int j = 0; j < bulletList.size(); ++j) {
                bulletObject* bullet = bulletList.at(j);
                if (checkCollision(bullet->getRect(), plane->getRect())) {
                    playSound(3);
                    for (int k = 0; k < 4; ++k) {
                        expMain->setFrame(k);
                        expMain->burn(plane);
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
        if (enemies.empty()) {
            playSound(4);
            messageBox("Я тебя люблю");
            break;
        }
    }
}
