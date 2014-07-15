#ifndef DOOR_HPP
#define DOOR_HPP

#include "../interfaces/physical.hpp"
#include "../interfaces/graphical.hpp"
#include "../interfaces/updatable.hpp"

class Door : public Physical, public Graphical, public Updatable {
public:
    Door(Map *map, Vector3f position, Vector3f size, int index);
    Vector3f &getPosition();
    Vector3f &getSize();
    bool isSolid();
    bool isPushable();
    bool hasFriction();
    void push(Vector3f direction);
    void move();
    void update();
    void updateGraphical();
    
private:
    void draw(RenderTarget &target, RenderStates states) const;
    
    Vector3f size;
    Vector3f position;
    Vector3f velocity;
    enum { High, MovingDown, Low, MovingUp } movementState;
    int zOrigin, zOffset;
    
    int index;
    
    Sprite sprite;
};

#endif
