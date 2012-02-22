#include "stdafx.h"
#include "DEMO_APP.h"
//************************************************************
//************ WINDOWS RELATED *******************************
//************************************************************
int WINAPI wWinMain(HINSTANCE hInstance,	// handle to application
				   HINSTANCE hPrevInstance,	// handle to previous app
				   LPTSTR lpCmdLine,		// command line string
				   int nCmdShow );			// show window value			   
LRESULT CALLBACK WndProc(HWND hWnd,				// handle to window
						 UINT message,			// incoming message
						 WPARAM wparam,			// message info
						 LPARAM lparam );		// message info
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int )
{
	//************ INTIALIZATION ******************/
	srand(unsigned int(time(0)));	//randomize!
	DEMO_APP myApp(hInstance,(WNDPROC)WndProc);	// store application handle
	//************ MAIN LOOP *************************/
    // use to catch windows messages
    MSG msg; ZeroMemory( &msg, sizeof( msg ) );
    while ( msg.message != WM_QUIT && myApp.Run() )
    {	
		// get any system messages
        if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        { 
            TranslateMessage( &msg );
            DispatchMessage( &msg ); 
        }
    }
	//************ SHUTDOWN *************************/
    return 0; // done, myApp destructor will run
}
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    // attempt to handle
	if(GetAsyncKeyState(VK_ESCAPE))
		message = WM_DESTROY;

    switch ( message )
    {
        case ( WM_DESTROY ): { PostQuitMessage( 0 ); }
        break;
    }
    // pass to default handler
    return DefWindowProc( hWnd, message, wParam, lParam );
}