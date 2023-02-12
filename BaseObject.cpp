#include "BaseObject.h"

baseObject::baseObject() {
    rect.x = 0; rect.y = 0;
    angle = 0; 
    texture = NULL;
}

baseObject::~baseObject() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}
bool baseObject::loadImage(const std::string& path) {
    texture = loadTexture(path);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    return (texture != NULL);
}

void baseObject::show() {
    applyTexture(texture, rect.x, rect.y, angle);
}