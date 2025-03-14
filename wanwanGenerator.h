#pragma once
#include "Engine/GameObject.h"
#include "Wanwan.h"
#include <vector>


using std::vector;

namespace {
	std::pair<int, int> GENPAIR[] = { {1,2},{0,2},{0,1} };
	const XMFLOAT3 WAN_POS[3]{ {-0.35f, 0.1f, 20.0f}, {0.0f,0.1f,20.0f}, {0.35f,0.1f,20.0f} };
	const float GENTIME{ 2.0 };//時間じゃなく距離にした方がいいかも
}

class wanwanGenerator :
    public GameObject
{
	bool isGenerated_;
	int spaceLane_;
	int oldLane_;
	int GenerateNum(int _n);
	vector<Wanwan*> wanList;
	float speed_;
	float time_;
	float spawnTimer_;
public:
	void Generate();
	void SetSpeed(float _speed);
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	wanwanGenerator(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

