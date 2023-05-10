#include "TextObject.h"

textObject::textObject() {

}

textObject::~textObject() {

}

void textObject::setColor(const int& type) {
    if (type == RED) color = {255, 0, 0};
    else if (type == BLACK) color = {0, 0, 0};
    else if (type == GREEN) color = {0, 255, 255};
    else if (type == WHITE) color = {255, 255, 255};
    else if (type == BLUE) color = {0, 0, 255};
    else if (type == BROWN) color = {92, 38, 3};
}

void textObject::loadFont(const std::string& path, const int& size) {
    font = TTF_OpenFont(path.c_str(), size);
}

void textObject::show(const int& x, const int& y, int opacity) {
    applyText(font, color, text, x, y, opacity);
}