#include"D3D.h"
#include"MathHelper.h"
#include"UploadBuffer.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

struct VPosData
{
	XMFLOAT3 Pos;
};
struct VColorData
{
	XMCOLOR Color;
};
struct ObjectConstants
{
	XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
	double gTime = 0.0;
};
class BoxApp :public D3DApp
{
public:
	BoxApp(HINSTANCE hInstance);
	BoxApp(const BoxApp& rhs) = delete;
	BoxApp& operator=(const BoxApp& rhs) = delete;
	~BoxApp();

	virtual bool Initialize()override;
private:
	virtual void OnResize()override;
	virtual void Update(const GameTimer& gt)override;
	virtual void Draw(const GameTimer& gt)override;

	virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
	virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
	virtual void OnMouseMove(WPARAM btnState, int x, int y)override;

	void BuildDescriptorHeaps();
	void BuildConstantBuffers();
	void BuildRootSignature();
	void BuildShadersAndInputLayout();
	void BuildBoxGeometry();
	void BuildPSO();

private:
	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
	ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

	std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;
	std::unique_ptr<UploadBuffer<double>> gTime = nullptr;
	std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;

	//
	Microsoft::WRL::ComPtr<ID3DBlob> colorVertexBufferCPU = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> colorVertexBufferGPU = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> colorVertexBufferUploader = nullptr;
	D3D12_VERTEX_BUFFER_VIEW colorVertexBufferView;

	//


	ComPtr<ID3DBlob> mvsByteCode = nullptr;
	ComPtr<ID3DBlob> mpsByteCode = nullptr;

	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

	ComPtr<ID3D12PipelineState> mPSO = nullptr;

	XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	float mTheta = 1.5f * XM_PI;
	float mPhi = XM_PIDIV4;
	float mRadius = 5.0f;

	POINT mLastMousePos;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
#if defined(DEBUG)|defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


	BoxApp theApp(hInstance);
	if (!theApp.Initialize())
		return 0;

	return theApp.Run();


}
BoxApp::BoxApp(HINSTANCE hInstance) :
	D3DApp(hInstance)
{

}
BoxApp::~BoxApp()
{

}
void BoxApp::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}
void BoxApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}
void BoxApp::OnMouseMove(WPARAM btnState, int x, int y) {

	if ((btnState & MK_LBUTTON) != 0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f * static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(y - mLastMousePos.y));

		// Update angles based on input to orbit camera around box.
		mTheta -= dx;
		mPhi -= dy;

		// Restrict the angle mPhi.
		mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi - 0.1f);
	}
	else if ((btnState & MK_RBUTTON) != 0)
	{
		// Make each pixel correspond to 0.005 unit in the scene.
		float dx = 0.005f * static_cast<float>(x - mLastMousePos.x);
		float dy = 0.005f * static_cast<float>(y - mLastMousePos.y);

		// Update the camera radius based on input.
		mRadius += dx - dy;

		// Restrict the radius.
		mRadius = MathHelper::Clamp(mRadius, 3.0f, 15.0f);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}
bool BoxApp::Initialize()
{
	if (!D3DApp::Initialize())
		return false;
	//명령목록 재설정
	mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr);


	BuildDescriptorHeaps();
	BuildConstantBuffers();
	BuildRootSignature();
	BuildShadersAndInputLayout();
	BuildBoxGeometry();
	BuildPSO();

	mCommandList->Close();

	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	//명령 목록 제출-> 명령 대기열은 그 할당자에 담긴 명령들을 참조(CreateCommandAllocator)
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	//fence를 이용해 명령 대기열을 비운다.
	FlushCommandQueue();

	return true;
}
void BoxApp::OnResize()
{
	D3DApp::OnResize();

	//뷰포트 설정?
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);
}

