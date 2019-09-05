#include <views/view_base.h>

#include <SDL2/SDL.h>

#include <gui/drawable.h>

class InterfaceView : public ViewBase {
    SDL_Renderer *_renderer;

    Drawable *_draw_root = nullptr;
public:
    InterfaceView(SDL_Renderer *renderer);
    bool init() override;
    void deinit() override;
    void update() override;
    void render() override;
};
