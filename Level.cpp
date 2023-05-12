#include "Level.h"

const int numEnemies = 9;

level::level() {
    plane = new mainObject();
    aim = new target();
    heartPoint = new heartPointObject();
    heart = new bonusObject();
    shield = new bonusObject();
    scoreText = new textObject();
}

level::~level() {
    delete plane; delete aim; delete heartPoint; 
    delete heart; delete shield; delete scoreText;
    for (int i = 0; i < enemies.size(); ++i) {
        threatObject* enemy = enemies.at(i);
        enemies.erase(enemies.begin() + i);
        delete enemy; enemy = nullptr;
    }
}

void level::init(int idLevel, int numThreat, int numHasRadar, int speedMain, int speedThreat) {
    this->idLevel = idLevel, bkg = 0;

    heartPoint->loadImage(5, 40, 10, "data/image/HP0.png", "data/image/HP1.png");
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
        enemy->loadImage(("data/image/enemy" + to_string(Rand(0, numEnemies - 1)) + ".png").c_str());
        enemy->setSpeed(speedThreat);
        enemy->setDuration(2);
        enemy->setHasRadar(hasRadar[i]);
        enemies.push_back(enemy);
    }

    aim->loadImage("data/image/target.png");  

    heart->loadImage("data/image/heart_item.png");  
    heart->setDuration(10); heart->setSpeed(300);

    shield->loadImage("data/image/shield_item.png"); 
    shield->setDuration(15); shield->setSpeed(300);

    scoreText->loadFont("data/font/blacknorth.ttf", 24);
    scoreText->setColor(textObject::BLACK);
}

void level::gameOver() {
    clearScreen();
    applyTexture(background, bkg, 0, SCREEN_WIDTH);
    heartPoint->show(plane->getHeartPoint());
    scoreText->setText(("Score: " + to_string(getScore())).c_str());
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
    for (int i = 0; i < 256; i += 2) {
        SDL_SetTextureAlphaMod(background, i);
        clearScreen();
        applyTexture(background, bkg, 0, SCREEN_WIDTH);
        heartPoint->show(plane->getHeartPoint());
        aim->show();
        scoreText->setText(("Score: " + to_string(getScore())).c_str());
        scoreText->show(800, 10);
        levelText->show(200, 200, 255 - i);
        show();
    }
}

void level::endGame() {
    for (int i = 255; i >= 0; i -= 2) {
        SDL_SetTextureAlphaMod(background, i);
        clearScreen();
        applyTexture(background, bkg, 0, SCREEN_WIDTH);
        heartPoint->show(plane->getHeartPoint());
        aim->show();
        scoreText->setText(("Score: " + to_string(getScore())).c_str());
        scoreText->show(800, 10);
        show();
    }
}

int level::run() {
    std::vector<explosionObject*> explosions;
    auto explode = [&](baseObject* object, bool nuclear) {
        explosionObject* exp = new explosionObject(); 
        const int numFrames = (nuclear ? 12 : 8);
        exp->setNumFrames(numFrames);
        if (!nuclear) exp->loadImage(("data/image/exp" + to_string(Rand(0, 2)) + ".png").c_str());
        else exp->loadImage("data/image/special_exp.png");
        exp->setClip();
        exp->burn(object, 1);
        exp->setFrame(0);
        object->setActive(false);
        explosions.push_back(exp);
    };

    playSound(theme, -1);
    SDL_Event e;
    double elapsedTime = 0;
    startGame();
    while (1) {
        std::chrono::system_clock::time_point entryTime = std::chrono::system_clock::now();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(1);
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) safeMode ^= 1, plane->setSafeMode(safeMode);
                if (e.key.keysym.sym == SDLK_BACKSPACE) goto label;
            }
            plane->handleInputAction(e);
            aim->handleInputAction(e);
        }
        clearScreen();
        applyTexture(background, bkg, 0, SCREEN_WIDTH);
        heartPoint->show(plane->getHeartPoint());
        plane->handleMove(elapsedTime);
        plane->showShield();
        plane->show();
        plane->makeBullet(elapsedTime);
        aim->show();
        scoreText->setText(("Score: " + to_string(getScore())).c_str());
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
                    explode(enemy, (bullet->getType() == bulletObject::ROCKET));
                    gainScore();
                    if (bkg < MAX_LEN - SCREEN_WIDTH) {
                        enemy->reborn();
                        enemy->loadImage(("data/image/enemy" + to_string(Rand(0, numEnemies - 1)) + ".png").c_str());
                    } else {
                        enemies.erase(enemies.begin() + i);
                        delete enemy; enemy = nullptr;
                    }
                    bulletList.erase(bulletList.begin() + j);
                    delete bullet; bullet = nullptr;
                    destroyed = true;
                    break;
                }
            }
            plane->setBulletList(bulletList);
            if (destroyed) continue;
            if (checkCollision(enemy->getRect(), plane->getRect())) {
                playSound(bomb);
                explode(plane, false);
                if (bkg < MAX_LEN - SCREEN_WIDTH) {
                    enemy->reborn();
                    enemy->loadImage(("data/image/enemy" + to_string(Rand(0, numEnemies - 1)) + ".png").c_str());
                } else {
                    enemies.erase(enemies.begin() + i);
                    delete enemy; enemy = nullptr;
                }
                if (!safeMode && !plane->checkShield() && plane->shooted()) {
                    haltSound(theme);
                    playSound(mainDeath);
                    endGame();
                    return 0; // lost
                } else gainScore();
            }
            bulletList = enemy->getBulletList();
            for (int j = 0; j < bulletList.size(); ++j) {
                bulletObject* bullet = bulletList.at(j);
                if (checkCollision(bullet->getRect(), plane->getRect())) {
                    playSound(bomb);
                    explode(plane, false);
                    bulletList.erase(bulletList.begin() + j);
                    delete bullet; bullet = nullptr;
                    if (!safeMode && !plane->checkShield() && plane->shooted()) {
                        haltSound(theme);
                        playSound(mainDeath);
                        endGame();
                        return 0; // lost
                    }
                }
            }
            enemy->setBulletList(bulletList);
            enemies[i] = enemy;
        }
        for (int i = 0; i < explosions.size(); ++i) {
            explosionObject* exp = explosions.at(i);
            if (exp->completed()) {
                explosions.erase(explosions.begin() + i);
                delete exp; exp = nullptr; 
            } else {
                exp->show();
                exp->nextFrame();
            }
        }
        show();
        if (bkg < MAX_LEN - SCREEN_WIDTH) ++bkg;
        if (enemies.empty()) plane->setWon();
        if (plane->getRect().x > SCREEN_WIDTH) break;
        std::chrono::system_clock::time_point exitTime = std::chrono::system_clock::now();
        elapsedTime = (exitTime - entryTime).count() / 1e9;
        // cout << elapsedTime << '\n';
    }
    label:;
    haltSound(theme);
    playSound(siuu);
    endGame();
    return 1; // won
}
