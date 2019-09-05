#include <views/view_base.h>

#include <SDL2/SDL.h>

#include <gui/drawable.h>
#include <models/mouse_input_model.h>

class InterfaceView : public ViewBase {
    SDL_Renderer *_renderer;

    const MouseInputModel *_mouse_input_model = nullptr;

    Drawable *_draw_root = nullptr;
public:
    InterfaceView(SDL_Renderer *renderer);
    void set_mouse_input_model(const MouseInputModel *mouse_input_model);
    bool init() override;
    void deinit() override;
    void update() override;
    void render() override;
};
