#include "Arrow.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Arrow::Arrow(GameObject* parent)
    :GameObject(parent, "Arrow"), hArrow_(-1)
{
}

//�f�X�g���N�^
Arrow::~Arrow()
{
}

//������
void Arrow::Initialize()
{
    //���f���f�[�^�̃��[�h
    hArrow_ = Model::Load("assets/Arrow.fbx");
    assert(hArrow_ >= 0);
}

//�X�V
void Arrow::Update()
{
}

//�`��
void Arrow::Draw()
{
    Model::SetTransform(hArrow_, transform_);
    Model::Draw(hArrow_);
}

//�J��
void Arrow::Release()
{
}
