#include "stdafx.h"
#include "StarComet.h"
#include "StarComet_Inseki.h"

StarComet* StarComet::m_instance = nullptr;

StarComet::StarComet()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


StarComet::~StarComet()
{	
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void StarComet::Comet_Hassya(CVector3 PlayerMoveSpeed, CVector3 Player_Pos) {

	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/Comet.wav");
	ss->SetVolume(1.0f);
	ss->Play(false);

	//ポジションと移動速度の計算
	PlayerMoveSpeed.Normalize();

	//隕石生成
	StarComet_Inseki*comet = NewGO<StarComet_Inseki>(0, "StarComet_Inseki");
	comet->SetPosition(Player_Pos);
	comet->SetMoveSpeed(PlayerMoveSpeed);
}
