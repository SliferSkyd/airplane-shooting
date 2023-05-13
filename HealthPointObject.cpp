#include "healthPointObject.h"

healthPointObject::healthPointObject() {

}

healthPointObject::~healthPointObject() {
    
}

void healthPointObject::loadImage(int numLives, int x, int y, const std::string& path0, const std::string& path1) {
    const int maxLivesInRow = 5;
    for (int i = 0; i < (numLives + maxLivesInRow - 1) / maxLivesInRow; ++i) {
        for (int j = 0; i * maxLivesInRow + j < numLives && j < maxLivesInRow; ++j) {
            baseObject* health = new baseObject();
            health->loadImage(path0);
            health->setRect(x + 40 * j, y + 60 * i);
            healths[0].push_back(health);
        }
    }
    for (int i = 0; i < (numLives + maxLivesInRow - 1) / maxLivesInRow; ++i) {
        for (int j = 0; i * maxLivesInRow + j < numLives && j < maxLivesInRow; ++j) {       
            baseObject* health = new baseObject();
            health->loadImage(path1);
            health->setRect(x + 40 * j, y + 60 * i);
            healths[1].push_back(health);
        }
    }
}

void healthPointObject::show(int remainingLives) {
    for (int i = 0; i < healths[0].size(); ++i) healths[(i < remainingLives)][i]->show();
}