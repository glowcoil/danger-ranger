#ifndef WARP_HPP
#define WARP_HPP

#include <SFML/System.hpp>
using namespace sf;

#include "../interfaces/physical.hpp"

class Warp : public Physical {
public:
    Warp(Map *map, Vector3f position, Vector3f solid);
    Vector3f &getPosition();
    Vector3f &getSize();
    bool isSolid();
    bool isPushable();
    bool hasFriction();
    bool isWarp();
    void push(Vector3f direction);
    
private:
    Vector3f size;
    Vector3f position;
};

#endif
