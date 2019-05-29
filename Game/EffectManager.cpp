#include "stdafx.h"
#include "EffectManager.h"
#include "EffectPlay.h"

EffectManager* EffectManager::m_instance = nullptr;

EffectManager::EffectManager()
{

	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


EffectManager::~EffectManager()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

//エフェクト再生くん
void EffectManager::EffectPlayer(Effect EF, CVector3 position, CVector3 scale) {
	//作成
	EffectPlay* p = NewGO<EffectPlay>(0);
	//名前を引っ張ってくる
	int len = (int)wcslen(DetaBase[EF]);
	for (int x = 0; x < len+1; x++) {
		EF_Name[x] = DetaBase[EF][x];
	}
	//設定
	p->SetAnimation(EF_Name);
	p->SetPosition(position);
	p->SetScale(scale);

}