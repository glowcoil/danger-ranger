#include "map.hpp"
#include "map_manager.hpp"

#include <cmath>
#include <algorithm>
#include <iostream>

Map::Map() : State(), updatables(), graphicals(), physicals(), buttons() {

}

void Map::setWidth(int w) {
    width = w;
}
void Map::setHeight(int h) {
    height = h;
}
void Map::setDepth(int d) {
    depth = d;
}
int Map::getWidth() {
    return width;
}
int Map::getHeight() {
    return height;
}
int Map::getDepth() {
    return depth;
}

bool compare_z(Graphical *a, Graphical *b) {
    return a->getPosition().z < b->getPosition().z;
}
void Map::update() {
    if (Keyboard::isKeyPressed(Keyboard::R)) {
        resetMap();
    }

    for (std::set<Updatable *>::iterator i = updatables.begin(); i != updatables.end(); i++) {
        (*i)->update();
    }
    for (std::set<Physical *>::iterator i = physicals.begin(); i != physicals.end(); i++) {
        (*i)->move();
    }
    for (std::set<Graphical *>::iterator i = graphicals.begin(); i != graphicals.end(); i++) {
        (*i)->updateGraphical();
    }

    if (character) {
        view.reset(FloatRect(std::min(float(width * 16) - 240, std::max(float(0), character->getPosition().x - 112)),
                             std::min(float((height*12)+(depth*12)) - 160, std::max(float(0), float(int(character->getPosition().y)) - float(int(character->getPosition().z)) - 80)), 240, 160));
    }
}
void Map::draw(RenderTarget &target, RenderStates states) const {
    std::vector<std::vector<std::set<Graphical *> > > grid(height);
    for (int y = 0; y < height; y++) {
        grid[y] = std::vector<std::set<Graphical *> >(width);
        for (int x = 0; x < width; x++) {
            grid[y][x] = std::set<Graphical *>();
        }
    }

    for (std::set<Graphical *>::const_iterator p = graphicals.begin(); p != graphicals.end(); p++) {
        Vector3f pos = (*p)->getPosition(); Vector3f size = (*p)->getSize();
        grid[std::min(std::max(int(ceil(pos.y / 12)), 0), height-1)][std::min(std::max(int(ceil(pos.x / 16)), 0), width-1)].insert(*p);
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::vector<Graphical *> sortedGraphicals(grid[y][x].begin(), grid[y][x].end());
            std::sort(sortedGraphicals.begin(), sortedGraphicals.end(), compare_z);
            for (std::vector<Graphical *>::const_iterator g = sortedGraphicals.begin(); g != sortedGraphicals.end(); g++) {
                target.draw(**g, states);
            }
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::R)) {
        target.clear(Color(0, 0, 0, 255));
    }

}

void Map::addUpdatable(Updatable *updatable) {
    updatables.insert(updatable);
}
void Map::removeUpdatable(Updatable *updatable) {
    updatables.erase(updatable);
}
void Map::addGraphical(Graphical *graphical) {
    graphicals.insert(graphical);
}
void Map::removeGraphical(Graphical *graphical) {
    graphicals.erase(graphical);
}
void Map::addPhysical(Physical *physical) {
    physicals.insert(physical);
}
void Map::removePhysical(Physical *physical) {
    physicals.erase(physical);
}
void Map::addButton(Button *button, int index) {
    buttons[index] = button;
}
Button *Map::getButton(int index) {
    return buttons[index];
}

bool intersect(Vector3f position1, Vector3f size1, Vector3f position2, Vector3f size2) {
    if (position1.x < position2.x + size2.x && position1.x + size1.x > position2.x &&
        position1.y < position2.y + size2.y && position1.y + size1.y > position2.y &&
        position1.z < position2.z + size2.z && position1.z + size1.z > position2.z) {
        return true;
    }
    return false;
}

std::set<Physical *> Map::getIntersecting(Physical *physical, Vector3f offset) {
    std::set<Physical *> results;
    
    for (std::set<Physical *>::iterator i = physicals.begin(); i != physicals.end(); i++) {
        if (*i != physical && intersect(physical->getPosition() + offset, physical->getSize(), (*i)->getPosition(), (*i)->getSize())) {
            results.insert(*i);
        }
    }
    return results;
}

