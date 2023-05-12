#ifndef LASTLEVEL__H
#define LASTLEVEL__H

#include "MainObject.h"
#include "BossObject.h"
#include "ExplosionObject.h"
#include "HPObject.h"
#include "BonusObject.h"
#include "TextObject.h"
#include "TargetObject.h"

using namespace std;
class lastLevel {
    mainObject *plane;
    bossObject *boss;
    targetObject *aim;
    SDL_Texture *background;
    heartPointObject *heartPointMain;
    heartPointObject *heartPointBoss;
    bonusObject *heart;
    bonusObject *shield;
    textObject *scoreText;
    bool safe;
public:
    lastLevel();
    ~lastLevel();
    void init(int& score, int speedMain, int speedBoss);
    void gameOver(int& score);
    int run(int& score);
    void startGame(int& score);
    void endGame(int& score);
    const int MAX_LEN = 1778;
};

#endif