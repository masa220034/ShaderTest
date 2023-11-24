#include "Stage.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hGround_(-1), hBall_(-1)
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
    hBall_ = Model::Load("assets/Ball.fbx");
    assert(hGround_ >= 0);
    assert(hBall_ >= 0);
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hGround_, transform_);
    Model::SetTransform(hBall_, transform_);
    Model::Draw(hGround_);
    Model::Draw(hBall_);
}

//�J��
void Stage::Release()
{
}
