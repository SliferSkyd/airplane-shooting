#ifndef BASE_OBJECT__H
#define BASE_OBJECT__H

#include "SDL_utils.h"

using namespace std;

class baseObject {
public:
    baseObject();
    ~baseObject();
    void show();
    void loadImage(const std::string& path);
    void setRect(const int& x, const int& y) {
        rect.x = x, rect.y = y;
    }
    void setAngle(const double& angle) {
        this->angle = angle;
    }
    SDL_Rect getRect() const {
        return rect;
    }
    SDL_Texture* getObject() {
        return texture;
    }
    void setSpeed(const int& speed) {
        this->speed = speed;
    }
protected:
    SDL_Rect rect;
    SDL_Texture* texture; 
    double angle;
    int speed;
};

#endif