#ifndef TARGET_OBJECT__H
#define TARGET_OBJECT__H

#include "BaseObject.h"

using namespace std;
class targetObject: public baseObject {
public:
    targetObject();
    ~targetObject();
    void handleInputAction(SDL_Event events);
};

#endif