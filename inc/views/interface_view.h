#include <views/view_base.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <gui/drawable.h>
#include <models/mouse_input_model.h>
#include <util/tree.h>

class InterfaceView : public ViewBase {
    /**
     * SDL Renderer to render on
     */
    SDL_Renderer *_renderer;
    /**
     * Font to us for text
     */
    TTF_Font *_font;

    /**
     * path to template file
     */
    const std::string _template_file_path;

    /**
     * pointer to the mouse intput model
     */
    const MouseInputModel *_mouse_input_model = nullptr;

    /**
     * Tree of Drawables that get rendered
     */
    Tree<Drawable> *_draw_tree;
public:
    /**
     * Constructor
     * @param renderer The SDL renderer to render on
     * @param remplate_file_path path to template file
     */
    InterfaceView(SDL_Renderer *renderer, std::string template_file_path);
    /**
     * set the reference to the moude input model
     * @param mouse_input_model pointer to the mouse input model
     */
    void set_mouse_input_model(const MouseInputModel *mouse_input_model);

    bool init() override;
    void deinit() override;
    void update() override;
    void render() override;
};
