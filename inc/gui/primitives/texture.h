#pragma once

#include <string>

#include "../drawable.h"
#include "../../application.h"

namespace SDL_GUI {
class Texture : public Drawable {
    std::string _path;
    static std::map<std::string, SDL_Texture *> _textures;
    friend Application::~Application();
    SDL_Texture *_texture;
public:
    Texture(std::string path, SDL_Renderer *renderer);

    void draw(SDL_Renderer *renderer, Position position) const override;

};
}
