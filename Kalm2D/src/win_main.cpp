
#include <windows.h>
#include "win_main.h"

static const u32 memoryByteSize = 64*1024;
static gameImport_t systemExport;
static engineAPI_t engineAPI;

const std::string WELCOME_MSG(std::string() +
        "\n\nKalm2D OpenGL Engine\n" +
        "\n(c) Kasper Sauramo, 2018\n" +
        "Compiled " + __DATE__ + " " + __TIME__ "\n" +
        "any@kaspersauramo.me\n\n"
);

engineAPI_t win_loadGame() {
    engineAPI_t api = {};

    HMODULE dll = LoadLibrary("Game64.dll");
    if( dll ) {
        PRINTL_STR( "Game64.dll loaded");

        api.engine = (kGame *)GetProcAddress( dll, "GetAPI");
        if( api.engine ) {
            PRINTL_STR( "GetAPI found");
        }
    }
    return api;
}


int main(int argc, char *argv[])
{
    printf("%s", WELCOME_MSG.c_str());

    /** initialize subsystems */
    kMemory memory( memoryByteSize);

    engineAPI = win_loadGame();

    /** prepare an export for the engine */
    systemExport.version = 1;
    //systemExport.memorySystem = &memory;

    /** prepare engine */
    //Kalm2D engine;

    //engine.Initialize( &systemExport);

    /*
     * main loop
     */
    //engine.Loop();

    /** destroy things */
    //engine.Terminate();

    return EXIT_SUCCESS;
}

