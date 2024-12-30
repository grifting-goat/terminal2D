#ifndef ENTITY_H
#define ENTITY_H

#include <utility>

class Entity {

private:
    typedef int HITBOX[];

    float mass; //kg
    std::pair<float, float> momentum; //(kg * m) /s * <r,c>
    std::pair<float, float> position; //center of mass <r,c>

public:

    Entity();

};

#endif //ENTITY_H