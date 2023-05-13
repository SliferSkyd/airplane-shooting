#ifndef LASTLEVEL__H
#define LASTLEVEL__H

#include "MainObject.h"
#include "BossObject.h"
#include "ExplosionObject.h"
#include "healthPointObject.h"
#include "BonusObject.h"
#include "TextObject.h"
#include "TargetObject.h"

using namespace std;
class lastLevel {
    mainObject *plane;
    bossObject *boss;
    targetObject *aim;
    SDL_Texture *background;
    healthPointObject *healthPointMain;
    healthPointObject *healthPointBoss;
    bonusObject *health, *shield, *nuclear;
    baseObject *nuclearIcon;
    textObject *scoreText, *nuclearText;
    bool safe;
public:
    lastLevel();
    ~lastLevel();
    void init(int& score, int speedMain, int speedBoss);
    int run(int& score, int& nuclearBombs);
    void startGame(int& score);
    void endGame(int& score);
    const int MAX_LEN = 1778;
};

#endif