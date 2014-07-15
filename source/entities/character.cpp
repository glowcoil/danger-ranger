#include "character.hpp"
#include "../image_manager.hpp"
#include "../map_manager.hpp"
#include "shadow.hpp"
#include "../state.hpp"
#include <cmath>

static enum Direction getKeyboardDirection();

Character::Character(Map *map, Vector3f position) : texture(), sprite(), Moving(map, position, Vector3f(0, 0, 0)), size(16, 12, 24), direction(South), movementState(IdleStanding), timer(0) {
    texture.loadFromFile("character.png");
    sprite.setTexture(texture);
    sprite.setSize(Vector2i(16, 24));
    sprite.setFrames(4);
    sprite.setDelay(8);
    Shadow *shadow = new Shadow(map, this);
    getMap()->addGraphical(shadow);
}

void Character::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite, states);
}
void Character::update() {
    if (getMap()->intersectsWarp(this, directionVector(direction))) {
        nextMap();
    }

    Direction d;
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        d = East;
    } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
        d = West;
    } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
        d = South;
    } else if (Keyboard::isKeyPressed(Keyboard::Up)) {
        d = North;
    } else {
        d = None;
    }
    
    switch (movementState) {
    break; case IdleWalking: case IdleStanding:
        if (getMap()->intersectsSolid(this, directionVector(Down))) {
            // If player is standing on the ground
            if (d != None) {
                // If a directional key is pressed
                if (direction == d) {
                    // If the player wants to walk in the same direction as they are facing
                    bool willLandOnWater = false;
                    if (!getMap()->intersectsBoat(this, directionVector(Down))) {
                        for (Vector3f offset(0, 0, 0); offset.z > -60; offset.z -= 12) {
                            if (!getMap()->getIntersecting(this, directionVector(direction) * float(16) + directionVector(Down) + offset).empty()) {
                                if (getMap()->intersectsWater(this, directionVector(direction) * float(16) + directionVector(Down) + offset) && !getMap()->intersectsSolid(this, directionVector(direction) * float(16) + directionVector(Down) + offset)) {
                                    willLandOnWater = true;
                                }
                                break;
                            }
                        }
                    }
                    if (getMap()->push(this, directionVector(direction)) && !willLandOnWater) {
                        // If the way to walk is clear
                        if (getMap()->intersectsBoat(this, directionVector(Down))) {
                            // If the player is standing on a boat
                            std::set<Physical *> below = getMap()->getIntersecting(this, directionVector(Down));
                            for (std::set<Physical *>::const_iterator i = below.begin(); i != below.end(); i++) {
                                if ((*i)->isSolid()) (*i)->push(directionVector(d));
                            }
                        } else if (movementState == IdleStanding) {
                            // If the player's walk cycle is starting over
                            sprite.stop();
                            sprite.play();
                            sprite.setDelay(8);
                            sprite.setTime(4);
                        } else {
                            // If the player's walk cycle is continuing
                            sprite.play();
                        }
                        movementState = Walking;
                        velocity = directionVector(direction);
                    } else if (getMap()->intersectsClimbable(this, directionVector(d))) {
                        // The player is walking against a ladder
                        movementState = ClimbingUp;
                        velocity = float(.5)*directionVector(Up);
                        sprite.setDelay(12);
                        sprite.setTime(4);
                        sprite.play();
                    }
                } else {
                    // If the player wants to change directions
                    movementState = Turning;
                    direction = d;
                    sprite.setFrameOffset(direction * 4);
                    sprite.setFrame(3);
                }
            }
        } else {
            // If there is nothing below the player
            movementState = Falling;
            velocity = Vector3f(0, 0, 0) + float(.5)*directionVector(Down);
        }
    break; case Turning:
        if (timer == 5) {
            timer = 0;
            movementState = IdleStanding;
        } else {
            if (timer == 3) {
                sprite.stop();
            }
            timer += 1;
        }
    break; case Walking:
        if (Vector3f(Vector3i(position)) == position && int(position.x) % 16 == 0 && position.y == float(int(position.y)) && int(position.y) % 12 == 0) {
            // If aligned to the tile grid
            if (getMap()->intersectsSolid(this, directionVector(Down))) {
                // If standing on the ground
                if (direction == d || !getMap()->intersectsFriction(this, directionVector(Down))) {
                    // If player wants to keep walking or is sliding
                    bool willLandOnWater = false;
                    if (!getMap()->intersectsBoat(this, directionVector(Down))) {
                        for (Vector3f offset(0, 0, 0); offset.z > -60; offset.z -= 12) {
                            if (!getMap()->getIntersecting(this, directionVector(direction) * float(16) + directionVector(Down) + offset).empty()) {
                                if (getMap()->intersectsWater(this, directionVector(direction) * float(16) + directionVector(Down) + offset) && !getMap()->intersectsSolid(this, directionVector(direction) * float(16) + directionVector(Down) + offset)) {
                                    willLandOnWater = true;
                                }
                                break;
                            }
                        }
                    }
                    if (getMap()->push(this, directionVector(direction)) && !willLandOnWater) {
                        // If the way to walk is clear
                        
                        if (getMap()->intersectsBoat(this, directionVector(Down))) {
                            // If the player is standing on a boat
                            std::set<Physical *> below = getMap()->getIntersecting(this, directionVector(Down));
                            for (std::set<Physical *>::const_iterator i = below.begin(); i != below.end(); i++) {
                                if ((*i)->isSolid()) (*i)->push(directionVector(d));
                            }
                            sprite.pause();
                        }
                        
                        if (!getMap()->intersectsFriction(this, directionVector(Down))) {
                            // If on ice
                            sprite.pause();
                        }
                    } else {
                        // If there is a solid in the way
                        if (getMap()->intersectsClimbable(this, directionVector(d))) {
                            // The player is walking against a ladder
                            movementState = ClimbingUp;
                            velocity = float(.5)*directionVector(Up);
                            sprite.setDelay(12);
                            sprite.setTime(4);
                            sprite.play();
                        } else {
                            // The player is walking against a wall
                            sprite.pause();
                            velocity = Vector3f(0, 0, 0);
                            movementState = IdleWalking;
                        }
                    }
                } else {
                    // If player wants to stop or change direction and is not sliding
                    sprite.pause();
                    velocity = Vector3f(0, 0, 0);
                    if (d == None) {
                        movementState = IdleWalking;
                    } else {
                        movementState = IdleStanding;
                    }
                }
            } else {
                // If there is nothing below the player
                if (getMap()->intersectsClimbable(this, -directionVector(direction) + directionVector(Down))) {
                    // There is a ladder behind the player
                    switch (direction) {
                    break; case South:
                        direction = North;
                    break; case North:
                        direction = South;
                    break; case West:
                        direction = East;
                    break; case East:
                        direction = West;
                    break; default: break;
                    }
                    sprite.setFrameOffset(direction * 4);
                    movementState = ClimbingDown;
                    velocity = float(.5) * directionVector(Down);
                    sprite.stop();
                    sprite.setDelay(12);
                    sprite.setTime(4);
                    sprite.play();
                } else {
                    // There is no ladder behind the player
                    movementState = Falling;
                    sprite.pause();
                    velocity = float(.5)*directionVector(Down);
                }
            }
        }
    break; case Falling:        
        if (getMap()->intersectsSolid(this, velocity)) {
            velocity = Vector3f(0, 0, 0);
            position = Vector3f(position.x, position.y, 12*int(position.z / 12));
            movementState = IdleStanding;
        } else {
            velocity += float(.5)*directionVector(Down);
        }
    break; case ClimbingIdle:
        if (d == North) {
            movementState = ClimbingUp;
            velocity = float(.5) * directionVector(Up);
            sprite.play();
        } else if (d == South) {
            movementState = ClimbingDown;
            velocity = float(.5) * directionVector(Down);
            sprite.play();
        }
    break; case ClimbingUp:
        if (Vector3f(Vector3i(position)) == position && int(position.z) % 12 == 0) {
            // If z is aligned to the tile grid
            if (getMap()->intersectsClimbable(this, directionVector(direction))) {
                // If there is more ladder
                velocity = Vector3f(0, 0, 0);
                sprite.pause();
                movementState = ClimbingIdle;
            } else {
                // If the player has reached the top of the ladder
                movementState = Walking;
                velocity = directionVector(direction);
                sprite.stop();
                sprite.setDelay(8);
                sprite.setTime(4);
                sprite.play();
            }
        }
    break; case ClimbingDown:
        if (Vector3f(Vector3i(position)) == position && int(position.z) % 12 == 0) {
            // If z is aligned to the tile grid
            if (getMap()->intersectsSolid(this, directionVector(Down))) {
                // If player is standing on the ground
                velocity = Vector3f(0, 0, 0);
                sprite.stop();
                switch (direction) {
                    break; case South:
                        direction = North;
                    break; case North:
                        direction = South;
                    break; case West:
                        direction = East;
                    break; case East:
                        direction = West;
                    break; default: break;
                }
                sprite.setFrameOffset(direction * 4);
                movementState = IdleStanding;
            } else {
                // If there is more ladder
                velocity = Vector3f(0, 0, 0);
                sprite.pause();
                movementState = ClimbingIdle;
            }
        }
    }
    
    sprite.update();
        
    //std::cout << "c:"<<position.x << "," << position.y << "," << position.z << std::endl;
    //std::cout << movementState << std::endl;
}
void Character::move() {
    if (((velocity.x != 0 || velocity.y != 0) && getMap()->canPush(this, velocity)) || velocity.z != 0) {
        position += velocity;
    }
}
void Character::updateGraphical() {
    sprite.setLocation(Vector3f(Vector3i(Vector3f(position.x, position.y - 14, position.z))));
}
Vector3f &Character::getPosition() {
    return position;
}
Vector3f &Character::getSize() {
    return size;
}
bool Character::isSolid() {
    return true;
}
bool Character::isPushable() {
    return true;
}
bool Character::hasFriction() {
    return true;
}
void Character::push(Vector3f d) {
    
}
