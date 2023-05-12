#ifndef LASTLEVEL__H
#define LASTLEVEL__H

#include "MainObject.h"
#include "BossObject.h"
#include "ExplosionObject.h"
#include "HPObject.h"
#include "BonusObject.h"
#include "TextObject.h"
#include "target.h"

using namespace std;

class lastLevel {
    mainObject *plane;
    bossObject *boss;
    target *aim;
    SDL_Texture *background;
    heartPointObject *heartPointMain;
    heartPointObject *heartPointBoss;
    bonusObject *heart;
    bonusObject *shield;
    textObject *scoreText;
public:
    lastLevel();
    ~lastLevel();
    void init(int speedMain, int speedBoss);
    void gameOver();
    int run();
    void startGame();
    void endGame();
    const int MAX_LEN = 1778;
};

#endif