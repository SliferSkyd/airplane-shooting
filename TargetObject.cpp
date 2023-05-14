#include "TargetObject.h"

targetObject::targetObject() {

}

targetObject::~targetObject() {

}

void targetObject::handleInputAction(SDL_Event events) {
    if (events.type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        rect.x = x - rect.w / 2, rect.y = y - rect.h / 2;
    } 
}
