#include <application.h>
#include <plugins/default_plugin.h>
#include <plugins/example_plugin.h>

using namespace SDL_GUI;

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;
    Application<ExamplePlugin, DefaultPlugin> app{"Application"};
    app.run();
    return 0;
}
