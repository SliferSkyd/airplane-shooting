#ifndef BUTTON_OBJECT__H
#define BUTTON_OBJECT__H

#include "BaseObject.h"

using namespace std;

class buttonObject: public baseObject {
public:
    buttonObject();
    ~buttonObject();
    void handleMove(SDL_Rect);
    void setPosition(const int& x, const int& y) {
        xVal = x, yVal = y;
    }
    bool isClicked(const SDL_Event& e);
    void show();
    void setSize() {
        w = rect.w, h = rect.h;
    }
private: 
    int w, h;
    int xVal, yVal;
    const double ratio = 1.2;
};

#endif