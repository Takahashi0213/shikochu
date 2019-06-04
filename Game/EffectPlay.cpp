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
	//�G�t�F�N�g�̃C���X�^���X�̍쐬�B
	effect = NewGO<prefab::CEffect>(0);
	effect->Play(animation.c_str());	//�Đ�
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

	//���O�͂����m��
	bool Flag = effect->IsPlay();
	if (Flag == false) {
		DeleteGO(this);
	}

}