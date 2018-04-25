
#include "win_main.h"

#include <wingdi.h>

// Global Variables:
HINSTANCE hInst;                                // current instance
static HDC DeviceContext;
static HGLRC RenderingContext;
static WINDOWPLACEMENT windowPlacement = { sizeof( WINDOWPLACEMENT)};

/* The title bar text */
const char *title = "Kalm2D";
/* The main window class name */
const char *windowClass = "Kalm2DWindowClass";

static u64 perfCountFrequency;
static u64 frame;

static b32 g_running = true;

i32 windowWidth = 800;
i32 windowHeight = 400;

void
Win_FreeMemory( void *Memory) {
    if( Memory) {
        VirtualFree( Memory, 0, MEM_RELEASE);
    }
}


Win_WindowDimensions_t Win_GetWindowDimensions( HWND Window) {
    Win_WindowDimensions_t result;

    RECT ClientRect;
    GetClientRect( Window, &ClientRect);
    result.width = ClientRect.right - ClientRect.left;
    result.height = ClientRect.bottom - ClientRect.top;

    return result;
}

void
Win_ToggleFullscreen( HWND hwnd)
{
    DWORD dwStyle = GetWindowLong( hwnd, GWL_STYLE);
    if( dwStyle & WS_OVERLAPPEDWINDOW) {
        MONITORINFO mi = { sizeof(mi) };
        if( GetWindowPlacement( hwnd, &windowPlacement) &&
            GetMonitorInfo( MonitorFromWindow( hwnd,
                    MONITOR_DEFAULTTOPRIMARY), &mi))
            {
            SetWindowLong( hwnd, GWL_STYLE,
                    dwStyle & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos( hwnd, HWND_TOP,
                   mi.rcMonitor.left, mi.rcMonitor.top,
                   mi.rcMonitor.right - mi.rcMonitor.left,
                   mi.rcMonitor.bottom - mi.rcMonitor.top,
                   SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
            }
     } else {
       SetWindowLong(hwnd, GWL_STYLE,
                     dwStyle | WS_OVERLAPPEDWINDOW);
       SetWindowPlacement(hwnd, &windowPlacement);
       SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
                    SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                    SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
     }
}


i32
Win_CreateGLContext()
{
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,                              /* version */
        PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,                             /* colordepth of the framebuffer */
        0, 0, 0, 0, 0, 0,               /* color bits (ignored) */
        0,                              /* no alpha buffer */
        0,                              /* alpha bits (ignored) */
        0,                              /* no accumulation buffer */
        0, 0, 0, 0,                     /* accum bits (ignored) */
        24,                             /* depth buffer */
        8,                              /* no stencil buffer */
        0,                              /* no auxiliary buffers */
        0,                              /* main layer */
        0,                              /* reserved */
        0, 0, 0,                        /* no layer, visible, damage masks */
    };

    i32 pixelFormat = ChoosePixelFormat(DeviceContext, &pfd);
    if( !SetPixelFormat(DeviceContext, pixelFormat, &pfd)) {
        OutputDebugStringA( "FAILED: Setting pixelformat\n");
        return 0;
    }
    HGLRC tempContext = wglCreateContext( DeviceContext);
    wglMakeCurrent( DeviceContext, tempContext);
    if( glewInit() != GLEW_OK) {
        OutputDebugStringA( "FAILED: glewInit()\n");
        return 0;
    }
    /* OpenGL version to load */
    i32 attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, GL_Version_Major,
            WGL_CONTEXT_MINOR_VERSION_ARB, GL_Version_Minor,
            WGL_CONTEXT_FLAGS_ARB, 0,
            0
    };
    if( wglewIsSupported( "WGL_ARB_create_context") == 1)
    {
        RenderingContext = wglCreateContextAttribsARB( DeviceContext, 0, attribs);
        wglDeleteContext( tempContext);
        wglMakeCurrent( DeviceContext, RenderingContext);
        OutputDebugStringA( "SUCCESS: GL 3.x context received\n");
    } else {
        RenderingContext = tempContext;
        OutputDebugStringA( "FAILED: GL 3.x context. Using GL 2.1 or earlier\n");
    }

    if( !RenderingContext) {
        OutputDebugStringA( "FAILED: Getting RenderingContext\n");
        return 0;
    }
    i32 OpenGLVersion[2];
    glGetIntegerv( GL_MAJOR_VERSION, &OpenGLVersion[0]);
    glGetIntegerv( GL_MINOR_VERSION, &OpenGLVersion[1]);

    // OpenGL Extensions

    /* vsync */
    if (wglewIsSupported( "WGL_EXT_swap_control")) {
        wglSwapIntervalEXT(1);
    }

    return 1;
}


