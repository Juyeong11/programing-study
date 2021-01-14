#include"D3D.h"
#include"MathHelper.h"
#include"UploadBuffer.h"

struct MyVertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT3 Tangent;
	DirectX::XMFLOAT3 Normal;
	DirectX::XMFLOAT2 Tex0;
	DirectX::XMFLOAT2 Tex1;
	DirectX::PackedVector::XMCOLOR color;
};

std::vector<D3D12_INPUT_ELEMENT_DESC> myInputLayout{
	{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
	{"TANGENT",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
	{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,24,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
	{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,36,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
	{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,44,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
	{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,52,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},

};

/*2번 입력슬록을 2개로 나누어 보자
const UINT colorByteSize = (UINT)color.size() * sizeof(VColorData);
ThrowIfFailed(D3DCreateBlob(colorByteSize, &colorVertexBufferCPU));
CopyMemory(colorVertexBufferCPU->GetBufferPointer(), color.data(), colorByteSize);
colorVertexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
	mCommandList.Get(), color.data(), colorByteSize, colorVertexBufferUploader);
colorVertexBufferView.BufferLocation = colorVertexBufferGPU->GetGPUVirtualAddress();
colorVertexBufferView.StrideInBytes = sizeof(VColorData);
colorVertexBufferView.SizeInBytes = colorByteSize;


	mCommandList->IASetVertexBuffers(0, 1, &mBoxGeo->VertexBufferView());
	mCommandList->IASetVertexBuffers(1, 1, &colorVertexBufferView);

	mInputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
*/

/*4번 사각뿔그리기
* 후면 제거를 꼭 생각하자
* array<VPosData, 5> vertices =
	{
		XMFLOAT3(-1.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, +1.0f), 
		XMFLOAT3(1.0f, 0.0f, 0.0f), 
		XMFLOAT3(0.0f, 0.0f, -1.0f), 
		XMFLOAT3(0.0f, 1.5f, 0.0f), 
	};
	array<VColorData, 8> color =
	{
		XMFLOAT4(Colors::White),
		XMFLOAT4(Colors::White),
		XMFLOAT4(Colors::White),
		XMFLOAT4(Colors::Black),
		XMFLOAT4(Colors::Black),
		XMFLOAT4(Colors::Black),
		XMFLOAT4(Colors::Cyan),
		XMFLOAT4(Colors::Cyan)
	};
	array<std::uint16_t, 18> indices =
	{
		0,2,1,0,3,2,0,4,3,3,4,2,2,4,1,1,4,0
	};

*/

/*6번 정점셰이더에서 정점을 세계공간으로 변환하기 전에 다른 변환을 하자
* struct ObjectConstants
{
	XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
	double gTime = 0.0;
};

	objConstants.gTime = gt.TotalTime();

	상수버퍼를 추가하는 방법은 왜 안되는 거지??
	나중에 여기서 문제점을 찾아보자
	
	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
	cbvHeapDesc.NumDescriptors = 1;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.NodeMask = 0;
	md3dDevice->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&mCbvHeap));
	* 
	//CD3DX12_DESCRIPTOR_RANGE cbvTable1;
	//cbvTable1.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);

	slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable);
	//slotRootParameter[1].InitAsDescriptorTable(1, &cbvTable1);
	* 
	gTime = std::make_unique<UploadBuffer<double>>(md3dDevice.Get(), 1, true);

	UINT TimeByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(double));

	D3D12_GPU_VIRTUAL_ADDRESS tcbAddress = gTime->Resource()->GetGPUVirtualAddress();

	tcbAddress += 1*TimeByteSize;

	D3D12_CONSTANT_BUFFER_VIEW_DESC tcbDesc;
	tcbDesc.BufferLocation = tcbAddress;
	tcbDesc.SizeInBytes = d3dUtil::CalcConstantBufferByteSize(sizeof(double));

	md3dDevice->CreateConstantBufferView(
		&tcbDesc,
		mCbvHeap->GetCPUDescriptorHandleForHeapStart());
	//mCommandList->SetGraphicsRootDescriptorTable(1, mCbvHeap->GetGPUDescriptorHandleForHeapStart());
	***
*
*/

/*
* 7번
* 
*	mCommandList->DrawIndexedInstanced(
		mBoxGeo->DrawArgs["box"].IndexCount-36, 1, 0, 0, 0
	);
	mCommandList->DrawIndexedInstanced(
		mBoxGeo->DrawArgs["box"].IndexCount-18, 1, 18, 5, 0
	);

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
	array<VColorData, 8> color =
	{
		XMFLOAT4(Colors::White),
		XMFLOAT4(Colors::White),
		XMFLOAT4(Colors::White),
		XMFLOAT4(Colors::Black),
		XMFLOAT4(Colors::Black),
		XMFLOAT4(Colors::Black),
		XMFLOAT4(Colors::Cyan),
		XMFLOAT4(Colors::Cyan)
	};
	array<std::uint16_t, 18> Pyramidindices =
	{
		0,2,1,
		0,3,2,
		0,4,3,
		3,4,2,
		2,4,1,
		1,4,0
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
*/

/*8,9번
* 	psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;
* 
*/

/*10번
		{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
*셰이더코드는 따로 안건들여도 된다.-> 인자 하나하나를 받는거니까 상관없지
*/

/*11번
* 입력슬롯의 번호만 맞으면 위치가 바뀌든 어떻게 되던 상관이 없네요
* 	mCommandList->IASetVertexBuffers(1, 1, &mBoxGeo->VertexBufferView());
	mCommandList->IASetVertexBuffers(0, 1, &colorVertexBufferView);

	{ "COLOR", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
*/
/*12, 13번
*	mScreenViewport.TopLeftX = 0;
	mScreenViewport.TopLeftY = 0;
	mScreenViewport.Width = static_cast<float>(mClientWidth);
	mScreenViewport.Height = static_cast<float>(mClientHeight);
	mScreenViewport.MinDepth = 0.0f;
	mScreenViewport.MaxDepth = 1.0f;

	mScissorRect = { 0, 0, mClientWidth, mClientHeight };
*/
/*15번 
* clip은 값이 0보다 작으면 버리는 연산을 수행한다.
*/