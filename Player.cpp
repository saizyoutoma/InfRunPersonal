#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "CDTimer.h"
#include "Ground.h"
#include "DirectXMath.h"

void Player::GetInputData()
{
    PPOS_STATE oldstate = posState_;
    if (isTraverasal()) {
		oldState_ = playerState_;
		return;//ˆÚ“®’†‚È‚ç“ü—ÍŽó•t‚µ‚È‚¢
	}

    if (Input::IsKeyDown(DIK_A)) {
        if (oldState_ != RUN) {
            oldState_= playerState_;
            playerState_ = RUN;
            Model::SetAnimFrame(hmodel_, PFRAMES[RUN].first, PFRAMES[RUN].second, 1);
        }
        posState_ = posSetter(ILEFT);
        moveDir_ = LEFT;
    }
}

PPOS_STATE Player::posSetter(INPUT_STATE inputDir)
{
    return PPOS_STATE();
}

Player::Player(GameObject* parent)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
}

void Player::Update()
{
}

void Player::Draw()
{
}

void Player::Release()
{
}

void Player::SetIdleState()
{
}

void Player::RunState()
{
}

void Player::SetDefeetState()
{
}

void Player::SetTraversalState()
{
}

XMVECTOR Player::GetMoveVec()
{
    return XMVECTOR();
}
