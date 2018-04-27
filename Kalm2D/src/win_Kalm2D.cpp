
#include <windows.h>
#include "win_Kalm2D.h"

#include "Systems.h"
#include "Memory.cpp"
#include "Filesystem.cpp"

/** GetGameAPI function definition */
typedef gameExport_t* (*GameAPI)( gameImport_t *);

static const u32 memoryByteSize = 32*1024;

gameImport_t g_gameImport = {};
gameExport_t * g_gameExport = nullptr;

//gameExport_t * GetGameAPI( gameImport_t *import);

const std::string WELCOME_MSG(std::string() +
        "\n\nKalm2D OpenGL Engine\n" +
        "\n(c) Kasper Sauramo, 2018\n" +
        "Compiled " + __DATE__ + " " + __TIME__ "\n" +
        "any@kaspersauramo.me\n\n"
);

gameExport_t * win_LoadGame() {
    HMODULE dll = LoadLibrary("Game64.dll");
    GameAPI gameAPI = nullptr;
    if( dll ) {
        PRINTL_STR( "Game64.dll loaded");

        /* Create a coherent function call for this */
        gameAPI = (GameAPI)(GetProcAddress( dll, "GetGameAPI"));
        if( gameAPI) {
            PRINTL_STR( "GetGameAPI found");
        }
    }
    g_gameExport = (*gameAPI)( &g_gameImport);

    return g_gameExport;
}

int main(int argc, char *argv[])
{
    printf("%s", WELCOME_MSG.c_str());

    /** initialize subsystems */
    kMemory memory( memoryByteSize);

    /** prepare an export for game.dll */
    g_gameImport.version = 1;
    g_gameImport.memorySystem = &memory;

    win_LoadGame();

    kGame *game = g_gameExport->game;
    /** prepare game */
    game->Initialize();

    /*
     * main loop
     */
    game->Loop();

    /** destroy things */
    game->Terminate();

    return EXIT_SUCCESS;
}

