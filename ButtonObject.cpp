#include "ButtonObject.h"

buttonObject::buttonObject() {

}

buttonObject::~buttonObject() {

}

void buttonObject::handleMove(SDL_Rect rect) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (checkCollision(this->rect, rect)) {
        if (this->rect.w == w && this->rect.h == h) playSound(6);
        this->rect.w = w * ratio;
        this->rect.h = h * ratio;
    } else {
        this->rect.w = w;
        this->rect.h = h;
    }    
    this->rect.x = xVal - this->rect.w / 2;
    this->rect.y = yVal - this->rect.h / 2;
}

bool buttonObject::isClicked(const SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
      SDL_GetMouseState(&x, &y);
      if (checkInside(this->rect, x, y)) return true;
      else return false;
    } else return false;
}

void buttonObject::show() {
    applyTexture(texture, rect);
}