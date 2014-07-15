#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "interfaces/updatable.hpp"
#include "interfaces/physical.hpp"
#include "interfaces/graphical.hpp"
#include "interfaces/button.hpp"
#include <set>
#include <vector>

using namespace sf;

class Map : public State {
public:
    Map();

    void setWidth(int width);
    void setHeight(int height);
    void setDepth(int depth);
    int getWidth();
    int getHeight();
    int getDepth();

    void update();
    
    void addUpdatable(Updatable *updatable);
    void removeUpdatable(Updatable *updatable);
    
    void addGraphical(Graphical *graphical);
    void removeGraphical(Graphical *graphical);

    void addPhysical(Physical *physical);
    void removePhysical(Physical *physical);
    
    void addButton(Button *button, int index);
    Button *getButton(int index);

    Physical *character;

    std::set<Physical *> getIntersecting(Physical *physical, Vector3f offset = Vector3f(0, 0, 0));
    bool intersectsSolid(Physical *physical, Vector3f offset = Vector3f(0, 0, 0));
    bool intersectsFriction(Physical *physical, Vector3f offset = Vector3f(0, 0, 0));
    bool intersectsClimbable(Physical *physical, Vector3f offset = Vector3f(0, 0, 0));
    bool intersectsWater(Physical *physical, Vector3f offset = Vector3f(0, 0, 0));
    bool intersectsBoat(Physical *physical, Vector3f offset = Vector3f(0, 0, 0));
    bool intersectsWarp(Physical *physical, Vector3f offset = Vector3f(0, 0, 0));
    bool canPush(Physical *pusher, Vector3f direction);
    bool push(Physical *pusher, Vector3f direction);

private:
    void draw(RenderTarget &target, RenderStates states) const;
    std::set<Updatable *> updatables;
    std::set<Graphical *> graphicals;
    std::set<Physical *> physicals;
    std::map<int, Button *> buttons;

    int width;
    int height;
    int depth;
};

#endif
