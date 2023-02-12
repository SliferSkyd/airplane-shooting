#include "target.h"

target::target() {

}

target::~target() {

}

void target::handleInputAction(SDL_Event events) {
    if (events.type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        rect.x = x - rect.w / 2, rect.y = y - rect.h / 2;
    } 
}
