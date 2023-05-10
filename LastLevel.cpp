#include "LastLevel.h"

void lastLevel::init(int lastScore, int speedMain, int speedBoss) {
    score = lastScore;

    heartPointMain->loadImage(5, 40, 10, "data/image/HP0.png", "data/image/HP1.png");
    heartPointBoss->loadImage(10, 870, 10, "data/image/boss_HP0.png", "data/image/boss_HP1.png");
    background = loadTexture("data/image/lastbg.png");
   
    plane->loadImage("data/image/plane.png");
    plane->loadShieldImage("data/image/shield.png");
    plane->setRect(10, Rand(10, SCREEN_HEIGHT - 100));
    plane->setSpeed(speedMain);
   
    boss->setNumFrames(32); 
    boss->loadImage("data/image/boss.png");
    boss->setClip();
    boss->setRect(SCREEN_WIDTH - boss->getRect().w / 32 - 50, Rand(10, SCREEN_HEIGHT - boss->getRect().h - 10));
    boss->setSpeed(speedBoss);
    
    aim->loadImage("data/image/target.png");  

    heart->loadImage("data/image/heart_item.png");  
    heart->setDuration(10); heart->setSpeed(300);

    shield->setDuration(15); shield->setSpeed(300);
    shield->loadImage("data/image/shield_item.png");  

    scoreText->loadFont("data/font/blacknorth.ttf", 24);
    scoreText->setColor(textObject::BLACK);
}

void lastLevel::gameOver() {
    clearScreen();
    applyTexture(background, 0, 0, SCREEN_WIDTH);
    heartPointMain->show(plane->getHeartPoint());
    heartPointBoss->show(boss->getHeartPoint());
    scoreText->setText(("Score: " + to_string(score)).c_str());
    scoreText->show(800, 10);
    show();
    playSound(5);
}

void lastLevel::startGame() {
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
        scoreText->show(800, 10);
        levelText->show(180, 200, 255 - i);
        show();
    }
}

void lastLevel::endGame() {
    for (int i = 255; i >= 0; i -= 2) {
        SDL_SetTextureAlphaMod(background, i);
        clearScreen();
        applyTexture(background, 0, 0, SCREEN_WIDTH);
        heartPointMain->show(plane->getHeartPoint());
        heartPointBoss->show(boss->getHeartPoint());
        aim->show();
        scoreText->setText(("Score: " + to_string(score)).c_str());
        scoreText->show(800, 10);
        show();
    }
}

int lastLevel::run(int& newScore) {
    static bool safeMode;
    cout << safeMode << '\n';
    auto explode = [&](baseObject* object, int numDup) {
        const int numFrames = 8;
        exp->setNumFrames(numFrames);
        exp->loadImage(("data/image/exp" + to_string(Rand(0, 2)) + ".png").c_str());
        exp->setClip();
        for (int i = 0; i < numFrames; ++i) {
            exp->setFrame(i);
            exp->burn(object, numDup);  
            show();         
        }
    };
    playSound(theme, -1);
    SDL_Event e;
    double elapsedTime = 0;
    startGame();
    while (1) {
        std::chrono::system_clock::time_point entryTime = std::chrono::system_clock::now();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(1);
            if (e.type == SDL_SCANCODE_S) safeMode ^= 1;
            plane->handleInputAction(e);
            aim->handleInputAction(e);
        }
        clearScreen();
        applyTexture(background, 0, 0, SCREEN_WIDTH);
        heartPointMain->show(plane->getHeartPoint());
        heartPointBoss->show(boss->getHeartPoint());
        plane->handleMove(elapsedTime);
        plane->showShield();
        plane->show();
        plane->makeBullet(elapsedTime);
        aim->show();
        scoreText->setText(("Score: " + to_string(score)).c_str());
        scoreText->show(800, 10);
        if (heart->getIsMove() && checkCollision(heart->getRect(), plane->getRect())) {
            playSound(pop);
            heart->setIsMove(false);
            plane->regen();
        }
        heart->handleMove(elapsedTime);
        if (heart->getIsMove()) heart->show();
        if (shield->getIsMove() && checkCollision(shield->getRect(), plane->getRect())) {
            playSound(pop);
            shield->setIsMove(false);
            plane->activeShield();
        }
        shield->handleMove(elapsedTime);
        if (shield->getIsMove()) shield->show();

        boss->scan(plane->getRect().x, plane->getRect().y);
        boss->handleMove(elapsedTime);
        boss->transit();
        boss->show();
        boss->makeBullet(elapsedTime);
        boss->regen();
        std::vector<bulletObject*> bulletList = plane->getBulletList();
        bool destroyed = false;
        for (int j = 0; j < bulletList.size(); ++j) {
            bulletObject* bullet = bulletList.at(j);
            if (checkCollision(bullet->getRect(), boss->getRect())) {
                playSound(explosion);
                explode(boss, 32);
                if (boss->shooted()) {
                    haltSound(theme);
                    playSound(siuu);
                    endGame();
                    return 1;
                }
                bulletList.erase(bulletList.begin() + j);
                destroyed = true;
                break;
            }
        }
        plane->setBulletList(bulletList);
        if (destroyed) continue;
        
        bulletList = boss->getBulletList();
        for (int j = 0; j < bulletList.size(); ++j) {
            bulletObject* bullet = bulletList.at(j);
            if (checkCollision(bullet->getRect(), plane->getRect())) {
                playSound(bomb);
                explode(plane, 1);
                if (!plane->checkShield() && plane->shooted()) {
                    haltSound(theme);
                    playSound(death);
                    endGame();
                    return 0;
                }
                bulletList.erase(bulletList.begin() + j);
            }
        }
        boss->setBulletList(bulletList);
        show();
        std::chrono::system_clock::time_point exitTime = std::chrono::system_clock::now();
        elapsedTime = (exitTime - entryTime).count() / 1e9;
        // cout << elapsedTime << '\n';
    }
}
