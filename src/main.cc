#include <application.h>
#include <plugins/default_plugin.h>
#include <plugins/example_plugin.h>

using namespace SDL_GUI;

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;
    Application<DefaultPlugin, ExamplePlugin> app{"Application", argc, argv};
    app.run();
    return 0;
}
