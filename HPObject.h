#ifndef HEARTPOINT_OBJECT__H
#define HEARTPOINT_OBJECT__H

#include "BaseObject.h"

using namespace std;
class heartPointObject: public baseObject {
public:
    heartPointObject();
    ~heartPointObject();
    void loadImage(int numLives, int x, int y, const std::string& path0, const std::string& path1);
    void show(int remainingLives);
private:
    std::vector<baseObject*> hearts[2];
};

#endif