#ifndef ICE_HPP
#define ICE_HPP

#include "../interfaces/physical.hpp"
#include "../map.hpp"

using namespace sf;

class Ice : public Physical {
public:
    Ice(Map *map, Vector3f position, Vector3f size);
    Vector3f &getPosition();
    Vector3f &getSize();
    bool isSolid();
    bool isPushable();
    bool hasFriction();
    void push(Vector3f d);
    
private:
    Vector3f size;
    Vector3f position;
};

#endif
