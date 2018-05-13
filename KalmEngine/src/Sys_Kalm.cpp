
#include "stdafx.h"
#include "Sys_Kalm.h"
#include "KalmTypes.h"

#include "Systems.h"
#include "../include/glad/glad.h"

#include "Sys_Common.cpp"
#include "Sys_Memory.cpp"
#include "Sys_Filesystem.cpp"
#include "Sys_Render.cpp"
#include "Sys_Assets.cpp"
#include "Sys_Config.cpp"

//#undef GLAD_DEBUG


// GLAD_DEBUG is only defined if the c-debug generator was used
#ifdef GLAD_DEBUG
// logs every gl call to the console
void pre_gl_call(const char *name, void *funcptr, int len_args, ...) {
    printf("Calling: %s (%d arguments)\n", name, len_args);
}

void pre_gl_clear(u32 thing) {
    //printf("glClear() thing: %u\n", thing);
    // call glClear here without calling glClear (infinite recursion)
}

void post_gl_call( const char *name, void *funcptr, int len_args, ...) {
    GLenum error_code;
    error_code = glad_glGetError();

    if (error_code != GL_NO_ERROR) {
        fprintf(stderr, "ERROR %d in %s\n", error_code, name);
    }
}
#endif


const u8 GL_Version_Major = 4;
const u8 GL_Version_Minor = 3;

static const u32 memoryByteSize = Megabytes( 64 );

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
        "kasper@kaspersauramo.me\n\n"
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
    //TODO(Kasper): Move to Common?
    glfwSetErrorCallback(ErrorCallback);

#ifdef GLAD_DEBUG
    // before every opengl call call pre_gl_call
    //glad_set_pre_callback(pre_gl_call);
    // post callback checks for glGetError by default
    glad_set_post_callback(post_gl_call);
    // don't use the callback for glClear
    // (glClear could be replaced with your own function)
    //glad_debug_glClear = pre_gl_clear;
#endif

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_Version_Major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_Version_Minor);
    //TODO(Kasper): What do Opengl profiles even do?
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    g_window = glfwCreateWindow( frameBufferWidth, frameBufferHeight, title, nullptr, nullptr);
    if (!g_window)
    {
        PRINTL_STR("Failed to create Window");
        return false;
    }

    glfwMakeContextCurrent(g_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        PRINTL_STR("Failed to initialize OpenGL context");
        return false;
    }
    PRINTL_STR( "Got OpenGL context");

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
    /* memory */
    kMemory memory( memoryByteSize);
    g_Memory = &memory;
    /* common */
    kCommonSystem commonSystem;
    g_Common = &commonSystem;
    /* filesystem */
    kFilesystem fileSystem;
    g_Filesystem = &fileSystem;
    /* renderer */
    kRender render;
    g_Render = &render;
    /* assets */
    kAssets assetSystem;
    g_Assets = &assetSystem;
    /* config */
    kConfig configSystem;
    g_Config = &configSystem;

    /** prepare an export for game.dll */
    g_gameImport.version = 1;

    g_gameImport.commonSystem = &commonSystem;
    g_gameImport.memorySystem = &memory;
    g_gameImport.fileSystem = &fileSystem;
    g_gameImport.renderSystem = &render;
    g_gameImport.assetSystem = &assetSystem;
    g_gameImport.configSystem = &configSystem;

    /** load game API */
    win_LoadGame();
    kGame *game = g_gameExport->game;

    /** Init needs the window */
    commonSystem.SetWindow( g_window );
    commonSystem.Initialize();
    render.SetWindow( g_window );
    render.Initialize();

    configSystem.Initialize();

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

