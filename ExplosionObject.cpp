#include "ExplosionObject.h"

explosionObject::explosionObject() {

}

explosionObject::~explosionObject() {

}

void explosionObject::setClip() {
    int len = rect.w / 4;
    for (int i = 0; i < 4; ++i) {
        clip[i].x = len * i;
        clip[i].y = 0;
        clip[i].w = len;
        clip[i].h = rect.h;
    }
}

void explosionObject::show() {
    if (frame >= 4) frame = 0;
    applyTexture(texture, clip[frame].x, clip[frame].y, rect.x, rect.y, clip[frame].w, clip[frame].h);
}

void explosionObject::burn(baseObject* object) {
    int x = object->getRect().x + object->getRect().w / 2 - clip[frame].w / 2;
    int y = object->getRect().y + object->getRect().h / 2 - clip[frame].h / 2;;
    setRect(x, y);
    show();   
}