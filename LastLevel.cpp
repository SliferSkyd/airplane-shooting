#include "LastLevel.h"

lastLevel::lastLevel() {
    plane = new mainObject();
    boss = new bossObject();
    aim = new targetObject();
    
    heartPointMain = new heartPointObject();
    heartPointBoss = new heartPointObject();
    heart = new bonusObject();
    shield = new bonusObject();
    scoreText = new textObject();

    safe = false;
}

lastLevel::~lastLevel() {
    clear(plane);  clear(aim); clear(heartPointMain);
    clear(heartPointBoss); clear(heart); clear(shield); 
    clear(scoreText); clear(boss);
}

void lastLevel::init(int& score, int speedMain, int speedBoss) {
    heartPointMain->loadImage(5, 40, 10, "data/image/HP0.png", "data/image/HP1.png");
    heartPointBoss->loadImage(10, 750, 10, "data/image/boss_HP0.png", "data/image/boss_HP1.png");
    background = loadTexture("data/image/lastbg.png");
   
    plane->loadImage("data/image/plane0.png");
    plane->loadShieldImage("data/image/shield.png");
    plane->setRect(10, Rand(10, SCREEN_HEIGHT - 100));
    plane->setSpeed(speedMain);
   
    boss->setNumFrames(32); 
    boss->loadImage("data/image/boss.png");
    boss->setClip();
    boss->setRect(SCREEN_WIDTH - boss->getRect().w / 32 - 50, Rand(10, SCREEN_HEIGHT - boss->getRect().h - 100));
    boss->setSpeed(speedBoss);
    boss->setHasRadar(true);
    
    aim->loadImage("data/image/target.png");  

    heart->loadImage("data/image/heart_item.png");  
    heart->setDuration(10); heart->setSpeed(300);

    shield->setDuration(15); shield->setSpeed(300);
    shield->loadImage("data/image/shield_item.png");  

    scoreText->loadFont("data/font/blacknorth.ttf", 40);
    scoreText->setColor(textObject::BROWN);
}

void lastLevel::gameOver(int& score) {
    clearScreen();
    applyTexture(background, 0, 0, SCREEN_WIDTH);
    heartPointMain->show(plane->getHeartPoint());
    heartPointBoss->show(boss->getHeartPoint());
    scoreText->setText(("Score: " + to_string(score)).c_str());
    scoreText->show(450, 10);
    show();
    playSound(5);
}

void lastLevel::startGame(int& score) {
    textObject *levelText = new textObject();
    levelText->loadFont("data/font/DripOctober.ttf", 150);
    levelText->setText("Last Level");
    levelText->setColor(textObject::RED);
    playSound(ready);
    for (int i = 0; i < 256; i += 2) {
        SDL_SetTextureAlphaMod(background, i);
        clearScreen();
        applyTexture(background, 0, 0, SCREEN_WIDTH);
        heartPointMain->show(plane->getHeartPoint());
        heartPointBoss->show(boss->getHeartPoint());
        aim->show();
        scoreText->setText(("Score: " + to_string(score)).c_str());
        scoreText->show(450, 10);
        levelText->show(50, 200, 255 - i);
        show();
    }
}

void lastLevel::endGame(int& score) {
    for (int i = 255; i >= 0; i -= 2) {
        SDL_SetTextureAlphaMod(background, i);
        clearScreen();
        applyTexture(background, 0, 0, SCREEN_WIDTH);
        heartPointMain->show(plane->getHeartPoint());
        heartPointBoss->show(boss->getHeartPoint());
        aim->show();
        scoreText->setText(("Score: " + to_string(score)).c_str());
        scoreText->show(450, 10);
        show();
    }
}