void BoxApp::Update(const GameTimer& gt)
{


	float x = mRadius * sinf(mPhi) * cosf(mTheta);
	float z = mRadius * sinf(mPhi) * sinf(mTheta);
	float y = mRadius * cosf(mPhi);

	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, view);

	XMMATRIX world = XMLoadFloat4x4(&mWorld);
	XMMATRIX proj = XMLoadFloat4x4(&mProj);
	XMMATRIX worldViewProj = world * view * proj;

	// Update the constant buffer with the latest worldViewProj matrix.

	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
	objConstants.gTime = gt.TotalTime();
	mObjectCB->CopyData(0, objConstants);

}
//여기서부터시작
void BoxApp::Draw(const GameTimer& gt)
{
	//명령 기록에 관련된 메모리의 재활용을 위해 명령 할당자를 재설정
	//재설정은 GPU가 관련 명령목록을 모두 처리한 후 일어 난다.
	ThrowIfFailed(mDirectCmdListAlloc->Reset());
	//명령 목록을 ExecuteCommandList를 통해서 명령 대기열에 추가했으면 명령 목록을 재설정할 수 있다.
	//명령 목록을 재설정하면 메모리가 재활용된다.
	mCommandList->Reset(mDirectCmdListAlloc.Get(), mPSO.Get());

	mCommandList->RSSetViewports(1, &mScreenViewport);
	mCommandList->RSSetScissorRects(1, &mScissorRect);

	//자원 용도에 관련된 상태 전이를 Direct3D에 통지한다.
	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
		CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	//후면 버퍼와 깊이 버퍼를 지운다.
	mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
	mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
		1.0f, 0, 0, nullptr);

	//랜더링 결과가 기록될 렌더 대상 버퍼들을 지정한다.
	mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());

	ID3D12DescriptorHeap* descriptorHeaps[] = { mCbvHeap.Get() };
	mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);


	mCommandList->SetGraphicsRootSignature(mRootSignature.Get());

	mCommandList->IASetVertexBuffers(1, 1, &mBoxGeo->VertexBufferView());
	mCommandList->IASetVertexBuffers(0, 1, &colorVertexBufferView);
	mCommandList->IASetIndexBuffer(&mBoxGeo->IndexBufferView());
	mCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	mCommandList->SetGraphicsRootDescriptorTable(0, mCbvHeap->GetGPUDescriptorHandleForHeapStart());

	mCommandList->DrawIndexedInstanced(
		mBoxGeo->DrawArgs["box"].IndexCount - 36, 1, 0, 0, 0
	);
	mCommandList->DrawIndexedInstanced(
		mBoxGeo->DrawArgs["box"].IndexCount - 18, 1, 18, 5, 0
	);
	//자원 용도에 관련된 상태 전이를 Direct3D에 통지한다
	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	mCommandList->Close();

	//명령목록을 명령대기열에 추가한다.
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	//후면버퍼와 전면버퍼를 교환
	mSwapChain->Present(0, 0);
	mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

	FlushCommandQueue();
}

void BoxApp::BuildDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
	cbvHeapDesc.NumDescriptors = 1;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.NodeMask = 0;
	md3dDevice->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&mCbvHeap));
}

void BoxApp::BuildConstantBuffers()
{

	mObjectCB = std::make_unique < UploadBuffer<ObjectConstants>>(md3dDevice.Get(), 1, true);

	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));

	D3D12_GPU_VIRTUAL_ADDRESS cbAddress = mObjectCB->Resource()->GetGPUVirtualAddress();

	int boxCBufIndex = 0;
	cbAddress += boxCBufIndex * objCBByteSize;

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = cbAddress;
	cbvDesc.SizeInBytes = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));

	md3dDevice->CreateConstantBufferView(
		&cbvDesc,
		mCbvHeap->GetCPUDescriptorHandleForHeapStart());

}

void BoxApp::BuildRootSignature()
{
	CD3DX12_ROOT_PARAMETER slotRootParameter[1];

	CD3DX12_DESCRIPTOR_RANGE cbvTable;
	cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
	//CD3DX12_DESCRIPTOR_RANGE cbvTable1;
	//cbvTable1.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);

	slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable);
	//slotRootParameter[1].InitAsDescriptorTable(1, &cbvTable1);


	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0, nullptr,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> serializedRootSig = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

	if (errorBlob != nullptr)
	{
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}

	md3dDevice->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&mRootSignature)
	);

}


