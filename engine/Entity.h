#ifndef ENTITY_H
#define ENTITY_H

#include <utility>
#include <vector>
#include <stdexcept> 

//#include "Game.h"

class Game;


class Entity {

public:

    typedef std::vector<std::pair<int,int>> HITBOX;

private:
    HITBOX hitBox;

    float health;
    float mass; //kg
    float resistance;
    std::pair<float, float> momentum; //(kg * m) /s * <r,c>
    std::pair<float, float> position; //center of mass <r,c>
    float force; //Newtons 

    //rules
    static const int NUM_RULES = 4;
    bool collisions; //can it colide with other things
    bool damage; //can it take damage
    bool locked; //can it move
    bool resistant; //only takes damage over a certain threshold

    bool* entityRules[NUM_RULES] = {&collisions, &damage, &locked, &resistant};

    Game *game = nullptr; //get map


public:

    Entity();

    //settas

    bool setMass(float newMass);

    bool setPosition(std::pair<float, float> newPos);
    
    bool setMomentum(std::pair<float, float> newMomenta);

    bool setMomentumRow(float newMomenta);

    bool setMomentumCol(float newMomenta);

    bool setHealth(float newHealth);

    bool setForce(float newForce);

    bool setResistance(float newResistance);

    void setHitBox(HITBOX box);

    //collisions, damage, locked, resistant
    void setRules(bool newCol, bool newDam, bool newLock, bool newRes);

    bool incrementMomentum(std::pair<float, float> offset);

    bool incrementMomentumRow(float offset);

    bool incrementMomentumCol(float offset);

    bool incrementPosition(std::pair<float, float> offSet);

    bool dealDamage(float amount);


    //gettas

    float getMass();

    float getHealth();

    float getForce();

    float getResistance();

    int getEntityRuleCount() const; //returns the number of rules

    bool** getEntityRules();

    std::pair<float, float> getPosition();

    std::pair<float, float> *getPositionRefs();
    
    std::pair<float, float> getMomentum();

    HITBOX getHitBox();

    //attach game
    void attachGame(Game &newGame);
    
};

#endif //ENTITY_H