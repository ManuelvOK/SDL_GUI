#include <application.h>
#include <plugins/core.h>
#include <plugins/example_plugin.h>

using namespace SDL_GUI;

int main(int argc, char *argv[]) {
    Application<Core, ExamplePlugin> app{"Application", argc, argv};
    app.run();
    return 0;
}
