/**
 * Kalm2D
 *
 * Copyright (C) 2018 Kasper Sauramo - All Rights Reserved
 * Created: 27/04/2018 
 */

#include "Kalm2D.h"

static void KeyCallback( GLFWwindow* window, const i32 key, const i32 scancode, const i32 action, const i32 mods);
static void ErrorCallback( const i32 error, const char* description);
static void ResizeCallback( GLFWwindow* window, const i32 numer, const i32 denom);


//BOOL WINAPI DllMain( HINSTANCE hinstDLL,
        //DWORD fdwReason,
        //LPVOID lpReserved ) {
    //return true;
//}


b32 InitializeGlfw() {
    if (!glfwInit()) {
        PRINT_STR("Failed to initialize glfw");
        return false;
    }

    glfwSetErrorCallback(ErrorCallback);
    return true;
}

b32 InitializePlatformSystem() {

#ifdef GLAD_DEBUG
    PRINT_STR("GLAD_DEBUG defined at compile time");
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
    Kalm2D::window = glfwCreateWindow(mode->width, mode->height , title, monitor, nullptr);
    if (!Kalm2D::window)
    {
        PRINT_STR("Failed to create Window");
        return false;
    }

    glfwMakeContextCurrent(Kalm2D::window);

    if (!gladLoadGL()) {
        PRINT_STR("Failed to initialize OpenGL context");
        return false;
    }
    PRINT_STR( "Got OpenGL context");
    //gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);
    if (GLVersion.major < 2) {
        printf("Your system doesn't support OpenGL >= 2!\n");
        return false;
    }

    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
           glGetString(GL_SHADING_LANGUAGE_VERSION));

    i32 width, height;
    glfwGetFramebufferSize( Kalm2D::window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback( Kalm2D::window, ResizeCallback);
    glfwSetKeyCallback( Kalm2D::window, KeyCallback);


    /* VSYNC */
    glfwSwapInterval(1);

    /*
     * TODO(Kasper): OpenGL error checks
     */

    return true;
}


b32 InitializeMemorySystem() {
    return true;
}


/**
 * Kalm2D
 */

GLFWwindow *Kalm2D::window = nullptr;
gameImport_t * Kalm2D::system = nullptr;

b32 Kalm2D::Initialize( gameImport_t *import ) {

    this->system = import;

    if( !InitializeGlfw() ) { return false; }
    if( !InitializePlatformSystem() ) { return false; }
    if( !InitializeMemorySystem() ) { return false; }

    return false;
}


/**
 * Main Loop
 */
i32 Kalm2D::Loop() {

    while(!glfwWindowShouldClose(window)) {

        static r64 lastTime = 0;
        static r64 time = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
        lastTime = time;
    }

    return true;
}


void Kalm2D::Terminate() {
    glfwTerminate();
}

/**
 * end of Kalm2D
 */


engineAPI_t GetAPI() {
    static Kalm2D engine;
    engineAPI_t newApi;
    newApi.engine = &engine;
    return newApi;
}


/**
 * Callbacks
 */

void KeyCallback(GLFWwindow* wnd, const i32 key, const i32 scancode, const i32 action, const i32 mods) {
    /* Close window */
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(wnd, GLFW_TRUE);
}

void ErrorCallback( i32 error, const char* description) {
    fprintf(stderr, "Error: %d: %s\n", error, description);
}

void ResizeCallback( GLFWwindow* wnd, const i32 numer, const i32 denom) {
    i32 width, height;
    glfwGetFramebufferSize( wnd, &width, &height);
    glfwSetWindowSize( wnd, width*numer, height*denom);
}
