#ifndef BOAT_HPP
#define BOAT_HPP

#include "../interfaces/physical.hpp"
#include "../interfaces/graphical.hpp"
#include "../interfaces/updatable.hpp"
#include "../animation.hpp"

class Boat : public Updatable, public Graphical, public Physical {
public:
    Boat(Map *map, Vector3f position, Vector3f size);
    Vector3f &getPosition();
    Vector3f &getSize();
    bool isSolid();
    bool isPushable();
    bool hasFriction();
    void push(Vector3f direction);
    void update();
    void updateGraphical();
    void move();
    
private:
    void draw(RenderTarget &target, RenderStates states) const;

    Vector3f size;
    Vector3f position;
    Vector3f velocity;
    enum { Idle, Moving } movementState;
    
    Animation sprite;
};

#endif
