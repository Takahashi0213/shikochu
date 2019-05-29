#include "stdafx.h"
#include "EffectPlay.h"

EffectPlay::EffectPlay()
{
}


EffectPlay::~EffectPlay()
{
}

bool EffectPlay::Start()
{
	//エフェクトのインスタンスの作成。
	prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
	effect->Play(animation.c_str());	//再生
	effect->SetScale(scale);
	effect->SetPosition(position);

	return true;
}
