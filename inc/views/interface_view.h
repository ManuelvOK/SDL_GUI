#include <views/view_base.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <gui/drawable.h>
#include <models/mouse_input_model.h>

class InterfaceView : public ViewBase {
    SDL_Renderer *_renderer;
    TTF_Font *_font;

    const std::string _template_file_path;

    const MouseInputModel *_mouse_input_model = nullptr;

    Drawable *_draw_root = nullptr;
public:
    InterfaceView(SDL_Renderer *renderer, std::string template_file_path);
    void set_mouse_input_model(const MouseInputModel *mouse_input_model);
    bool init() override;
    void deinit() override;
    void update() override;
    void render() override;
};
