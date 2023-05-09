#ifndef TARGET__H
#define TARGET__H

#include "BaseObject.h"

using namespace std;
class target: public baseObject {
public:
    target();
    ~target();
    void handleInputAction(SDL_Event events);
};

#endif