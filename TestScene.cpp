#include "TestScene.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Ossan.h"
#include "Engine/Debug.h"
#include "Ground.h"
#include "Wanwan.h"
#include "wanwanGenerator.h"
#include "Engine/Debug.h"
#include "Engine/Direct3D.h"
#include "Engine/SceneManager.h"

namespace {
	const XMFLOAT3 INITCAMPOS{ 0, 1, -1.5 };
	//const XMFLOAT3 INITCAMPOS{ 0, 0.5, 0.1 };
	
}

void TestScene::PlayUpdate()
{
	if (timer_->IsTimeOver())
	{
		wang->Generate();
		timer_->ResetTimer();
		timer_->StartTimer();
	}
	timer_->Update();
}

void TestScene::ReadyUpdate()
{
	
	if (timer_->IsTimeOver())
	{
		PSTATE = PLAY;
		player->SetRunState();
		wang = Instantiate<wanwanGenerator>(this);
		wang->SetSpeed(0.1f);
	
		timer_->SetInitTime(GPERIODS[PSTATE]);
		timer_->StartTimer();
	}
	
	timer_->Update();
}



//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),timer_(nullptr),PSTATE(READY)
{
}

//初期化
void TestScene::Initialize()
{

	timer_ = new CDTimer(this, GPERIODS[READY]);

	ground = Instantiate<Ground>(this);
	camPos_ = INITCAMPOS;
	Camera::SetPosition(camPos_);

	player = Instantiate<Ossan>(this);
	XMFLOAT3 pos = player->GetWorldPosition();
	Camera::SetTarget({ 0.0f, 0.2f, 2.0f });
}

//更新
void TestScene::Update()
{
	switch (PSTATE)
	{
	case READY:
		ReadyUpdate();
		break;
	case PLAY:
		PlayUpdate();
		break;
	case DEAD:
		break;
	default:
		return;
	}

	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
}

//描画//
void TestScene::Draw()
{
	switch (PSTATE)
	{
	case READY:
		break;
	case PLAY:
		//EffectDraw();
		break;
	case DEAD:
		break;
	default:
		return;
	}
	
}

//開放
void TestScene::Release()
{
}
