#ifndef EXPLOSION_OBJECT__H
#define EXPLOSION_OBJECT__H

#include "BaseObject.h"

using namespace std;

class explosionObject: virtual public baseObject {
public:
    explosionObject();
    ~explosionObject();
    void setClip();
    void setFrame(const int& frame) {
        this->frame = frame;
    }
    SDL_Rect getClip(const int& i) const {
        return clip[i];
    }
    void show();
    void nextFrame() {
        ++frame;
    }
    int completed() {
        return (frame >= numFrames);
    }
    void burn(baseObject* object, int numDup);
    void setNumFrames(const int& numFrames) {
        this->numFrames = numFrames;
        clip.resize(numFrames);
    }
    baseObject* getObject() {
        return object;
    }
protected:
    int numFrames, frame = 0;
    std::vector<SDL_Rect> clip;
    baseObject* object;
};

#endif