#include "tile.hpp"
#include "../image_manager.hpp"

Tile::Tile(Vector3f position, Vector3f size, const char *filename, IntRect tile) : position(position), size(size) {
    sprite.setTexture(getTexture(filename));
    sprite.setTextureRect(tile);
    sprite.setPosition(position.x, position.y - position.z - 12);
}

Vector3f &Tile::getPosition() {
    return position;
}
Vector3f &Tile::getSize() {
    return size;
}

void Tile::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite, states);
}
void Tile::updateGraphical() {

}