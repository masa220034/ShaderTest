#include "Arrow.h"
#include "Engine/Model.h"

//コンストラクタ
Arrow::Arrow(GameObject* parent)
    :GameObject(parent, "Arrow"), hArrow_(-1)
{
}

//デストラクタ
Arrow::~Arrow()
{
}

//初期化
void Arrow::Initialize()
{
    //モデルデータのロード
    hArrow_ = Model::Load("assets/Arrow.fbx");
    assert(hArrow_ >= 0);
}

//更新
void Arrow::Update()
{
}

//描画
void Arrow::Draw()
{
    Model::SetTransform(hArrow_, transform_);
    Model::Draw(hArrow_);
}

//開放
void Arrow::Release()
{
}
