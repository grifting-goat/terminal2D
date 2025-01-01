/*
Implementation file for Entity class

created by levi morris - 12/30/24
*/

#include "Entity.h"
 

Entity::Entity() {
    mass = 0.0f; // Default mass
    momentum = {0.0f, 0.0f};
    position = {0.0f, 0.0f};
    resistance = 0.0f;
    health = 0.0f;
    force = 0.0f;

    //rules
    collisions = false;
    damage = false;
    locked = false;
    resistant = false;
}

// Settas
bool Entity::setMass(float newMass) {
    if (newMass < 0) {return 0;}
    mass = newMass;
    return true;
}

bool Entity::setPosition(std::pair<float, float> newPos) {
    if (!locked) {position = newPos; return true;}
    return false;

}

bool Entity::setMomentum(std::pair<float, float> newMomenta) {
    if (!locked) {momentum = newMomenta; return true;}
    return false;
}

bool Entity::setMomentumRow(float newMomenta) {
    if (!locked) {momentum.first = newMomenta; return true;}
    return false;
}

bool Entity::setMomentumCol(float newMomenta) {
    if (!locked) {momentum.second = newMomenta; return true;}
    return false;
}

bool Entity::setHealth(float newHealth) {
    if (damage) {health = newHealth; return true;}
    return false;
}

bool Entity::setForce(float newForce) {
    force = newForce; return true;

}

bool Entity::setResistance(float newResistance) {
    if (resistant) {resistance = newResistance; return true;}
    return false;
}

void Entity::setRules(bool newCol, bool newDam, bool newLock, bool newRes) {
    collisions = newCol;
    damage = newDam;
    locked = newLock;
    resistant = newRes;
}


void Entity::setHitBox(HITBOX box) {
    hitBox = box;
}


bool Entity::incrementMomentum(std::pair<float, float> offset) {
    if (!locked) {
        momentum.first += offset.first;
        momentum.second += offset.second;
        return true;
    }
    return false;
}

bool Entity::incrementMomentumRow(float offset) {
    if (!locked) {
        momentum.first += offset;
    }
    return false;
}

bool Entity::incrementMomentumCol(float offset) {
    if (!locked) {
        momentum.second += offset;
    }
    return false;
}

bool Entity::incrementPosition(std::pair<float, float> offset) {
    if (!locked) {
        position.first += offset.first; 
        position.second += offset.second;
        return true;
    }
    return false;
}

bool Entity::dealDamage(float amount) {
    if (!damage) {return false;}

    if(resistant) {
        if (amount > resistance) {
            health -= (amount - resistance);
        }
        return true;
    }
    else {health -= amount; return true;}
}

//Gettas
float Entity::getMass() {
    return mass;
}

float Entity::getHealth() {
    return health;
}

int Entity::getEntityRuleCount() const {
    return NUM_RULES;
}
bool** Entity::getEntityRules() {
    return entityRules;
}

float Entity::getForce() {
    return force;
}

float Entity::getResistance() {
    return resistance;
}

std::pair<float, float> Entity::getPosition() {
    return position;
}

std::pair<float, float>* Entity::getPositionRefs() {
    return &position;
}

std::pair<float, float> Entity::getMomentum() {
    return momentum;
}

Entity::HITBOX Entity::getHitBox() {
    return hitBox;
}


void Entity::attachGame(Game &newGame) {
    game = &newGame;
}
