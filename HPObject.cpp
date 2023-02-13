#include "HPObject.h"

hpObject::hpObject() {

}

hpObject::~hpObject() {

}

void hpObject::loadImage(const std::string& path0, const std::string& path1) {
    for (int i = 0; i < 5; ++i) {
        baseObject* heart = new baseObject();
        heart->loadImage(path0);
        heart->setRect(40 + 40 * i, 10);
        hearts[0].push_back(heart);
    }
    for (int i = 0; i < 5; ++i) {
        baseObject* heart = new baseObject();
        heart->loadImage(path1);
        heart->setRect(40 + 40 * i, 10);
        hearts[1].push_back(heart);
    }
    HP = 5;
}

void hpObject::show() {
    for (int i = 0; i < 5; ++i) hearts[(i < HP)][i]->show();
}