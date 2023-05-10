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
    mainObject *plane = new mainObject();
    std::vector<threatObject*> enemies;
    target *aim = new target();
    explosionObject *exp = new explosionObject();
    SDL_Texture *background;
    heartPointObject *heartPoint = new heartPointObject();
    bonusObject *heart = new bonusObject();
    bonusObject *shield = new bonusObject();
    textObject *scoreText = new textObject();

    int bkg, score, idLevel;
public:
    void init(int lastScore, int idLevel, int numThreat, int numHasRadar, int speedMain, int speedThreat);
    void gameOver();
    int run(int &curScore, int &safeMode);
    void startGame();
    void endGame();
    const int MAX_LEN = 4643;
};

#endif