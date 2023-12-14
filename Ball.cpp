#include "Ball.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hBall_(-1)
{
}

//�f�X�g���N�^
Ball::~Ball()
{
}

//������
void Ball::Initialize()
{
    //���f���f�[�^�̃��[�h
    hBall_ = Model::Load("assets/Donuts.fbx");
    assert(hBall_ >= 0);
}

//�X�V
void Ball::Update()
{
    transform_.position_ = XMFLOAT3(0.9, 0.5, -1);
    transform_.scale_ = XMFLOAT3(0.3f, 0.3f, 0.3f);
}

//�`��
void Ball::Draw()
{
    Model::SetTransform(hBall_, transform_);
    Model::Draw(hBall_);
}

//�J��
void Ball::Release()
{
}