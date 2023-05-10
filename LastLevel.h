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
    mainObject *plane = new mainObject();
    bossObject *boss = new bossObject();
    target *aim = new target();
    explosionObject *exp = new explosionObject();
    SDL_Texture *background;
    heartPointObject *heartPointMain = new heartPointObject();
    heartPointObject *heartPointBoss = new heartPointObject();
    bonusObject *heart = new bonusObject();
    bonusObject *shield = new bonusObject();
    textObject *scoreText = new textObject();

    int score;
public:
    void init(int lastScore, int speedMain, int speedBoss);
    void gameOver();
    int run(int &newScore, int &safeMode);
    void startGame();
    void endGame();
    const int MAX_LEN = 1778;
};

#endif