#ifndef LEVEL__H
#define LEVEL__H

#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "healthPointObject.h"
#include "BonusObject.h"
#include "TextObject.h"
#include "TargetObject.h"

using namespace std;
class level {
    mainObject *plane;
    std::vector<threatObject*> enemies;
    targetObject *aim;
    SDL_Texture *background;
    healthPointObject *healthPoint;
    bonusObject *health, *shield, *nuclear;
    baseObject *nuclearIcon;
    textObject *scoreText, *nuclearText;
    int bkg, idLevel;
    bool safe;
public:
    level();
    ~level();
    void init(int& score, int idLevel, int numThreat, int numHasRadar, int speedMain, int speedThreat);
    int run(int& score, int& nuclearBombs);
    void startGame(int& score);
    void endGame(int& score);
    const int MAX_LEN = 4643;
};

#endif