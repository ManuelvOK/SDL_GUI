#pragma once

#include <SDL2/SDL.h>

#include "view_base.h"
#include "../models/interface_model.h"

namespace SDL_GUI {
class InterfaceView : public ViewBase {
protected:
    /**
     * SDL Renderer to render on
     */
    SDL_Renderer *_renderer;

    /**
     * pointer to the interface model
     */
    const InterfaceModel *_interface_model;

public:
    /**
     * Constructor
     * @param renderer The SDL renderer to render on
     */
    InterfaceView(SDL_Renderer *renderer, const InterfaceModel *interface_model);

    bool init() override;
    void deinit() override;
    void update() override;
    void render() override;
};
}
