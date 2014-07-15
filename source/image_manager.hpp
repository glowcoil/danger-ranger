#ifndef IMAGE_MANAGER_HPP
#define IMAGE_MANAGER_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;

Texture &getTexture(std::string path);

#endif
