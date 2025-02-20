#include "wanwanGenerator.h"
#include <set>
#include "Engine/Model.h"
#include "Engine/Debug.h"

int wanwanGenerator::GenerateNum(int _n)
{
	
	float thd = (float)rand() / RAND_MAX;
	if (thd > 0.5)
		return GENPAIR[_n].first;
	else
		return GENPAIR[_n].second;
}

void wanwanGenerator::Generate()
{
	isGenerated_ = false;
}

void wanwanGenerator::SetSpeed(float _speed)
{
	speed_ = _speed;
}

wanwanGenerator::wanwanGenerator(GameObject* parent)
	:GameObject(parent, "WG"), isGenerated_(false), oldLane_(1)
{
	spaceLane_ = rand() % 3;
}

void wanwanGenerator::Initialize()
{
	//wan_ = new Wanwan(this->GetParent());
	//wan_ = Instantiate<Wanwan>(this->GetParent());
	//wan_->Initialize();
}

void wanwanGenerator::Update()
{
	if (!isGenerated_) {
		if (wanList.size() < 9) {
			Wanwan* w = Instantiate<Wanwan>(this->GetParent());

			oldLane_ = spaceLane_;
			spaceLane_ = GenerateNum(oldLane_);

			w->SetPosition(WAN_POS[spaceLane_]);

			// ¶¬‚³‚ê‚½1‘Ì‚ðwanList‚É’Ç‰Á
			wanList.push_back(w);

			isGenerated_ = true;
		}
		time_ = 0.0f;
	}

	for (auto& theI : wanList)
	{
		XMVECTOR mv{ 0,0,-0.5 };
		XMFLOAT3 fl3tmp = theI->GetPosition();
		XMVECTOR tmp = XMLoadFloat3(&fl3tmp);
		tmp = tmp + speed_ * mv;
		
		XMStoreFloat3(&(fl3tmp), tmp);
		theI->SetPosition(fl3tmp);
	}
	Debug::Log((int)wanList.size(), true);
	auto itr = wanList.begin();
	while (itr != wanList.end())
	{
		if ((*itr)->GetPosition().z < 0)
		{
			(*itr)->KillMe();
			itr = wanList.erase(itr);
		}
		else
		{
			itr++;
		}
	}

}

void wanwanGenerator::Draw()
{
	//for (auto& theI : wanList)
	//{
	//	wan_->SetPosition(theI.position_);
	//	wan_->Draw();
	//}
}

void wanwanGenerator::Release()
{
}
