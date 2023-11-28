#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hGround_(-1)
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //���f���f�[�^�̃��[�h
    hGround_ = Model::Load("assets/Ground.fbx");
    assert(hGround_ >= 0);
}

//�X�V
void Stage::Update()
{
    Camera::SetPosition(XMFLOAT3(2, 3, -3));

    transform_.scale_ = XMFLOAT3(2.5f, 2.5f, 2.5f);
}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hGround_, transform_);
    Model::Draw(hGround_);
}

//�J��
void Stage::Release()
{
}
