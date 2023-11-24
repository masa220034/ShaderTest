#include "Stage.h"
#include "Engine/Model.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hGround_(-1), hBall_(-1)
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
    hBall_ = Model::Load("assets/Ball.fbx");
    assert(hGround_ >= 0);
    assert(hBall_ >= 0);
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
    Model::SetTransform(hGround_, transform_);
    Model::SetTransform(hBall_, transform_);
    Model::Draw(hGround_);
    Model::Draw(hBall_);
}

//開放
void Stage::Release()
{
}
