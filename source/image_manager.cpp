#include "image_manager.hpp"
#include <list>
#include <SFML/OpenGL.hpp>

Texture &getTexture(std::string path) {
    static std::map<std::string, Texture> textures;
    
    if (textures.count(path) > 0) {
        return textures[path];
    } else {
        Texture &t = textures[path] = Texture();
        t.loadFromFile(path);
        glFlush();
        return t;
    }
}
