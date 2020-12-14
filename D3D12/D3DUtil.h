#pragma once
#include<Windows.h>
#include<iostream>
#include<wrl.h>
#include<d3d12.h>
#include"d3dx12.h"
#include<dxgi.h>
#include<dxgi1_4.h>
#include<assert.h>

class D3Dutil
{
public:
	static Microsoft::WRL::ComPtr<ID3D12Resource> CreateDefaultBuffer(
		ID3D12Device* device,
		ID3D12GraphicsCommandList* cmdList,
		const void* ininData,
		UINT64 byteSize,
		Microsoft::WRL::ComPtr<ID3D12Resource>& uploadBuffer);
};