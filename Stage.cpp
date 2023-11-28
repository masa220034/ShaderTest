#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hGround_(-1)
{
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
}

//更新
void Stage::Update()
{
    Camera::SetPosition(XMFLOAT3(2, 3, -3));

    transform_.scale_ = XMFLOAT3(2.5f, 2.5f, 2.5f);
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
