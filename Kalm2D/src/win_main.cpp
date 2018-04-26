
#include "win_main.h"

const std::string WELCOME_MSG(std::string() +
        "\n\nKalm2D OpenGL Engine\n" +
        "\n(c) Kasper Sauramo, 2018\n" +
        "Compiled " + __DATE__ + " " + __TIME__ "\n" +
        "any@kaspersauramo.me\n\n"
);

int main(int argc, char *argv[])
{

    printf("%s", WELCOME_MSG.c_str());
    InitializeGraphicsContext();

    /*
     * main loop
     */
    KalmLoop();

    KalmTerminate();

    return EXIT_SUCCESS;
}

