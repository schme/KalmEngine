

#include "kalm2d.h"

b32 InitializeGraphics();


static GLFWwindow *window = nullptr;

b32 InitializeGraphics() {
    if (!glfwInit()) {
        printf("%s\n", "Failed to initialize glfw");
        return false;
    }

    glfwSetErrorCallback(ErrorCallback);
    return true;
}


b32 InitializeGraphicsContext() {

    if( !InitializeGraphics() ) {
    }

#ifdef GLAD_DEBUG
    printf("%s\n", "GLAD_DEBUG defined at compile time");
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
    window = glfwCreateWindow(mode->width, mode->height , title, monitor, nullptr);
    if (!window)
    {
        printf("%s\n", "Failed to create Window");
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        printf("%s\n", "Failed to initialize OpenGL context");
        return false;
    }
    printf("%s\n", "Got OpenGL context");
    //gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);
    if (GLVersion.major < 2) {
        printf("Your system doesn't support OpenGL >= 2!\n");
        return false;
    }

    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
           glGetString(GL_SHADING_LANGUAGE_VERSION));

    i32 width, height;
    glfwGetFramebufferSize( window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback( window, ResizeCallback);
    glfwSetKeyCallback( window, KeyCallback);


    /* VSYNC */
    glfwSwapInterval(1);

    /*
     * TODO(Kasper): OpenGL error checks
     */

    return true;
}


i32 KalmLoop() {

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


void KalmTerminate() {
    glfwTerminate();
}

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