inline LARGE_INTEGER
Win_GetWallClock() {
    LARGE_INTEGER Result;
    QueryPerformanceCounter( &Result);
    return Result;
}


inline r32
Win_GetSecondsElapsed( LARGE_INTEGER Start, LARGE_INTEGER End)
{
    r32 Result = ((r32)(End.QuadPart - Start.QuadPart) /
                    (r32)perfCountFrequency);
    return Result;
}


void
Win_HandleMessages( KalmInput_t &input) {

    MSG Message;
    while( PeekMessage( &Message, 0,0,0, PM_REMOVE)) {

        switch( Message.message ) {

            case WM_QUIT: {
                              g_running = false;
            } break;

            case WM_SYSKEYUP:
            case WM_KEYUP:
            case WM_SYSKEYDOWN:
            case WM_KEYDOWN: {

                u32 VKCode = (u32)Message.wParam;
                u32 wasDown = ((Message.lParam & (1 << 30)) != 0);
                u32 isDown = ((Message.lParam & (1 << 31)) == 0);
                if( wasDown != isDown) {

                    switch (VKCode) {
                        case 'W': {
                                      input.KEY_W = 1;
                        } break;
                        case 'A': {
                                      input.KEY_A = 1;
                        } break;
                        case 'S': {
                                      input.KEY_S = 1;
                        } break;
                        case 'D': {
                                      input.KEY_D = 1;
                        } break;
                        case 'Q': {
                                      input.KEY_Q = 1;
                        } break;
                        case 'E': {
                                      input.KEY_E = 1;
                        } break;
                        case VK_UP: {
                                      input.KEY_UP = 1;
                        } break;
                        case VK_LEFT: {
                                      input.KEY_LEFT = 1;
                        } break;
                        case VK_DOWN: {
                                      input.KEY_DOWN = 1;
                        } break;
                        case VK_RIGHT: {
                                      input.KEY_RIGHT = 1;
                        } break;
                        case VK_SPACE: {
                                      input.KEY_SPACE = 1;
                        } break;
                        case VK_ESCAPE: {
                                      input.KEY_ESCAPE = 1;
                        } break;
                    } // VKCode
                } //wasDown != isDown

                if( isDown) {
                    u32 AltKeyWasDown = (Message.lParam & (1 << 29));
                    if(( VKCode == VK_F4) && AltKeyWasDown) {
                        g_running = false;
                    }
                    if(( VKCode == VK_RETURN) && AltKeyWasDown) {
                        if( Message.hwnd) {
                            Win_ToggleFullscreen( Message.hwnd);
                        }
                    }
                }

            } break;

        default: {
            TranslateMessage( &Message);
            DispatchMessageA( &Message);
        } break;

        } // switch (Message)
    } // while( PeekMessage())
}


LRESULT CALLBACK
Win_WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    switch (message) {

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    } break;

    case WM_CREATE: {
        DeviceContext = GetDC( hWnd);
        if( Win_CreateGLContext()) {
            // TODO: Start using OpenGL context
        }
    } break;

    case WM_CLOSE: {
        // TODO: Stop using OpenGL
        g_running = false;
        wglMakeCurrent( nullptr, nullptr);
        wglDeleteContext( RenderingContext);
        ReleaseDC( hWnd, DeviceContext);
    } break;
    case WM_DESTROY: {
        g_running = false;
        PostQuitMessage(0);
    } break;

    case WM_SIZE: {
        Win_WindowDimensions_t dim = Win_GetWindowDimensions( hWnd);
        //resizeCallback( dim.width, dim.height);
    } break;
    //case WM_SETCURSOR: {
    //} break;

    default:
        result = DefWindowProc(hWnd, message, wParam, lParam);
    }
    return result;
}

