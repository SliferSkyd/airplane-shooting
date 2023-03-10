#ifndef LEVEL__H
#define LEVEL__H

#include <bits/stdc++.h>
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
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
    explosionObject *expMain = new explosionObject(), *expThreat = new explosionObject();
    SDL_Texture *background;
    hpObject *HP = new hpObject();
    bonusObject *heart = new bonusObject();
    bonusObject *shield = new bonusObject();
    textObject *scoreText = new textObject();

    int bkg, score;
public:
    void init(int lastScore, int idLevel, int numThreat, int numHasRadar, int speedMain, int speedThreat);
    void gameOver();
    int run();
    void shooted();
    void endGame();
};

#endif