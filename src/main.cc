#include <example_application.h>

using namespace SDL_GUI;

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;
    ExampleApplication app{"Application"};
    app.run();
    return 0;
}