i32 WinMain(    HINSTANCE hInstance,
                HINSTANCE hPrevInstance,
                LPTSTR    lpCmdLine,
                i32       nCmdShow)
{

    // Timing
    LARGE_INTEGER PerfCountFrequencyResult;
    QueryPerformanceFrequency( &PerfCountFrequencyResult);
    perfCountFrequency = PerfCountFrequencyResult.QuadPart;

    unsigned sleepIsGranular = (timeBeginPeriod( 1) == TIMERR_NOERROR);

#define GameUpdateHz 60
    r32 targetSecondsPerFrame = 1.0f / (r32)GameUpdateHz;

    // WindowClass
    WNDCLASSA WindowClass = {};
    WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    WindowClass.lpfnWndProc = Win_WndProc;
    WindowClass.hInstance = hInstance;
    WindowClass.hCursor = LoadCursor(0, IDC_CROSS);
    //WindowClass.hIcon;
    WindowClass.lpszClassName = windowClass;

    if( !RegisterClassA( &WindowClass)) {
        OutputDebugStringA( "FAILED: RegisterWindowClass\n");
    }

    HWND hWnd =
            CreateWindowExA(
                    0,
                    WindowClass.lpszClassName,
                    title,
                    WS_VISIBLE | WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, CW_USEDEFAULT,
                    windowWidth, windowHeight,
                    NULL,   // PrevInstance
                    NULL,
                    hInstance,
                    NULL );
    if( !hWnd) {
        OutputDebugStringA( "FAILED: Create Window\n");
        return 0;
    }

    SetWindowText( hWnd, title);

    // Timing
    LARGE_INTEGER LastCounter = Win_GetWallClock();
    u64 LastCycleCount = __rdtsc();
    r64 msPerFrame = 0.0;

    Win_WindowDimensions_t dimensions = Win_GetWindowDimensions( hWnd);
    //resizeCallback( dimensions.width, dimensions.height);

    /**
     * MainLoop
     */
    while( g_running ) {

        KalmInput_t input = {};
        Win_HandleMessages( input );
        input.frame = frame;
        input.deltaTime = msPerFrame;

        KalmUpdate( input );

        // Timing
        LARGE_INTEGER workCounter = Win_GetWallClock();
        r32 workSecondElapsed = Win_GetSecondsElapsed( LastCounter, workCounter);
        r32 secondsElapsedForFrame = workSecondElapsed;


        if( secondsElapsedForFrame < targetSecondsPerFrame )
        {
            if( sleepIsGranular)
            {
                DWORD SleepMS = (DWORD)(1000.0f * (targetSecondsPerFrame -
                                                    secondsElapsedForFrame));
            }
            r32 testSecondsElapsedForFrame = Win_GetSecondsElapsed( LastCounter, Win_GetWallClock());
        } else {
            OutputDebugStringA( "MISSED FRAME\n");
        }


        LARGE_INTEGER EndCounter = Win_GetWallClock();
        msPerFrame = 1000.0f*Win_GetSecondsElapsed( LastCounter, EndCounter);
        LastCounter = EndCounter;

        SwapBuffers( DeviceContext);

        u64 endCycleCount = __rdtsc();
        u64 cyclesElapsed = endCycleCount - LastCycleCount;
        LastCycleCount = endCycleCount;

        i64 counterElapsed = EndCounter.QuadPart - LastCounter.QuadPart;

        ++frame;

        r64 FPS = (r64)perfCountFrequency / (r64)counterElapsed;
        r64 MCPF = ((r64)cyclesElapsed / (1000.0f * 1000.0f));

        char timeStrBuffer[256];

        _snprintf_s( timeStrBuffer, sizeof( timeStrBuffer), "%.02fms/f, %.02fmc/f, frame %llu \n", msPerFrame, MCPF, frame);

        OutputDebugStringA( timeStrBuffer);
        //if( frame % 20 == 0) {
            //SetWindowText( Window, timeStrBuffer);
        //}

    }

    return EXIT_SUCCESS;
}