bool Map::intersectsSolid(Physical *physical, Vector3f offset) {
    std::set<Physical *> intersecting = getIntersecting(physical, offset);
    
    for (std::set<Physical *>::iterator i = intersecting.begin(); i != intersecting.end(); i++) {
        if ((*i)->isSolid()) {
            return true;
        }
    }
    return false;
}
bool Map::intersectsFriction(Physical *physical, Vector3f offset) {
    std::set<Physical *> intersecting = getIntersecting(physical, offset);
    
    for (std::set<Physical *>::iterator i = intersecting.begin(); i != intersecting.end(); i++) {
        if ((*i)->hasFriction()) {
            return true;
        }
    }
    return false;
}
bool Map::intersectsClimbable(Physical *physical, Vector3f offset) {
    std::set<Physical *> intersecting = getIntersecting(physical, offset);
    
    for (std::set<Physical *>::iterator i = intersecting.begin(); i != intersecting.end(); i++) {
        if ((*i)->isClimbable()) {
            return true;
        }
    }
    return false;
}
bool Map::intersectsWater(Physical *physical, Vector3f offset) {
    std::set<Physical *> intersecting = getIntersecting(physical, offset);
    
    for (std::set<Physical *>::iterator i = intersecting.begin(); i != intersecting.end(); i++) {
        if ((*i)->isWater()) {
            return true;
        }
    }
    return false;
}
bool Map::intersectsWarp(Physical *physical, Vector3f offset) {
    std::set<Physical *> intersecting = getIntersecting(physical, offset);
    
    for (std::set<Physical *>::iterator i = intersecting.begin(); i != intersecting.end(); i++) {
        if ((*i)->isWarp()) {
            return true;
        }
    }
    return false;
}
bool Map::intersectsBoat(Physical *physical, Vector3f offset) {
    return intersectsWater(physical, offset) && intersectsSolid(physical, offset);
}
bool Map::canPush(Physical *pusher, Vector3f direction) {
    std::set<Physical *> pushed = getIntersecting(pusher, direction);
        
    if (pushed.empty()) {
        return true;
    }
    
    if (!intersectsFriction(pusher, directionVector(Down))) {
        return false;
    }
    
    for (std::set<Physical *>::iterator i = pushed.begin(); i != pushed.end(); i++) {
        if (((*i)->isSolid() && !(*i)->isPushable()) || intersectsSolid(*i, direction) ||
            (intersectsWater(*i, direction * float(16) + directionVector(Down)) && !intersectsSolid(*i, direction * float(16) + directionVector(Down)) && !intersectsBoat(*i, directionVector(Down)))) {
            return false;
        }
    }
    return true;
}
bool Map::push(Physical *pusher, Vector3f direction) {
    std::set<Physical *> pushed = getIntersecting(pusher, direction * float(16));
    
    if (pushed.empty()) {
        return true;
    }
    
    if (!intersectsFriction(pusher, directionVector(Down))) {
        return false;
    }
    
    for (std::set<Physical *>::iterator i = pushed.begin(); i != pushed.end(); i++) {
        if (!(*i)->isPushable() || intersectsSolid(*i, direction) ||
            (intersectsWater(*i, direction * float(16) + directionVector(Down)) && !intersectsSolid(*i, direction * float(16) + directionVector(Down)) && !intersectsBoat(*i, directionVector(Down))))
            return false;
    }
    for (std::set<Physical *>::iterator i = pushed.begin(); i != pushed.end(); i++) {
        (*i)->push(direction);

        if (intersectsBoat(*i, directionVector(Down))) {
            // If the pushed object is standing on a boat
            std::set<Physical *> below = getIntersecting(*i, directionVector(Down));
            for (std::set<Physical *>::const_iterator i = below.begin(); i != below.end(); i++) {
                if ((*i)->isSolid() && !intersectsSolid(*i, direction)) {
                    (*i)->push(direction);
                    return false;
                }
            }
        }
    }
    return true;
}
