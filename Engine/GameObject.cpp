#include "GameObject.h"
#include "SphereCollider.h"

GameObject::GameObject()
	:pParent_(nullptr), IsDead_(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name),IsDead_(false), pCollider_(nullptr)
{
	if (parent != nullptr)
	{
		this->transform_.pParent_ = &(parent->transform_);
	}
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	Update();

	RoundRobin(GetRootJob());
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->IsDead_ == true)
		{
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::ReleaseSub()
{
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
		SAFE_DELETE(*itr);
	}
	Release();
}

void GameObject::KillMe()
{
	IsDead_ = true;
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(x, y, z));
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_)
	{
		return(this);//������_objName�̃I�u�W�F�N�g������!
	}
	else
	{
		
		//for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		for(auto itr: childList_)
		{
			//GameObject* obj = (*itr)->FindChildObject(_objName);
			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
			{
				return obj;
			}
		}
	}
	return nullptr;
}

/// <summary>
/// �ċN�Ăяo����RootJob��T���Ă��̃A�h���X��Ԃ��֐�
/// </summary>
/// <returns>RootJob�̃A�h���X(GameObject *�^)</returns>
GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this;
	}

	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	return GetRootJob()->FindChildObject(_objName);
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	if (pTarget->pCollider_ == nullptr)
	{
		return; //Target��Collider���A�^�b�`����Ă��Ȃ�
	}

	/*XMVECTOR v{transform_.position_.x - pTarget->transform_.position_.x,
				transform_.position_.y - pTarget->transform_.position_.y,
				transform_.position_.z - pTarget->transform_.position_.z,
				 0 };
	XMVECTOR dist = XMVector3Dot(v, v);*/
	float dist = (transform_.position_.x - pTarget->transform_.position_.x) * (transform_.position_.x - pTarget->transform_.position_.x)
		+ (transform_.position_.y - pTarget->transform_.position_.y) * (transform_.position_.y - pTarget->transform_.position_.y)
		+ (transform_.position_.z - pTarget->transform_.position_.z) * (transform_.position_.z - pTarget->transform_.position_.z);
	float rDist = (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius()) * (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius());

	if (dist <= rDist)
	{
		double p = 0;
	}
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	if (pCollider_ == nullptr)
	{
		return;
	}

	if (pTarget->pCollider_ != nullptr) //������Target
	{
		Collision(pTarget);
	}

	for (auto itr:pTarget->childList_)
	{
		RoundRobin(itr);
	}
}
