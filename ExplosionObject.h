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
    void burn(baseObject* object, int numDup);
    void setNumFrames(const int& numFrames) {
        this->numFrames = numFrames;
        clip.resize(numFrames);
    }
protected:
    int numFrames;
    int frame;
    std::vector<SDL_Rect> clip;
};

#endif