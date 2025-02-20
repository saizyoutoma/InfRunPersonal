#include "Ground.h"
#include "Engine/Model.h"

Ground::Ground(GameObject* parent)
	:GameObject(parent, "Ground"), hmodel_(-1)
{
}

void Ground::Initialize()
{
	hmodel_ = Model::Load("Ground_fix.fbx");
	assert(hmodel_ >= 0);

	for (int i = 0; i < ROAD_NUM; i++) {
		Transform tmp;
		tmp.scale_ = { 1, 1, 1 };
		tmp.position_ = { 0, 0, (float)(i * 2)   };
		gt.push_back(tmp);
	}
}

void Ground::Update()
{
}

void Ground::Draw()
{
	for (int i = 0; i < ROAD_NUM; i++) {
		Model::SetTransform(hmodel_, gt[i]);
		Model::Draw(hmodel_);
	}
}

void Ground::Release() 
{
}
