#include "Wanwan.h"
#include "Engine/Model.h"

Wanwan::Wanwan(GameObject* parent)
	:GameObject(parent,"Wanwan"),speed_(INIT_SPEED)
{
}

void Wanwan::Initialize()
{
	hmodel_ = Model::Load("Enemy.fbx");
	assert(hmodel_ >= 0);

	transform_.scale_ = { 0.0013, 0.0013, 0.0013 };
	transform_.position_ = { 0, 0, 20};
	transform_.rotate_ = { 0, 180, 0 };
	wss_ = WanwanSS::MOVE;
	Model::SetAnimFrame(hmodel_, WANWANFRAMES[wss_].first, WANWANFRAMES[wss_].second, 5.0);
}

void Wanwan::Update()
{
	//Model::ResetAnimeRenderState(hmodel_);
	//transform_.position_.z = transform_.position_.z - speed_;
}

void Wanwan::Draw()
{
	Model::SetTransform(hmodel_, transform_);
	Model::Draw(hmodel_);
}

void Wanwan::Release()
{
}
