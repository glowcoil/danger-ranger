#include "map_manager.hpp"
#include "json/json.h"
#include "entities/tile.hpp"
#include "entities/solid.hpp"
#include "entities/ice.hpp"
#include "entities/boulder.hpp"
#include "entities/ladder.hpp"
#include "entities/grass_button.hpp"
#include "entities/door.hpp"
#include "entities/water.hpp"
#include "entities/boat.hpp"
#include "entities/character.hpp"
#include "entities/warp.hpp"
#include "entities/crashed_airplane.hpp"

#include "states/ending.hpp"

#include "image_manager.hpp"

#include <sstream>

std::vector<Map *> maps;
std::vector<const char *> mapFilenames;
int mapIndex = -1;

Music soundtrack;

void initMusic() {
    soundtrack.openFromFile("music.ogg");
    soundtrack.setLoop(true);
}
void playMusic() {
    soundtrack.play();
}

void loadMap(const char *filename) {
    maps.push_back(new Map());
    mapFilenames.push_back(filename);
    Map *map = maps[maps.size()-1];

    std::ifstream mapFile(filename);
    std::string mapText((std::istreambuf_iterator<char>(mapFile)), (std::istreambuf_iterator<char>()));

    Json::Value mapRoot;
    Json::Reader reader;
    if (reader.parse(mapText, mapRoot)) {
        unsigned int tileWidth = mapRoot["tileWidth"].asInt();
        unsigned int tileHeight = mapRoot["tileHeight"].asInt();
        unsigned int tileDepth = mapRoot["tileDepth"].asInt();
        Texture &tileset = getTexture(mapRoot["tileset"].asCString());

        std::string tilesetFilename = mapRoot["tileset"].asString();
        std::ifstream schemaFile(tilesetFilename.substr(0, tilesetFilename.length() - 4).append(".schema").c_str());
        std::string schemaText((std::istreambuf_iterator<char>(schemaFile)), (std::istreambuf_iterator<char>()));

        Json::Value schemaRoot;
        if (reader.parse(schemaText, schemaRoot)) {
            const Json::Value tiles = mapRoot["tiles"];
            map->setDepth(tiles.size());
            map->setHeight(tiles[0].size());
            map->setWidth(tiles[0][0].size());
		    for (unsigned int z = 0; z < tiles.size(); z++) {
                const Json::Value layer = tiles[z];
			    for (unsigned int y = 0; y < layer.size(); y++) {
                    const Json::Value row = layer[y];
                    for (unsigned int x = 0; x < row.size(); x++) {
                        unsigned int tilesetWidth = tileset.getSize().x / tileWidth;
                        unsigned int tilesetHeight = tileset.getSize().y / tileHeight;
                        int tile = row[x].asInt();
                        Vector3f tilePosition = Vector3f(float(x * tileWidth), float(y * tileHeight), float(z * tileDepth));
                        Vector3f tileSize = Vector3f(float(tileWidth), float(tileHeight), float(tileDepth));
                        if (schemaRoot[tile].isString()) {
                            if (schemaRoot[tile].compare("solid") == 0) {
                                map->addPhysical(new Solid(map, tilePosition, tileSize));
                                map->addGraphical(new Tile(tilePosition, tileSize, mapRoot["tileset"].asCString(), IntRect((tile % tilesetWidth) * tileWidth, (tile / tilesetWidth) * (tileHeight + tileDepth), tileWidth, tileHeight + tileDepth)));
                            } else if (schemaRoot[tile].compare("ice") == 0) {
                                map->addPhysical(new Solid(map, tilePosition, tileSize, false));
                                map->addGraphical(new Tile(tilePosition, tileSize, mapRoot["tileset"].asCString(), IntRect((tile % tilesetWidth) * tileWidth, (tile / tilesetWidth) * (tileHeight + tileDepth), tileWidth, tileHeight + tileDepth)));
                            } else if (schemaRoot[tile].compare("boulder") == 0) {
                                Boulder *b = new Boulder(map, tilePosition);
                                map->addPhysical(b);
                                map->addUpdatable(b);
                                map->addGraphical(b);
                            } else if (schemaRoot[tile].compare("ladder") == 0) {
                                map->addPhysical(new Ladder(map, tilePosition, tileSize));
                                map->addGraphical(new Tile(tilePosition, tileSize, mapRoot["tileset"].asCString(), IntRect((tile % tilesetWidth) * tileWidth, (tile / tilesetWidth) * (tileHeight + tileDepth), tileWidth, tileHeight + tileDepth)));
                            } else if (schemaRoot[tile].compare("water") == 0) {
                                map->addPhysical(new Water(map, tilePosition, tileSize));
                                map->addGraphical(new Tile(tilePosition, tileSize, mapRoot["tileset"].asCString(), IntRect((tile % tilesetWidth) * tileWidth, (tile / tilesetWidth) * (tileHeight + tileDepth), tileWidth, tileHeight + tileDepth)));
                            } else if (schemaRoot[tile].compare("boat") == 0) {
                                Boat *boat = new Boat(map, tilePosition + Vector3f(0, 0, -11), tileSize + Vector3f(0, 0, -1));
                                map->addPhysical(boat);
                                map->addGraphical(boat);
                                map->addUpdatable(boat);
                            } else if (schemaRoot[tile].compare("character") == 0) {
                                Character *character = new Character(map, tilePosition);
                                map->addPhysical(character);
                                map->addGraphical(character);
                                map->addUpdatable(character);
                                map->character = character;
                            } else if (schemaRoot[tile].compare("end") == 0) {
                                Warp *warp = new Warp(map, tilePosition, tileSize);
                                map->addPhysical(warp);
                            }
                        } else if (schemaRoot[tile].isObject()) {
                            if (schemaRoot[tile]["type"].compare("grass_button") == 0) {
                                GrassButton *button = new GrassButton(map, tilePosition, tileSize);
                                map->addPhysical(button);
                                map->addUpdatable(button);
                                map->addGraphical(button);
                                map->addButton(button, schemaRoot[tile]["index"].asInt());
                            } else if (schemaRoot[tile]["type"].compare("door") == 0) {
                                Door *door = new Door(map, tilePosition, tileSize, schemaRoot[tile]["index"].asInt());
                                map->addPhysical(door);
                                map->addUpdatable(door);
                                map->addGraphical(door);
                            }
                        }
                    }
                }
            }
        }
    }
}

Map *getMap(int index) {
    return maps[index];
}

void nextMap() {
    if (mapIndex < 5) {
        mapIndex++;
        std::stringstream n;
        n << mapIndex << ".map";
        loadMap(n.str().c_str());
        if (mapIndex == 0) {
            maps[mapIndex]->addGraphical(new CrashedAirplane(Vector3f(16, 128, 100)));
        }
        changeState(getMap(mapIndex));
    } else {
        changeState(new Ending());
    }
}

void resetMap() {
    maps.pop_back(); mapFilenames.pop_back();
    mapIndex--;
    nextMap();
}