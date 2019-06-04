#include "stdafx.h"
#include "EffectPlay.h"
#include "Player.h"

EffectPlay::EffectPlay()
{
}


EffectPlay::~EffectPlay()
{
}

bool EffectPlay::Start()
{
	//エフェクトのインスタンスの作成。
	effect = NewGO<prefab::CEffect>(0);
	effect->Play(animation.c_str());	//再生
	effect->SetScale(scale);
	effect->SetPosition(position);

	return true;
}

void EffectPlay::Update() {
	if (P_TuibiFlag == true) {
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		effect->SetPosition(P_Position);
	}

	//お前はもう洋梨
	bool Flag = effect->IsPlay();
	if (Flag == false) {
		DeleteGO(this);
	}

}