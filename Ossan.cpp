#include "Ossan.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "CDTimer.h"
#include "Ground.h"
#include "DirectXMath.h"



Ossan::Ossan(GameObject* parent)
	:GameObject(parent, "Ossan"), hmodel_(-1),moveDir_(MAXDIR),cdtimer_(nullptr),PlayerState_(PSTATE::IDLE),oldState_(PSTATE::IDLE)
{
}

void Ossan::SetIdleState() {
	PlayerState_ = PSTATE::IDLE; Model::SetAnimFrame(hmodel_, PFRAMES[PlayerState_].first, PFRAMES[PlayerState_].second, 1);
}
void Ossan::SetRunState() {
	PlayerState_ = PSTATE::MOVING; Model::SetAnimFrame(hmodel_, PFRAMES[PlayerState_].first, PFRAMES[PlayerState_].second, 1);
}
void Ossan::SetAttackState()
{
	PlayerState_ = PSTATE::ATTACK; Model::SetAnimFrame(hmodel_, PFRAMES[PlayerState_].first, PFRAMES[PlayerState_].second, 1);
}
void Ossan::SetDefeetState() { PlayerState_ = PSTATE::DEATH; }
void Ossan::SetTraversalState() { PlayerState_ = PSTATE::TRAVERSAL; }

void Ossan::Initialize()
{
	hmodel_ = Model::Load("Man.fbx");
	assert(hmodel_ >= 0);
	transform_.scale_ = { 0.1f, 0.1f, 0.1f };
	transform_.position_ = { 0.0f, 0.0f, 0.0f };
	posState_ = OCENTER;
	Model::SetAnimFrame(hmodel_, PFRAMES[PlayerState_]. first, PFRAMES[PlayerState_].second, 1.5 );
	cdtimer_ = new CDTimer(this, TRAVERSAL_TIME);
}


void Ossan::GetInputData()
{
	PPOS_STATE oldstate = posState_;
	if (isTraverasal()) {
		oldState_ = PlayerState_;
		return;//ˆÚ“®’†‚È‚ç“ü—ÍŽó•t‚µ‚È‚¢
	}

	if (Input::IsKeyDown(DIK_A) || Input::IsKeyDown(DIK_LEFT))
	{
		if (PlayerState_ != MOVING) {
			oldState_ = PlayerState_;
			PlayerState_ = MOVING;
			Model::SetAnimFrame(hmodel_, PFRAMES[MOVING].first, PFRAMES[MOVING].second, 1);
		}
		posState_ = posSetter(ILEFT);
		moveDir_ = UP;
		if (posState_ != oldstate) {
			oldState_ = PlayerState_;
			PlayerState_ = TRAVERSAL;
			cdtimer_->ResetTimer();
			cdtimer_->StartTimer();
		}
	}
	if (Input::IsKeyDown(DIK_D) || Input::IsKeyDown(DIK_RIGHT))
	{
		if (PlayerState_ != MOVING) {
			oldState_ = PlayerState_;
			PlayerState_ = MOVING;
			Model::SetAnimFrame(hmodel_, PFRAMES[MOVING].first, PFRAMES[MOVING].second, 1);
		}
		posState_ = posSetter(IRIGHT);
		moveDir_ = UP;
		if (posState_ != oldstate) {
			oldState_ = PlayerState_;
			PlayerState_ = TRAVERSAL;
			cdtimer_->ResetTimer();
			cdtimer_->StartTimer();
		}
	}
	//transform_.position_ = REF_POS[posState_];
	if (Input::IsKeyUp(DIK_SPACE))
	{
		oldState_ = PlayerState_;
		PlayerState_ = (PSTATE)((int)((PlayerState_ + 1)%((int)MAXOSS)));
		Model::SetAnimFrame(hmodel_, PFRAMES[PlayerState_].first, PFRAMES[PlayerState_].second, 1);
	}
}

PPOS_STATE Ossan::posSetter(INPUT_STATE inputDir)
{
	int posTmp = (int)posState_;
	int inputVal[3]{ -1, 1, 0 };
	
	posTmp = posTmp + inputVal[inputDir];
	if (posTmp < 0)
		posTmp = PPOS_STATE::OLEFT;
	if (posTmp >= PPOS_STATE::MAXPOS)
		posTmp = PPOS_STATE::ORIGHT;
	return (PPOS_STATE)posTmp;
}

XMVECTOR Ossan::GetMoveVec()
{
	static XMFLOAT3 oldPos = transform_.position_;
	XMVECTOR mV = XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&oldPos) ;
	oldPos = transform_.position_;
	return mV;
}

void Ossan::Update()
{	
	PPOS_STATE oldPos = posState_;
	GetInputData();
	float speed = MOVESPEED;

	float lerpTime = (float)(cdtimer_->GetTime());
	if (lerpTime <= 0)
	{
		PlayerState_ = MOVING;
		lerpTime = 0;
	}

	if (PlayerState_ == TRAVERSAL) {
		float lerpRate = 1.0f - lerpTime / TRAVERSAL_TIME;
		static XMVECTOR sourcePos;
		static XMVECTOR targetPos;

		if (oldState_ != TRAVERSAL) {
			sourcePos = XMLoadFloat3(&REF_POS[oldPos]);
			targetPos = XMLoadFloat3(&REF_POS[posState_]);
		}
		XMVECTOR lpos = XMVectorLerp(sourcePos, targetPos, lerpRate);

		float rotAngle = TR_ROTANGLE*sin(lerpRate * XM_PI);
		if (XMVectorGetX(sourcePos) > XMVectorGetX(targetPos))
			rotAngle = -rotAngle;
		XMStoreFloat3(&(transform_.position_), lpos);
		transform_.rotate_.y = rotAngle;
	}
	else
	{
		transform_.rotate_.y = 0.0f;
		transform_.position_ = REF_POS[posState_];
	}
	//Model::ResetAnimeRenderState(hmodel_);
	cdtimer_->Update();

}

void Ossan::Draw()
{
	Model::SetTransform(hmodel_, transform_);
	Model::Draw(hmodel_);
}

void Ossan::Release()
{
}
