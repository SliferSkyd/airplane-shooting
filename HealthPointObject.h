#ifndef HEALTHPOINT_OBJECT__H
#define HEALTHPOINT_OBJECT__H

#include "BaseObject.h"

using namespace std;
class healthPointObject: public baseObject {
public:
    healthPointObject();
    ~healthPointObject();
    void loadImage(int numLives, int x, int y, const std::string& path0, const std::string& path1);
    void show(int remainingLives);
private:
    std::vector<baseObject*> healths[2];
};

#endif