#include "BulletObject.h"

bulletObject::bulletObject() {
    rect.x = 0, rect.y = 0;
    xVal = 0, yVal = 0;
    isMove = false; type = NONE;
}

bulletObject::~bulletObject() {

}

void bulletObject::handleMove(const double& elapsedTime) {
    int s = speed * elapsedTime;
    rect.x += speed * cos(angle);
    rect.y += speed * sin(angle);
    if (rect.x > SCREEN_WIDTH || rect.x < 0 || rect.y > SCREEN_HEIGHT || rect.y < 0) isMove = false;
}
 
void bulletObject::handleInputAction(SDL_Event events) {

}