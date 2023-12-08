#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hGround_(-1), lightPosition
{
}

void Stage::IntConstantBuffer()
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CBUFF_STAGESCENE);
    cb.Usage = D3D11_USAGE_DYNAMIC;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;
    Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //モデルデータのロード
    hGround_ = Model::Load("assets/Ground.fbx");
    assert(hGround_ >= 0);

    IntConstantBuffer();
}

//更新
void Stage::Update()
{
    Camera::SetPosition(XMFLOAT3(2, 3, -3));

    transform_.scale_ = XMFLOAT3(2.5f, 2.5f, 2.5f);

    CBUFF_STAGESCENE cb;
    cb.lightPosition = lightSourcePosition_;
    XMStoreFloat4(&cb.eyePos, Camera::GetEyePosition());

    Direct3D::pContext_->UpdateSubresource(pCBStageScene_, 0, NULL, &cb, 0, 0);

    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_); //頂点シェーダー用
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_); //
}

//描画
void Stage::Draw()
{
    Model::SetTransform(hGround_, transform_);
    Model::Draw(hGround_);
}

//開放
void Stage::Release()
{
}
