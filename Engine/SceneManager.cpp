#include "SceneManager.h"
#include "Model.h"
#include "../TestScene.h"

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	//シーンを切り替える
	//現在のシーンと、nextシーンが別だったら切り替え
	if (currentSceneID_ != nextSceneID_)
	{
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();

		Model::Release();
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		}
		currentSceneID_ = nextSceneID_;
	}
	//現在のシーンの跡片付け
	//新しいシーンの準備
	//currentSceneID_をnextSceneID_
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;
}
