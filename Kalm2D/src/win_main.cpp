
#include "win_main.h"

#include <wingdi.h>


/* The title bar text */
const char *title = "Kalm2D";
/* The main window class name */
const char *windowClass = "Kalm2DWindowClass";

static b32 g_running = true;

i32 windowWidth = 800;
i32 windowHeight = 400;


int main(int argc, char *argv[])
{
    if (!glfwInit()) {
        printf("%s\n", "Failed to initialize glfw");
    }

    glfwSetErrorCallback(ErrorCallback);
#ifdef GLAD_DEBUG
    printf("%s\n", "GLAD_DEBUG defined at compile time");
    // before every opengl call call pre_gl_call
    glad_set_pre_callback(pre_gl_call);
    // post callback checks for glGetError by default
    // don't use the callback for glClear
    // (glClear could be replaced with your own function)
    glad_debug_glClear = glad_glClear;
#endif
    // gladLoadGLLoader(&glutGetProcAddress);


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_Version_Major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_Version_Minor);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    /* Windowed Fullscreen */
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height , title, monitor, NULL);
    if (!window)
    {
        printf("%s\n", "Failed to create Window");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        printf("%s\n", "Failed to initialize OpenGL context");
        return -1;
    }
    //gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);
    if (GLVersion.major < 2) {
        printf("Your system doesn't support OpenGL >= 2!\n");
        return -1;
    }

    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
           glGetString(GL_SHADING_LANGUAGE_VERSION));

    glfwSetKeyCallback( window, KeyCallback);

    i32 width, height;
    glfwGetFramebufferSize( window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback( window, ResizeCallback);

    /* VSYNC */
    glfwSwapInterval(1);

    /*
     * TODO(Kasper): OpenGL error checks
     */

    r64 lastTime = 0;
    /*
     * main loop
     */
    while (!glfwWindowShouldClose(window)) {
        r64 time = glfwGetTime();

        glfwSwapBuffers(window);
        glfwPollEvents();

        lastTime = time;
    }

    return EXIT_SUCCESS;
}

static void KeyCallback(GLFWwindow* window, const i32 key, const i32 scancode, const i32 action, const i32 mods) {
    /* Close window */
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void ErrorCallback( i32 error, const char* description) {
    fprintf(stderr, "Error: %d: %s\n", error, description);
}

void ResizeCallback( GLFWwindow* window, const i32 numer, const i32 denom) {
    i32 width, height;
    glfwGetFramebufferSize( window, &width, &height);
    glfwSetWindowSize( window, width*numer, height*denom);
}
