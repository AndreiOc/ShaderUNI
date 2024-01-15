#include"Headers/DirectX.h"
#include"Headers/Paddle.h"
#include"Headers/Ball.h"
#include"Headers/Block.h"

// global declarations
IDXGISwapChain* swapchain;              // the pointer to the swap chain interface
ID3D11Device* dev;                      // the pointer to our Direct3D device interface
ID3D11DeviceContext* devcon;            // the pointer to our Direct3D device context
ID3D11RenderTargetView* backbuffer;     // the pointer to our back buffer
ID3D11InputLayout* pLayout;             // the pointer to the input layout
ID3D11VertexShader* pVS;                // the pointer to the vertex shader
ID3D11PixelShader* pPS;                 // the pointer to the pixel shader

float SHIFTINGX = 0.00f;
float SHIFTINGBALLX = 0.00f;
float SHIFTINGBALLY = 0.00f;

float flagX= 1.0f;
float flagY = 1.0f;

float RED;

// function prototypes
void InitD3D(HWND hWnd);    // sets up and initializes Direct3D
void RenderFrame(Paddle paddle,Ball ball,Block blocks[]);     // renders a single frame
void CleanD3D(Paddle paddle);        // closes Direct3D and releases memory
void InitGraphics(void);    // creates the shape to render
void InitPipeline(void);    // loads and prepares the shaders

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"WindowClass";

    RegisterClassEx(&wc);

    RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd = CreateWindowEx(NULL,
        L"WindowClass",
        L"Our First Direct3D Program",
        WS_OVERLAPPEDWINDOW,
        300,
        100,
        wr.right - wr.left,
        wr.bottom - wr.top,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hWnd, nCmdShow);
    Paddle paddle;
    Ball ball;
    ///array of block how block the ball, now a neeed to the define the move ball
    Block *blocks = new Block[BLOCKX * BLOCKY];
    int count = 0;
    for (float i =  -6.0f; i < 7; i++)
    {
        for (float j = 0; j < 5; j++)
        {
            blocks[count] = Block(i/7.0f,j/5.0f);
            count++;
        }
    }


    // set up and initialize Direct3D
    InitD3D(hWnd);

    MSG msg;
    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;

        }
        SHIFTINGBALLX += 0.0005f * flagX;
        SHIFTINGBALLY += 0.0005f * flagY;

        RenderFrame(paddle,ball,blocks);
    }

    // clean up DirectX and COM
    CleanD3D(paddle);

    return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        break;
        case WM_KEYDOWN:
        {
            if (wParam == VK_LEFT)
            {
                if (SHIFTINGX >= -0.8f)
                   SHIFTINGX -= 0.02f;
            }
            if (wParam == VK_RIGHT)
            {
                if (SHIFTINGX <= 0.8f)
                    SHIFTINGX += 0.02f;
            }
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void InitD3D(HWND hWnd)
{
    // create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                   // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
    scd.BufferDesc.Width = SCREEN_WIDTH;                   // set the back buffer width
    scd.BufferDesc.Height = SCREEN_HEIGHT;                 // set the back buffer height
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
    scd.OutputWindow = hWnd;                               // the window to be used
    scd.SampleDesc.Count = 4;                              // how many multisamples
    scd.Windowed = TRUE;                                   // windowed/full-screen mode
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &scd,
        &swapchain,
        &dev,
        NULL,
        &devcon);


    // get the address of the back buffer
    ID3D11Texture2D* pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();

    // set the render target as the back buffer
    devcon->OMSetRenderTargets(1, &backbuffer, NULL);


    // Set the viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = SCREEN_WIDTH;
    viewport.Height = SCREEN_HEIGHT;

    devcon->RSSetViewports(1, &viewport);

    InitPipeline();
    InitGraphics();
}


// this is the function used to render a single frame
void RenderFrame(Paddle paddle, Ball ball, Block blocks[])
{
    // clear the back buffer to a deep blue
    devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

    if (SHIFTINGBALLX + ball.GetX() > 1.0f)
        flagX = flagX * -1;
    if (SHIFTINGBALLX + ball.GetX() < - 1.0f)
        flagX = flagX * -1;


    if (SHIFTINGBALLY + ball.GetY() > 1.0f)
        flagY = flagY * -1;
    if (SHIFTINGBALLY + ball.GetY() < -1.0f)
        flagY = flagY * -1;


    ball.Update(dev, devcon, SHIFTINGBALLX, SHIFTINGBALLY);

    paddle.Update(SHIFTINGX,dev,devcon);
    
    int count = 0;
    for (int i = 0; i < BLOCKX; i++)
    {
        for (int j = 0; j < BLOCKY; j++)
        {
            blocks[count].Update(dev, devcon, ball.GetX(), ball.GetY(), 0.1f, 0.1f);
            count++;
        }
    }

    // switch the back buffer and the front buffer
    swapchain->Present(0, 0);
}


// this is the function that cleans up Direct3D and COM
void CleanD3D(Paddle paddle)
{
    swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

    // close and release all existing COM objects
    pLayout->Release();
    pVS->Release();
    pPS->Release();
    swapchain->Release();
    backbuffer->Release();
    dev->Release();
    devcon->Release();
}


// this is the function that creates the shape to render
void InitGraphics()
{


}


// this function loads and prepares the shaders
void InitPipeline()
{
    // load and compile the two shaders
    ID3D10Blob* VS, * PS;
    D3DX11CompileFromFile(L"shaders.hlsl", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
    D3DX11CompileFromFile(L"shaders.hlsl", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

    // encapsulate both shaders into shader objects
    dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
    dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

    // set the shader objects
    devcon->VSSetShader(pVS, 0, 0);
    devcon->PSSetShader(pPS, 0, 0);

    // create the input layout object
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
    devcon->IASetInputLayout(pLayout);
}
