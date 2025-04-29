
#include <windows.h>
#include <stdio.h>

static bool Running;



//device independent bitmap
static void ResizeDIBSection(int,int){
BITMAPINFO BitmapInfo;
BitmapInfo = {};
void *BitmapMemory;
HBITMAP BitmapHandle=CreateDIBSection(DeviceContext,&BitmapInfo,DIB_RGB_COLORS,&BitmapMemory, 0, 0);
    
}

static  void UpdateWindows(HDC DeviceContext,int X, int Y, int Width, int Height ){
StretchDIBits(DeviceContext
    ,X,Y,Width,Height
    ,X,Y,Width,Height,void,const,
DIB_RGB_COLORS,
SRCCOPY);

}

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
        RECT ClientRect;
        GetClientRect(Window, &ClientRect );
        int Width = ClientRect.right - ClientRect.left;
        int Height = ClientRect.bottom - ClientRect.left;
        ResizeDIBSection(Width,Height);

       
    }break;
    case WM_CLOSE:{
        PostQuitMessage(0);// is the way the app stops 
        DestroyWindow(Window);
    }break;
    case WM_PAINT:
    {
       PAINTSTRUCT Paint;
       HDC DeviceContext = BeginPaint(Window,&Paint);
       int X =Paint.rcPaint.left;
       int Y =Paint.rcPaint.top;
       int Width = Paint.rcPaint.right - Paint.rcPaint.left;
       int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
        
       static DWORD Operation = WHITENESS;

       UpdateWindows(DeviceContext,X,Y,Width,Height);

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
        //TODO (Caien): Logging
    }

    return (0);
}
