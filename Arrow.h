#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Arrow : public GameObject
{
    int hArrow_;
public:
    //�R���X�g���N�^
    Arrow(GameObject* parent);

    //�f�X�g���N�^
    ~Arrow();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

