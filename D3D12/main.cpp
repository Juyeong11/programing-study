#include"D3D.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	D3D box(hInstance);
	box.InitMainWindow();
	box.InitDirect3D();


	return box.Run();
}

