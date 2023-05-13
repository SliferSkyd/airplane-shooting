#include "HeartPointObject.h"

heartPointObject::heartPointObject() {

}

heartPointObject::~heartPointObject() {
    
}

void heartPointObject::loadImage(int numLives, int x, int y, const std::string& path0, const std::string& path1) {
    const int maxLivesInRow = 5;
    for (int i = 0; i < (numLives + maxLivesInRow - 1) / maxLivesInRow; ++i) {
        for (int j = 0; i * maxLivesInRow + j < numLives && j < maxLivesInRow; ++j) {
            baseObject* heart = new baseObject();
            heart->loadImage(path0);
            heart->setRect(x + 40 * j, y + 60 * i);
            hearts[0].push_back(heart);
        }
    }
    for (int i = 0; i < (numLives + maxLivesInRow - 1) / maxLivesInRow; ++i) {
        for (int j = 0; i * maxLivesInRow + j < numLives && j < maxLivesInRow; ++j) {       
            baseObject* heart = new baseObject();
            heart->loadImage(path1);
            heart->setRect(x + 40 * j, y + 60 * i);
            hearts[1].push_back(heart);
        }
    }
}

void heartPointObject::show(int remainingLives) {
    for (int i = 0; i < hearts[0].size(); ++i) hearts[(i < remainingLives)][i]->show();
}