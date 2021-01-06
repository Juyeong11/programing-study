#pragma once
#include"D3DUtil.h"
#include"GameTimer.h"
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
class D3D {
protected:
	D3D(HINSTANCE hInstance);
	D3D(const D3D& rhs) = delete;
	D3D& operator=(const D3D& rhs) = delete;
	virtual ~D3D();
public:

	static D3D* GetApp();

	HINSTANCE AppInst()const;
	HWND MainWnd()const;
	float AspectRatio()const;

	bool Get4xMsaaState()const;
	void Set4xMsaaState(bool value);
	int Run();

	virtual bool Initialize();

	LRESULT D3D::MsgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

protected:
	bool InitMainWindow();
	bool InitDirect3D();
	void FlushCommandQueue();

	void CreateCommandObjects();
	void CreateSwapChain();
	

	ID3D12Resource* CurrentBackBuffer()const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;

protected:
	virtual void CreateRtvAndDsvDescriptorHeaps();
	virtual void OnResize();
	virtual void Update(const GameTimer& gt) = 0;
	virtual void Draw(const GameTimer& gt) = 0;

	virtual void OnMouseDown(WPARAM btnState, int x, int y){}
	virtual void OnMouseUp(WPARAM btnState,int x, int y){}
	virtual void OnMouseMove(WPARAM btnState,int x, int y){}

protected:
	static D3D* mApp;

	HINSTANCE D3D_hInstance = nullptr;
	HWND hwnd = nullptr;

	Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;

	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
	UINT64 mCurrentFence = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;
	static const int SwapChainBufferCount = 2;
	int mCurrBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;

	D3D12_VIEWPORT mScreenViewport;
	D3D12_RECT mScissorRect;

	UINT mRtvDescriptorSize = 0;
	UINT mDsvDescriptorSize = 0;
	UINT mCbvSrvUavDescriptorSize = 0;

	DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	bool      m4xMsaaState = false;
	UINT      m4xMsaaQuality = 0;
	GameTimer mTimer;
	bool      mAppPaused = false;
	int mClientWidth = 800;
	int mClientHeight = 600;
};