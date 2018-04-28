
#include <windows.h>
#include "win_Kalm2D.h"

#include "Systems.h"
#include "glad.c"
#include "CommonSystem.cpp"
#include "Memory.cpp"
#include "Filesystem.cpp"
#include "Render.cpp"

const u8 GL_Version_Major = 3;
const u8 GL_Version_Minor = 1;

static const u32 memoryByteSize = 32*1024;

GLFWwindow* g_window = nullptr;

gameImport_t g_gameImport = {};
gameExport_t * g_gameExport = nullptr;

/** GetGameAPI function definition */
typedef gameExport_t* (*GameAPI)( gameImport_t *);

static void ErrorCallback( const i32 error, const char* description);

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


b32 InitializeGlfw() {

    if (!glfwInit()) {
        PRINTL_STR("Failed to initialize glfw");
        return false;
    }

    glfwSetErrorCallback(ErrorCallback);


#ifdef GLAD_DEBUG
    // before every opengl call call pre_gl_call
    glad_set_pre_callback(pre_gl_call);
    // post callback checks for glGetError by default
    // don't use the callback for glClear
    // (glClear could be replaced with your own function)
    glad_debug_glClear = glad_glClear;
#endif

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_Version_Major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_Version_Minor);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    /* Windowed Fullscreen */

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    /** Passing in a monitor gives fullscreen */
    //Kalm2D::window = glfwCreateWindow(mode->width, mode->height, title, monitor, nullptr);
    g_window = glfwCreateWindow( (u32)(mode->width*0.6f), (u32)(mode->height*0.6f), title, nullptr, nullptr);
    if (!g_window)
    {
        PRINTL_STR("Failed to create Window");
        return false;
    }

    glfwMakeContextCurrent(g_window);

    if (!gladLoadGL()) {
        PRINTL_STR("Failed to initialize OpenGL context");
        return false;
    }
    PRINTL_STR( "Got OpenGL context");
    //gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    if (GLVersion.major < 2) {
        printf("Your system doesn't support OpenGL >= 2!\n");
        return false;
    }

    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
           glGetString(GL_SHADING_LANGUAGE_VERSION));


    /* VSYNC */
    glfwSwapInterval(1);

    /*
     * TODO(Kasper): OpenGL error checks
     */

    return true;

}

int main(int argc, char *argv[])
{
    if( argc > 1) {
        printf("%s: %s?! What do you mean!\n", argv[0], argv[1]);
    }

    printf("%s", WELCOME_MSG.c_str());

    if( !InitializeGlfw() ) {
        PRINTL_STR( "Failed to initialize GLFW. Exiting.");
        return 0;
    }

    /** initialize subsystems */
    kCommonSystem commonSystem;
    kMemory memory( memoryByteSize);
    kFilesystem fileSystem;
    kRender render;

    commonSystem.SetWindow( g_window );
    commonSystem.Initialize();
    /** Init needs the window */
    render.SetWindow( g_window );
    render.Initialize();

    /** prepare an export for game.dll */
    g_gameImport.version = 1;

    g_gameImport.commonSystem = &commonSystem;
    g_gameImport.memorySystem = &memory;
    g_gameImport.fileSystem = &fileSystem;
    g_gameImport.renderSystem = &render;

    /** load game API */
    win_LoadGame();

    kGame *game = g_gameExport->game;
    /** prepare game */
    game->Initialize();

    /*
     * GAME LOOP
     */
    game->Loop();

    /** destroy things */
    glfwTerminate();
    game->Terminate();

    return EXIT_SUCCESS;
}

/**
 * Callbacks
 */

void ErrorCallback( i32 error, const char* description) {
    fprintf(stderr, "Error: %d: %s\n", error, description);
}

