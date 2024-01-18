#pragma once
// include the basic windows header files and the Direct3D header files
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <iostream>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")



// define the screen resolution
#define SCREEN_WIDTH  600	
#define SCREEN_HEIGHT 600
const int BLOCKX = 13;
const int BLOCKY = 5;


 struct VERTEX { FLOAT X, Y, Z; D3DXCOLOR Color; };


