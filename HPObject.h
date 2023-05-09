#ifndef HP_OBJECT__H
#define HP_OBJECT__H

#include "BaseObject.h"

using namespace std;
class hpObject: public baseObject {
public:
    hpObject();
    ~hpObject();
    void loadImage(const std::string& path0, const std::string& path1);
    void show();
    int getHP() const {
        return HP;
    }
    void addHP() {
        if (HP == 5) return;
        ++HP;
    }
    void subHP() {
        --HP;
    }
private:
    std::vector<baseObject*> hearts[2];
    int HP;
};

#endif