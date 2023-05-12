#ifndef LEVEL__H
#define LEVEL__H

#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "HPObject.h"
#include "BonusObject.h"
#include "TextObject.h"
#include "target.h"

using namespace std;
class level {
    mainObject *plane;
    std::vector<threatObject*> enemies;
    target *aim;
    SDL_Texture *background;
    heartPointObject *heartPoint;
    bonusObject *heart;
    bonusObject *shield;
     textObject *scoreText;
    int bkg, idLevel;
public:
    level();
    ~level();
    void init(int idLevel, int numThreat, int numHasRadar, int speedMain, int speedThreat);
    void gameOver();
    int run();
    void startGame();
    void endGame();
    const int MAX_LEN = 4643;
};

#endif