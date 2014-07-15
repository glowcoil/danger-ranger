#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "../interfaces/updatable.hpp"
#include "../interfaces/physical.hpp"
#include "../interfaces/graphical.hpp"
#include "../interfaces/moving.hpp"
#include "../animation.hpp"

using namespace sf;

class Character : public Updatable, public Moving, public Graphical {
public:
    Character(Map *map, Vector3f position);
    void update();
    Vector3f &getPosition();
    Vector3f &getSize();
    bool isSolid();
    bool isPushable();
    bool hasFriction();
    void push(Vector3f direction);
    void updateGraphical();
    void move();
    
private:
    void draw(RenderTarget &target, RenderStates states) const;
    
    Texture texture;
    Animation sprite;
    Vector3f size;
    enum Direction direction;
    void walk(Direction d);
    enum MovementState { IdleWalking, Turning, IdleStanding, Walking, Falling, ClimbingIdle, ClimbingUp, ClimbingDown } movementState;
    int timer;
};

#endif
