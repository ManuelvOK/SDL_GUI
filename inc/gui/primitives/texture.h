#pragma once

#include <string>

#include "../drawable.h"

namespace SDL_GUI {
class Texture : public Drawable {
    std::string _path;
    SDL_Texture *_texture;
public:
    static std::map<std::string, SDL_Texture *> _textures;
    Texture(std::string path, SDL_Renderer *renderer);

    void draw(SDL_Renderer *renderer, Position position) const override;

};
}
