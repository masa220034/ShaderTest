#include "Ball.h"
#include "Engine/Model.h"

//コンストラクタ
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hBall_(-1)
{
}

//デストラクタ
Ball::~Ball()
{
}

//初期化
void Ball::Initialize()
{
    //モデルデータのロード
    hBall_ = Model::Load("assets/Donuts.fbx");
    assert(hBall_ >= 0);
}

//更新
void Ball::Update()
{
    transform_.position_ = XMFLOAT3(0.9, 0.5, -1);
    transform_.scale_ = XMFLOAT3(0.3f, 0.3f, 0.3f);
}

//描画
void Ball::Draw()
{
    Model::SetTransform(hBall_, transform_);
    Model::Draw(hBall_);
}

//開放
void Ball::Release()
{
}