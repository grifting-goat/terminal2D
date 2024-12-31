#ifndef ENTITY_H
#define ENTITY_H

#include <utility>

class Entity {

private:
    typedef int* HITBOX;
    HITBOX hitBox;

    float mass; //kg
    std::pair<float, float> momentum; //(kg * m) /s * <r,c>
    std::pair<float, float> position; //center of mass <r,c>

public:

    Entity();

    //settas

    void setMass(float newMass);

    void setPosition(std::pair<float, float> newPos);
    
    void setMomentum(std::pair<float, float> newMomenta);

    void setHitBox(int array[], int size);

    void incrementMomentum(std::pair<float, float> offset);

    void incrementPosition(std::pair<float, float> offSet);

    //gettas

    float getMass();

    std::pair<float, float> getPosition();

    std::pair<float, float> *getPositionRefs();
    
    std::pair<float, float> getMomentum();

    HITBOX getHitBox();

   ~Entity();
    
};

#endif //ENTITY_H