int lastLevel::run(int& score) {
    std::vector<explosionObject*> explosions;
    auto explode = [&](baseObject* object, bool isBoss) {
        explosionObject* exp = new explosionObject(); 
        const int numFrames = (isBoss ? 12 : 8);
        const int numDuplicates = (isBoss ? 32 : 1);
        exp->setNumFrames(numFrames);
        if (!isBoss) exp->loadImage(("data/image/exp" + to_string(Rand(0, 2)) + ".png").c_str());
        else exp->loadImage("data/image/special_exp.png");
        exp->setClip();
        exp->burn(object, numDuplicates);
        exp->setFrame(0);
        object->setActive(false);
        explosions.push_back(exp);
    };
    playSound(lastTheme, -1);
    SDL_Event e;
    double elapsedTime = 0;
    startGame(score);
    while (1) {
        std::chrono::system_clock::time_point entryTime = std::chrono::system_clock::now();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(1);
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) safe ^= 1, plane->setSafe(safe);
            }
            plane->handleInputAction(e);
            aim->handleInputAction(e);
        }

        clearScreen();
        applyTexture(background, 0, 0, SCREEN_WIDTH);
        heartPointMain->show(plane->getHeartPoint());
        heartPointBoss->show(boss->getHeartPoint());
        aim->show();
        scoreText->setText(("Score: " + to_string(score)).c_str());
        scoreText->show(450, 10);
        heart->handleMove(elapsedTime);
        if (heart->getIsMove()) heart->show();
        shield->handleMove(elapsedTime);
        if (shield->getIsMove()) shield->show();    
        plane->makeBullet(elapsedTime);
        if (plane->getActive()) {
            plane->handleMove(elapsedTime);
            plane->showShield();
            plane->show();
            if (heart->getIsMove() && checkCollision(heart->getRect(), plane->getRect())) {
                playSound(pop);
                heart->setIsMove(false);
                plane->regen();
            }
            if (shield->getIsMove() && checkCollision(shield->getRect(), plane->getRect())) {
                playSound(pop);
                shield->setIsMove(false);
                plane->activeShield();
            }
            std::vector<bulletObject*> bulletList = plane->getBulletList();
            for (int j = 0; j < bulletList.size(); ++j) {
                bulletObject* bullet = bulletList.at(j);
                if (checkCollision(bullet->getRect(), boss->getRect())) {
                    playSound(bossHurt);
                    explode(boss, true);
                    ++score;
                    if (boss->shooted()) {
                        playSound(bossDeath);
                        haltSound(lastTheme);
                        playSound(siuu);
                        while (explosions.size()) {
                            for (int i = 0; i < explosions.size(); ++i) {
                                explosionObject* exp = explosions.at(i);
                                if (exp->completed()) {
                                    exp->getObject()->setActive(true);
                                    explosions.erase(explosions.begin() + i);
                                    clear(exp); exp = nullptr;
                                    --i;
                                } else {
                                    exp->show();
                                    exp->nextFrame();
                                }
                            }
                        }
                        endGame(score);
                        return 1;
                    }
                    bulletList.erase(bulletList.begin() + j);
                    clear(bullet); bullet = nullptr;
                    break;
                }
            }
            plane->setBulletList(bulletList);
        }
        boss->makeBullet(elapsedTime);
        if (boss->getActive()) {
            boss->scan(plane->getRect().x, plane->getRect().y);
            boss->handleMove(elapsedTime);
            boss->transit();
            boss->show();
            boss->regen();
            std::vector<bulletObject*> bulletList = boss->getBulletList();
            for (int j = 0; j < bulletList.size(); ++j) {
                bulletObject* bullet = bulletList.at(j);
                if (checkCollision(bullet->getRect(), plane->getRect())) {
                    playSound(bomb);
                    explode(plane, false);
                    if (!safe && !plane->checkShield() && plane->shooted()) {
                        haltSound(lastTheme);
                        playSound(mainDeath);
                        while (explosions.size()) {
                            for (int i = 0; i < explosions.size(); ++i) {
                                explosionObject* exp = explosions.at(i);
                                if (exp->completed()) {
                                    exp->getObject()->setActive(true);
                                    explosions.erase(explosions.begin() + i);
                                    clear(exp); exp = nullptr;
                                    --i;
                                } else {
                                    exp->show();
                                    exp->nextFrame();
                                }
                            }
                        }
                        endGame(score);
                        return 0;
                    }
                    bulletList.erase(bulletList.begin() + j);
                    clear(bullet); bullet = nullptr;
                }
            }
            boss->setBulletList(bulletList);
        }
        
        for (int i = 0; i < explosions.size(); ++i) {
            explosionObject* exp = explosions.at(i);
            if (exp->completed()) {
                exp->getObject()->setActive(true);
                explosions.erase(explosions.begin() + i);
                clear(exp); exp = nullptr;
            } else {
                exp->show();
                exp->nextFrame();
            }
        }
        show();
        std::chrono::system_clock::time_point exitTime = std::chrono::system_clock::now();
        elapsedTime = (exitTime - entryTime).count() / 1e9;
        // cout << elapsedTime << '\n';
    }
}
