
#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK Wndproc(
    HWND Window,
    UINT Message,
    WPARAM WParam,
    LPARAM LParam)
{
    LRESULT Result = 0;

    switch (Message)
    {
    case WM_SIZE:
    {
    }
    case WM_PAINT:
    {
       PAINTSTRUCT Paint;
       HDC DeviceContext = BeginPaint(Window,&Paint);
       int X =Paint.rcPaint.left;
       int Y =Paint.rcPaint.top;
       int Width = Paint.rcPaint.right - Paint.rcPaint.left;
       int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
       static DWORD Operation = WHITENESS;
       PatBlt(DeviceContext,X,Y,Width,Height,Operation);

       if(Operation == WHITENESS){
        Operation = BLACKNESS;
       }
       else{
        Operation = WHITENESS;
       }
       EndPaint(Window,&Paint);
    }
    break;
    default:
    {
        Result = DefWindowProc(Window, Message, WParam, LParam);
    }
    break;
    }

    return (Result);
}

int WINAPI WinMain(
    HINSTANCE Instance,
    HINSTANCE PrevInstance,
    PSTR CmdLine,
    int CmdShow)
{
    WNDCLASS WindowClass = {0};
    WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = Wndproc;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = "HereWeGoAgain";

    // Registering the window
    if (RegisterClass(&WindowClass))
    {
        HWND WindowHandler = CreateWindowExA(
            0,
            WindowClass.lpszClassName,
            "Fist WIndow",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            Instance,
            0);

        if (WindowHandler)
        {
            MSG Message;

            for (;;)
            {
                BOOL MessageResult = GetMessageA(&Message, 0, 0, 0);
                if (MessageResult > 0)
                {
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }
                else
                {
                    printf("Couldnt generate a Message result");

                    break;
                }
            }
        }
        else
        {
            // Todo(Caien):Logging

            printf("Couldnt generate a window handler");
        }
    }
    else
    {
    }

    return (0);
}
