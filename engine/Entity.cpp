/*
Implementation file for Entity class

created by levi morris - 12/30/24
*/

#include "Entity.h"
#include <stdexcept>  

Entity::Entity() {
    mass = 100.0f; // Default mass
    momentum = {0.0f, 0.0f};
    position = {0.0f, 0.0f};
    hitBox = nullptr; // No hitbox by default
}

// Settas
void Entity::setMass(float newMass) {
    if (newMass < 0) {throw std::invalid_argument("Physics broke: Mass cannot be negative");}
    mass = newMass;
}

void Entity::setPosition(std::pair<float, float> newPos) {
    position = newPos;
}

void Entity::setMomentum(std::pair<float, float> newMomenta) {
    momentum = newMomenta;
}

void Entity::setHitBox(int array[], int size) {
     if (hitBox == nullptr) {hitBox = new int[size];}
     else {delete[] hitBox; hitBox = nullptr; setHitBox(array, size);}

     hitBox = array;
}

void Entity::incrementMomentum(std::pair<float, float> offset) {
    momentum.first += offset.first;
    momentum.second += offset.second;
}

void Entity::incrementPosition(std::pair<float, float> offset) {
    position.first += offset.first;
    position.second += offset.second;
}

//Gettas
float Entity::getMass() {
    return mass;
}

std::pair<float, float> Entity::getPosition() {
    return position;
}

std::pair<float, float> Entity::getMomentum() {
    return momentum;
}

Entity::HITBOX Entity::getHitBox() {
    return hitBox;
}

Entity::~Entity() {
    delete[] hitBox;
}