void BoxApp::BuildShadersAndInputLayout()
{
	HRESULT hr = S_OK;

	mvsByteCode = d3dUtil::CompileShader(L"color.hlsl", nullptr, "VS", "vs_5_0");
	mpsByteCode = d3dUtil::CompileShader(L"color.hlsl", nullptr, "PS", "ps_5_0");

	mInputLayout =
	{
		{ "COLOR", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
}

void BoxApp::BuildBoxGeometry()
{
	using std::array;

	array<VPosData, 5> Pyramidvertices =
	{
		XMFLOAT3(-1.0f, 1.1f, 0.0f),
		XMFLOAT3(0.0f, 1.1f, +1.0f),
		XMFLOAT3(1.0f, 1.1f, 0.0f),
		XMFLOAT3(0.0f, 1.1f, -1.0f),
		XMFLOAT3(0.0f, 2.6f, 0.0f),
	};
	array<VPosData, 8> Boxvertices =
	{
		XMFLOAT3(-1.0f, -1.0f, -1.0f),
		XMFLOAT3(-1.0f, +1.0f, -1.0f),
		XMFLOAT3(+1.0f, +1.0f, -1.0f),
		XMFLOAT3(+1.0f, -1.0f, -1.0f),
		XMFLOAT3(-1.0f, -1.0f, +1.0f),
		XMFLOAT3(-1.0f, +1.0f, +1.0f),
		XMFLOAT3(+1.0f, +1.0f, +1.0f),
		XMFLOAT3(+1.0f, -1.0f, +1.0f),
	};
	array<VColorData, 13> color =
	{
		XMCOLOR(Colors::Blue),
		XMCOLOR(Colors::Red),
		XMCOLOR(Colors::Red),
		XMCOLOR(Colors::Red),
		XMCOLOR(Colors::Red),

		XMCOLOR(Colors::White),
		XMCOLOR(Colors::Black),
		XMCOLOR(Colors::Red),
		XMCOLOR(Colors::Green),
		XMCOLOR(Colors::Blue),
		XMCOLOR(Colors::Yellow),
		XMCOLOR(Colors::Cyan),
		XMCOLOR(Colors::Magenta) };
	array<std::uint16_t, 18> Pyramidindices =
	{
		0,2,1,
		0,3,2,
		0,4,3,
		3,4,2,
		1,4,0,
		2,4,1

	};

	array<std::uint16_t, 36> Boxindices =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	const UINT colorByteSize = (UINT)color.size() * sizeof(VColorData);
	ThrowIfFailed(D3DCreateBlob(colorByteSize, &colorVertexBufferCPU));
	CopyMemory(colorVertexBufferCPU->GetBufferPointer(), color.data(), colorByteSize);
	colorVertexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
		mCommandList.Get(), color.data(), colorByteSize, colorVertexBufferUploader);
	colorVertexBufferView.BufferLocation = colorVertexBufferGPU->GetGPUVirtualAddress();
	colorVertexBufferView.StrideInBytes = sizeof(VColorData);
	colorVertexBufferView.SizeInBytes = colorByteSize;



	const UINT PyramibvbSize = (UINT)Pyramidvertices.size() * sizeof(VPosData);
	const UINT BoxvbSize = (UINT)Boxvertices.size() * sizeof(VPosData);

	const UINT PyramidibSize = (UINT)Pyramidindices.size() * sizeof(std::uint16_t);
	const UINT BoxibSize = (UINT)Boxindices.size() * sizeof(std::uint16_t);


	std::vector<VPosData> vertices;
	vertices.insert(vertices.end(), Pyramidvertices.begin(), Pyramidvertices.end());
	vertices.insert(vertices.end(), Boxvertices.begin(), Boxvertices.end());
	std::vector<uint16_t> indices;
	indices.insert(indices.end(), Pyramidindices.begin(), Pyramidindices.end());
	indices.insert(indices.end(), Boxindices.begin(), Boxindices.end());

	const UINT vbByteSize = (UINT)vertices.size() * sizeof(VPosData);
	const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);
	mBoxGeo = std::make_unique<MeshGeometry>();
	mBoxGeo->Name = "boxGeo";

	ThrowIfFailed(D3DCreateBlob(vbByteSize, &mBoxGeo->VertexBufferCPU));
	CopyMemory(mBoxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &mBoxGeo->IndexBufferCPU));
	CopyMemory(mBoxGeo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

	mBoxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
		mCommandList.Get(), vertices.data(), vbByteSize, mBoxGeo->VertexBufferUploader);

	mBoxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
		mCommandList.Get(), indices.data(), ibByteSize, mBoxGeo->IndexBufferUploader);

	mBoxGeo->VertexByteStride = sizeof(VPosData);
	mBoxGeo->VertexBufferByteSize = vbByteSize;
	mBoxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
	mBoxGeo->IndexBufferByteSize = ibByteSize;

	SubmeshGeometry submesh;
	submesh.IndexCount = (UINT)indices.size();
	submesh.StartIndexLocation = 0;
	submesh.BaseVertexLocation = 0;

	mBoxGeo->DrawArgs["box"] = submesh;
}

void BoxApp::BuildPSO()
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
	psoDesc.pRootSignature = mRootSignature.Get();
	psoDesc.VS = {
		reinterpret_cast<BYTE*>(mvsByteCode->GetBufferPointer()),
	mvsByteCode->GetBufferSize()
	};

	psoDesc.PS = {
		reinterpret_cast<BYTE*>(mpsByteCode->GetBufferPointer()),
		mpsByteCode->GetBufferSize()
	};
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	//psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = mBackBufferFormat;
	psoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	psoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	psoDesc.DSVFormat = mDepthStencilFormat;
	md3dDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPSO));
}