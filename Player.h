#pragma once
#include "Engine/GameObject.h"

enum PSTATE
{
	IDLE, RUN, JUMP, ATTACK, ROLL,MAXPLAYER
};

class CDTimer;

namespace
{
	enum MOVEDIR
	{
		UP, LEFT, DOWN, RIGHT,MAXDIR
	};
	XMFLOAT3 MOVEC[MAXDIR + 1]
	{
		{0,0,1},{-1,0,0},{0,0,-1},{1,0,0},{0,0,0}
	};
	float MOVESPEED = 0.01f;
	std::pair<int, int> PFRAMES[MAXDIR]
	{
		{0,147},{148,186},{187,226},{227,500}
	};
	const XMFLOAT3 INITDIR{ 0,0,1 };
	const XMFLOAT3 REF_POS[3]{ {-0.35f, 0.0f, 0.0f}, {0.0f,0.0f,0.0f}, {0.35f,0.0f,0.0f} };
	const float TRAVERSAL_TIME{ 0.5f };
	const float TR_ROTANGLE{ 75 };
	const float ROTANGLE[5]{ 0, -90, 180, 90, 0 };
	enum PPOS_STATE{ PLEFT, PCENTER, PRIGHT, MAXPOS };
	enum INPUT_STATE{ILEFT,IRIGHT, IONE, IMAX};
}

class Player : public GameObject
{
	int hmodel_;
	void GetInputData();
	MOVEDIR moveDir_;
	PSTATE playerState_;
	PSTATE oldState_;

	PPOS_STATE posState_;
	PPOS_STATE posSetter(INPUT_STATE inputDir);

	bool isTraverasal() { return(playerState_ == JUMP); }
public:
	Player(GameObject* parent);

	~Player() override;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
	void SetIdleState();
	void RunState();
	void SetDefeetState();
	void SetTraversalState();
	PSTATE GetState() { return playerState_; }
public:
	XMVECTOR GetMoveVec();
	CDTimer* cdtimer_;
};

