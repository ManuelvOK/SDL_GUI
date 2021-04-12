# Dependencies

 * sdl2
 * sdl2_ttf
 * sdl2_image
 * fontconfig

# Building

`make` builds an example application into `build/SDL_GUI`.
To Only build the lib use `make lib`.


# Usage

## linking

`make lib` builds the following two library files into `build/` that you will
have to link statically into your application:

 * libSDL_GUI.a
 * libSDL2_gfx.a
