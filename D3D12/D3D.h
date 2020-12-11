#pragma once
#include<Windows.h>
#include<iostream>
#include<wrl.h>
#include<d3d12.h>
#include"d3dx12.h"
#include<dxgi.h>
#include<dxgi1_4.h>
#include<assert.h>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
class D3D {
protected:

	HINSTANCE D3D_hInstance = nullptr;
	HWND hwnd = nullptr;

	Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;

	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
	UINT64 mCurrentFence = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDIrectCmdListAlloc;
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
	
	int mClientWidth = 800;
	int mClientHeight = 600;
protected:
	void CreateCommandObjects();
	void CreateSwapChain();
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;
protected:
	virtual void CreateRtvAndDsvDescriptorHeaps();
	virtual void OnResize();
public:
	D3D(HINSTANCE hInstance);

	bool InitMainWindow();
	bool InitDirect3D();
	void FlushCommandQueue();
	bool Run();


};