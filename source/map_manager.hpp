#ifndef MAP_MANAGER_HPP
#define MAP_MANAGER_HPP

#include "map.hpp"

#include <string>
#include <fstream>
#include <SFML/Audio.hpp>

#include "json/json.h"

void loadMap(const char *filename);
Map *getMap(int index);
void nextMap();
void resetMap();
void initMusic();
void playMusic();

#endif
