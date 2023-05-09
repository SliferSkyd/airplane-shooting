#include "Level.h"

void level::init(int lastScore, int idLevel, int numThreat, int numHasRadar, int speedMain, int speedThreat) {
    this->idLevel = idLevel;
    HP->loadImage("data/image/HP0.png", "data/image/HP1.png");
    assert(numThreat >= numHasRadar);
    vector<bool> hasRadar = randomTrueFalse(numHasRadar, numThreat - numHasRadar);
    background = loadTexture(("data/image/bg" + to_string(idLevel) + ".png").c_str());
    plane->loadImage("data/image/plane.png");
    plane->loadShieldImage("data/image/shield.png");
    plane->setRect(10, Rand(10, SCREEN_HEIGHT - 100));
    plane->setSpeed(speedMain);
    int waitDistance = (numThreat ? SCREEN_WIDTH / numThreat : 0);
    for (int i = 0; i < numThreat; ++i) {
        threatObject* enemy = new threatObject();
        enemy->setRect(SCREEN_WIDTH - 50 + waitDistance * i, Rand(10, SCREEN_HEIGHT - 100));
        enemy->loadImage(("data/image/enemy" + to_string(Rand(0, 7)) + ".png").c_str());
        enemy->setSpeed(speedThreat);
        enemy->setDuration(2);
        enemy->setHasRadar(hasRadar[i]);
        enemies.push_back(enemy);
    }
    expMain->loadImage("data/image/exp_main.png");
    expMain->setClip();
    expThreat->loadImage("data/image/exp_threat.png");
    expThreat->setClip();
    aim->loadImage("data/image/target.png");  

    heart->loadImage("data/image/heart_item.png");  
    shield->loadImage("data/image/shield_item.png");  
    heart->setDuration(10); heart->setSpeed(300);
    shield->setDuration(15); shield->setSpeed(300);
    score = lastScore, bkg = 0;
    scoreText->loadFont("data/font/blacknorth.ttf", 24);
    scoreText->setColor(textObject::BLACK);
}

int level::shooted() {
    HP->subHP();
    if (HP->getHP() == 0) return 1;        
    return 0;
}

void level::gameOver() {
    clearScreen();
    applyTexture(background, bkg, 0, SCREEN_WIDTH);
    HP->show();
    scoreText->setText(("Score: " + to_string(score)).c_str());
    scoreText->show(800, 10);
    show();
    playSound(5);
}

void level::startGame() {
    textObject *levelText = new textObject();
    levelText->loadFont("data/font/DripOctober.ttf", 150);
    levelText->setText(("Level " + to_string(idLevel)).c_str());
    levelText->setColor(textObject::RED);
    playSound(ready);
    for (int i = 0; i < 256; i += 3) {
        SDL_SetTextureAlphaMod(background, i);
        clearScreen();
        applyTexture(background, bkg, 0, SCREEN_WIDTH);
        HP->show();
        aim->show();
        scoreText->setText(("Score: " + to_string(score)).c_str());
        scoreText->show(800, 10);
        levelText->show(250, 200, 255 - i);
        show();
    }
}

void level::endGame() {
    for (int i = 255; i >= 0; i -= 3) {
        SDL_SetTextureAlphaMod(background, i);
        clearScreen();
        applyTexture(background, bkg, 0, SCREEN_WIDTH);
        HP->show();
        aim->show();
        scoreText->setText(("Score: " + to_string(score)).c_str());
        scoreText->show(800, 10);
        show();
    }
}

int level::run(int& newScore) {
    playSound(theme, -1);
    SDL_Event e;
    double elapsedTime = 0;
    startGame();
    while (1) {
        std::chrono::system_clock::time_point entryTime = std::chrono::system_clock::now();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(1);
            plane->handleInputAction(e);
            aim->handleInputAction(e);
        }
        clearScreen();
        applyTexture(background, bkg, 0, SCREEN_WIDTH);
        HP->show();
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
            HP->addHP();
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
        for (int i = 0; i < enemies.size(); ++i) {
            threatObject* enemy = enemies.at(i);
            enemy->scan(plane->getRect().x, plane->getRect().y);
            enemy->initBullet();
            enemy->handleMove(elapsedTime);
            enemy->show();
            enemy->makeBullet(elapsedTime);
            std::vector<bulletObject*> bulletList = plane->getBulletList();
            bool destroyed = false;
            for (int j = 0; j < bulletList.size(); ++j) {
                bulletObject* bullet = bulletList.at(j);
                if (checkCollision(bullet->getRect(), enemy->getRect())) {
                    playSound(explosion);
                    for (int k = 0; k < 4; ++k) {
                        expThreat->setFrame(k);
                        expThreat->burn(enemy);  
                        show();         
                    }
                    ++score;
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
                playSound(bomb);
                for (int j = 0; j < 4; ++j) {
                    expMain->setFrame(j);
                    expMain->burn(plane);
                    show();      
                }
                enemy->reborn();
                if (!plane->checkShield()) {
                    if (shooted()) {
                        newScore = score;
                        haltSound(theme);
                        playSound(death);
                        endGame();
                        return 0; // lost
                    }
                } else ++score;
            }
            bulletList = enemy->getBulletList();
            for (int j = 0; j < bulletList.size(); ++j) {
                bulletObject* bullet = bulletList.at(j);
                if (checkCollision(bullet->getRect(), plane->getRect())) {
                    playSound(bomb);
                    for (int k = 0; k < 4; ++k) {
                        expMain->setFrame(k);
                        expMain->burn(plane);
                        show();       
                    }
                    bulletList.erase(bulletList.begin() + j);
                    if (!plane->checkShield()) {
                        if (shooted()) {
                            newScore = score;
                            haltSound(theme);
                            playSound(death);
                            endGame();
                            return 0; // lost
                        }
                    }
                }
            }
            enemy->setBulletList(bulletList);
            enemies[i] = enemy;
        }
        show();
        if (bkg < MAX_LEN - SCREEN_WIDTH) ++bkg;
        if (enemies.empty()) plane->setWon();
        if (plane->getRect().x > SCREEN_WIDTH) break;
        std::chrono::system_clock::time_point exitTime = std::chrono::system_clock::now();
        elapsedTime = (exitTime - entryTime).count() / 1e9;
        // cout << elapsedTime << '\n';
    }
    haltSound(theme);
    playSound(siuu);
    newScore = score;
    endGame();
    return 1; // won
}
