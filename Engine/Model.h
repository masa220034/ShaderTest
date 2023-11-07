#pragma once
#include<string>
#include<vector>
#include "Fbx.h"

namespace Model
{
	struct ModelData
	{
		Fbx* pFbx_; //FBX
		Transform transform_;//�g�����X�t�H�[��
		std::string filename_;
	};
	
	int Load(std::string FileName);
	void SetTransform(int hModel, Transform transfrom);
	void Draw(int hModel);
	void Release();
}