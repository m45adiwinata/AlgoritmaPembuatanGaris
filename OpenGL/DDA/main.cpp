/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>


/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);


/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "OpenGL Sample", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 666, 666,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);

            glPushMatrix ();
            glRotatef (theta, 0.0f, 0.0f, 1.0f);
            float x1=0.3,y1=0.2,x2=0.8,y2=0.7;
            glPointSize(4.0);
            glBegin (GL_POINTS);
            glColor3f(0.0,0.5,0.8); glVertex2f(0.256,0.442);
            glColor3f(0.0,0.5,0.8); glVertex2f(0.625,0.772);
            glColor3f(0.0,0.5,0.8); glVertex2f(0.333,0.666);
            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (x1, y1);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(x2,y2);
            float x_inc,y_inc,s,r;
            x_inc=x2-x1;
            if(x_inc<0){
            	x_inc*=(-1);
			}
            y_inc=y2-y1;
            if(y_inc<0){
            	y_inc*=(-1);
			}
            glColor3f(1.0f, 1.0f, 1.0f); glVertex2f(0.0f,0.0f);
            
            if(x_inc>=y_inc){
            	s=x_inc;
            	r=y_inc/(s*1000);
            	s/=(s*1000);
			}
			else{
				r=y_inc;
				s=x_inc/(r*1000);
				r/=(r*1000);
			}
			
			if(x1<x2){
				if(y1<y2){
					while(x1<x2){
						x1+=s; y1+=r;
						glColor3f(1.0f,0.0f,0.5f); glVertex2f(x1,y1);
					}
					
				}
				else{
					while(x1<x2){
						x1+=s; y1-=r;
						glColor3f(1.0f,0.0f,0.5f); glVertex2f(x1,y1);
					}
				}
			}
			else{
				if(y1<y2){
					while(x1>x2){
						x1-=s; y1+=r;
						glColor3f(1.0f,0.0f,0.5f); glVertex2f(x1,y1);
					}
					
				}
				else{
					while(x1>x2){
						x1-=s; y1-=r;
						glColor3f(1.0f,0.0f,0.5f); glVertex2f(x1,y1);
					}
				}
			}
			x1=0.1; x2=0.8; y1=0.7;y2=0.33;
			x_inc=x2-x1;
			if(x_inc<0){
				x_inc*=(-1);
			}
			y_inc=y2-y1;
			if(y_inc<0){
				y_inc*=(-1);
			}
			if(x_inc>y_inc){
				s=x_inc;
				r=y_inc/(s*1000);
				s/=(s*1000);
			}
			else{
				r=y_inc;
				s=x_inc/(r*1000);
				r/=(r*1000);
			}
			if(x1<x2){
				if(y1<y2){
					while(x1<x2){
						glColor3f(1.0,1.0,0.0); glVertex2f(x1,y1);
						x1+=s; y1+=r;
					}
				}
				else{
					while(x1<x2){
						glColor3f(1.0,1.0,0.0); glVertex2f(x1,y1);
						x1+=s; y1-=r;
					}
				}
			}
			else{
				if(y1<y2){
					while(x1<x2){
						glColor3f(1.0,1.0,0.0); glVertex2f(x1,y1);
						x1-=s; y1+=r;
					}
				}
				else{
					while(x1<x2){
						glColor3f(1.0,1.0,0.0); glVertex2f(x1,y1);
						x1-=s; y1-=r;
					}
				}
			}
            glEnd ();
            glPopMatrix ();

            SwapBuffers (hDC);

            
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
