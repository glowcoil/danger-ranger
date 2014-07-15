#ifndef LADDER_HPP
#define LADDER_HPP

#include "../interfaces/physical.hpp"
#include "../interfaces/graphical.hpp"
#include "../interfaces/updatable.hpp"

class Ladder : public Physical {
public:
    Ladder(Map *map, Vector3f position, Vector3f size);
    Vector3f &getPosition();
    Vector3f &getSize();
    bool isSolid();
    bool isPushable();
    bool hasFriction();
    bool isClimbable();
    void push(Vector3f direction);
    
private:
    Vector3f size;
    Vector3f position;
};

#endif
