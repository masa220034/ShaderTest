#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include <vector>

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

using std::vector;

enum RENDER_STATE
{
	RENDER_DIRLIGHT,
	RENDER_PNTLIGHT,
};

class Texture;

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4	diffuse;
		XMFLOAT4	ambient;
		XMFLOAT4	specular;
		float  shininess;
	};

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP; //���[���h�r���[�v���W�F�N�V����
		XMMATRIX    matW; //���[���h�ϊ��̂�
		XMMATRIX	matNormal; //�X�P�[���~���s�ړ��̋t�s��
		XMFLOAT4    diffuseColor; //FBX����Ƃ��Ă����ʂ̐F
		XMFLOAT4    ambientColor;
		XMFLOAT4    specularColor;
		FLOAT       shininess;
		BOOL        isTextured;
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;
	vector <int> indexCount_;

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
	RENDER_STATE state_;
public:
	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    SetRenderingShader(RENDER_STATE _state) { state_ = _state; }
	void    Release();
};
