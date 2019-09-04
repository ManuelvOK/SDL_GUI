#include <view/view_base.h>

#include <SDL2/SDL.h>

class InterfaceView : public ViewBase {
    SDL_Renderer *_renderer;
public:
    InterfaceView(SDL_Renderer *renderer);
    bool init() override;
    void deinit() override;
    void update() override;
    void render() override;
};
