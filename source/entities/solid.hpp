#ifndef SOLID_HPP
#define SOLID_HPP

#include <SFML/System.hpp>
using namespace sf;

#include "../interfaces/physical.hpp"

class Solid : public Physical {
public:
    Solid(Map *map, Vector3f position, Vector3f solid, bool friction = true);
    Vector3f &getPosition();
    Vector3f &getSize();
    bool isSolid();
    bool isPushable();
    bool hasFriction();
    void push(Vector3f direction);
    
private:
    Vector3f size;
    Vector3f position;
    bool friction;
};

#endif
