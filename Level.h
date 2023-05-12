#ifndef LEVEL__H
#define LEVEL__H

#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "HPObject.h"
#include "BonusObject.h"
#include "TextObject.h"
#include "TargetObject.h"

using namespace std;
class level {
    mainObject *plane;
    std::vector<threatObject*> enemies;
    targetObject *aim;
    SDL_Texture *background;
    heartPointObject *heartPoint;
    bonusObject *heart;
    bonusObject *shield;
    textObject *scoreText;
    int bkg, idLevel;
    bool safe;
public:
    level();
    ~level();
    void init(int& score, int idLevel, int numThreat, int numHasRadar, int speedMain, int speedThreat);
    void gameOver(int& score);
    int run(int& score);
    void startGame(int& score);
    void endGame(int& score);
    const int MAX_LEN = 4643;
};

#endif