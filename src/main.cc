#include <application.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;
    Application app{"Application"};
    app.run();
    return 0;
}
