#include "TitleScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

TitleScene::TitleScene(GameObject* parent)
{
}

void TitleScene::Initialize()
{
	tImage_ = Image::Load("Image\\title.jpg");
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_P))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
}

void TitleScene::Draw()
{
	Image::Draw(tImage_);
}

void TitleScene::Release()
{
}
