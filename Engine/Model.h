#pragma once
#include<string>
#include<vector>
#include "Fbx.h"

namespace Model
{
	struct ModelData
	{
		Fbx* pFbx_; //FBX
		Transform transform_;//トランスフォーム
		std::string filename_;
	};
	
	int Load(std::string FileName);
	void SetTransform(int hModel, Transform transfrom);
	Fbx* GetModel(int _hModel);
	void Draw(int hModel);
	void Release();
	void ToggleRenderState();
}