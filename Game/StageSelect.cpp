#include "stdafx.h"
#include "StageSelect.h"
#include "Game.h"
#include "GameData.h"
#include "LevelData.h"
#include "UICamera.h"

StageSelect* StageSelect::m_instance = nullptr;

StageSelect::StageSelect()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}

StageSelect::~StageSelect()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}
	for (int i = 0; i < m_skinModelRender.size(); i++) {
		DeleteGO(m_skinModelRender[i]);
	}

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool StageSelect::Start() {

	GameData * gamedata = GameData::GetInstance();
	SelectStageNow = gamedata->GetStageNo(); //ステージNoを取得するぜ

	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_motion1].Load(L"animData/StageMini1.tka");
	m_animClips[enAnimationClip_motion1].SetLoopFlag(true);
	m_animClips[enAnimationClip_motion2].Load(L"animData/StageMini2.tka");
	m_animClips[enAnimationClip_motion2].SetLoopFlag(true);

	//必要な有象無象を設定するぜ
	//0番 上の飾り
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/SelectDodai.dds", 1280.0f, 220.0f);
	r->SetPosition({ 0.0f ,250.0f,0.0f });
	m_spriteRender.push_back(r);
	//1番 タイムカード
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Time.dds", 400.0f*1.3, 430.0f*1.3);
	r->SetPosition({ -380.0f , -80.0f,0.0f });
	m_spriteRender.push_back(r);

	//虫も出る…ムシモデル… 0番
	e = NewGO<prefab::CSkinModelRender>(10);
	e->Init(L"modelData/bug.cmo", nullptr, 0);
	e->SetPosition({ -100.0f,-50.0f,0.0f });
	e->SetScale(CVector3::One);	
	m_rotation.SetRotation(CVector3::AxisY, 3.1f);
	e->SetRotation(m_rotation);
	m_skinModelRender.push_back(e);

	return true;
}

void StageSelect::Update(){

	//これでおけ
	if (Pad(0).IsPress(enButtonStart)) {
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}

}
