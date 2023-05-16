#include "Level.h"

const int numEnemies = 10;

level::level() {
    plane = new mainObject();
    aim = new targetObject();
    healthPoint = new healthPointObject();
    health = new bonusObject();
    shield = new bonusObject();
    nuclear = new bonusObject();
    nuclearIcon = new baseObject();
    scoreText = new textObject();
    nuclearText = new textObject();
    safe = false;
}

level::~level() {
    clear(plane); clear(aim); clear(healthPoint); 
    clear(health); clear(shield); clear(scoreText);
    clear(nuclear); clear(nuclearIcon); clear(nuclearText);
    for (int i = 0; enemies.size(); ) {
        threatObject* enemy = enemies.at(i);
        enemies.erase(enemies.begin());
        clear(enemy); enemy = nullptr;
    }
}

void level::init(int& score, int idLevel, int numThreat, int numHasRadar, int speedMain, int speedThreat) {
    this->idLevel = idLevel, bkg = 0;

    healthPoint->loadImage(5, 40, 10, "data/image/HP0.png", "data/image/HP1.png");
    vector<bool> hasRadar = randomTrueFalse(numHasRadar, numThreat - numHasRadar);
    background = loadTexture(("data/image/bg" + to_string(idLevel) + ".png").c_str());
   
    plane->loadImage("data/image/plane0.png");
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

    health->loadImage("data/image/health_item.png");  
    health->setDuration(10); health->setSpeed(300);

    shield->loadImage("data/image/shield_item.png"); 
    shield->setDuration(15); shield->setSpeed(300);

    nuclear->loadImage("data/image/nuclear_item.png");
    nuclear->setDuration(17); nuclear->setSpeed(300);

    nuclearIcon->loadImage("data/image/nuclear.png");
    nuclearIcon->setRect(40, 60);

    scoreText->loadFont("data/font/blacknorth.ttf", 40);
    scoreText->setColor(textObject::BROWN);
    scoreText->setPosition(450, 10);

    nuclearText->loadFont("data/font/blacknorth.ttf", 30);
    nuclearText->setColor(textObject::ORANGE);    
    nuclearText->setPosition(80, 70);
}

void level::startGame(int& score) {
    textObject *levelText = new textObject();
    levelText->loadFont("data/font/DripOctober.ttf", 150);
    levelText->setText(("Level " + to_string(idLevel)).c_str());
    levelText->setColor(textObject::RED);
    levelText->setPosition(200, 200);
    playSound(ready);
    for (int i = 0; i < 256; i += 2) {
        SDL_SetTextureAlphaMod(background, i);
        clearScreen();
        applyTexture(background, bkg, 0, SCREEN_WIDTH);
        healthPoint->show(plane->gethealthPoint());
        nuclearIcon->show();
        aim->show();
        scoreText->setText(("Score: " + to_string(score)).c_str());
        scoreText->show();
        nuclearText->setText(to_string(plane->getNuclear()));
        nuclearText->show();
        levelText->show(255 - i);
        show();
    }
}

void level::endGame(int& score) {
    for (int i = 255; i >= 0; i -= 2) {
        SDL_SetTextureAlphaMod(background, i);
        clearScreen();
        applyTexture(background, bkg, 0, SCREEN_WIDTH);
        healthPoint->show(plane->gethealthPoint());
        nuclearIcon->show();
        aim->show();
        scoreText->setText(("Score: " + to_string(score)).c_str());
        scoreText->show();
        nuclearText->setText(to_string(plane->getNuclear()));
        nuclearText->show();
        show();
    }
}

int level::run(int& score, int& nuclearBombs) {
    plane->setNuclear(nuclearBombs);
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
    startGame(score);
    while (1) {
        std::chrono::system_clock::time_point entryTime = std::chrono::system_clock::now();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(1);
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) safe ^= 1, plane->setSafe(safe);
                if (e.key.keysym.sym == SDLK_BACKSPACE) goto label;
            }
            plane->handleInputAction(e);
            aim->handleInputAction(e);
        }
        clearScreen();
        applyTexture(background, bkg, 0, SCREEN_WIDTH);
        
        healthPoint->show(plane->gethealthPoint());
        aim->show();
        scoreText->setText(("Score: " + to_string(score)).c_str());
        scoreText->show();
        nuclearText->setText(to_string(plane->getNuclear()));
        nuclearText->show();    
        nuclearIcon->show();

        if (health->getIsMove() && checkCollision(health->getRect(), plane->getRect())) {
            playSound(pop);
            health->setIsMove(false);
            plane->heal();
        }
        health->handleMove(elapsedTime);
        if (health->getIsMove()) health->show();

        if (shield->getIsMove() && checkCollision(shield->getRect(), plane->getRect())) {
            playSound(pop);
            shield->setIsMove(false);
            plane->activeShield();
        }
        shield->handleMove(elapsedTime);
        if (shield->getIsMove()) shield->show();

        if (nuclear->getIsMove() && checkCollision(nuclear->getRect(), plane->getRect())) {
            playSound(pop);
            nuclear->setIsMove(false);
            plane->gainNuclear();
        }
        nuclear->handleMove(elapsedTime);
        if (nuclear->getIsMove()) nuclear->show();

        plane->handleMove(elapsedTime);
        plane->showShield();
        plane->show();
        plane->makeBullet(elapsedTime);
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
                    ++score;
                    if (bkg < MAX_LEN - SCREEN_WIDTH) {
                        enemy->reborn();
                        enemy->loadImage(("data/image/enemy" + to_string(Rand(0, numEnemies - 1)) + ".png").c_str());
                    } else {
                        enemies.erase(enemies.begin() + i);
                        clear(enemy); enemy = nullptr;
                    }
                    bulletList.erase(bulletList.begin() + j);
                    clear(bullet); bullet = nullptr;
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
                    clear(enemy); enemy = nullptr;
                }
                ++score;
                if (!safe && !plane->checkShield() && plane->shot()) {
                    haltSound(theme);
                    playSound(mainDeath);
                    endGame(score);
                    nuclearBombs = plane->getNuclear();
                    return 0; // lost
                }
            }
            if (enemy == nullptr) continue; // destructed
            bulletList = enemy->getBulletList();
            for (int j = 0; j < bulletList.size(); ++j) {
                bulletObject* bullet = bulletList.at(j);
                if (checkCollision(bullet->getRect(), plane->getRect())) {
                    playSound(bomb);
                    explode(plane, false);
                    bulletList.erase(bulletList.begin() + j);
                    clear(bullet); bullet = nullptr;
                    if (!safe && !plane->checkShield() && plane->shot()) {
                        haltSound(theme);
                        playSound(mainDeath);
                        endGame(score);
                        nuclearBombs = plane->getNuclear();
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
                clear(exp); exp = nullptr; 
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
    endGame(score);
    nuclearBombs = plane->getNuclear();
    return 1; // won
}
