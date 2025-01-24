#include "ResultScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

ResultScene::ResultScene(GameObject* parent)
{
}

void ResultScene::Initialize()
{
	cImage_ = Image::Load("Image\\clear.jpg");
	gImage_ = Image::Load("Image\\gameover.jpg");
}

void ResultScene::Update()
{
	if (Input::IsKeyDown(DIK_T))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void ResultScene::Draw()
{
	Image::Draw(cImage_);
}

void ResultScene::Release()
{
}
