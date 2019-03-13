#include "stdafx.h"
#include "GameData.h"
#include "Player_Status.h"
#include "Player.h"
#include "GameData.h"

Player_Status::Player_Status()
{
}


Player_Status::~Player_Status()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}

}

bool Player_Status::Start() {

	//寿命土台
	prefab::CSpriteRender* r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/LifeBar_base.dds", 480.0f, 120.0f);
	CVector3 Position = { 400.0f, 300.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//バー
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/LifeBar.dds", 480.0f, 120.0f);
	Position = { 400.0f, 300.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//寿命上部分
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/LifeBarUe.dds", 480.0f, 120.0f);
	Position = { 400.0f, 300.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//ソウルアイコン
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/soulIC.dds", 100.0f, 100.0f);
	Position = { 150.0f, 300.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//残機アンダー
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Zanki.dds", 300.0f, 300.0f);
	Position = { -550.0f, 280.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);

	return true;

}

void Player_Status::Update() {

	CVector3 LifeScale = CVector3::Zero;
	Player * player = FindGO<Player>("Bug");
	GameData * gamedata = FindGO<GameData>("GameData");

	float DEF_Life = (float)gamedata->GetDEF_Life();
	float NOW_Life = (float)player->GetLife();

	//寿命の拡大率を計算
	float LifeX = NOW_Life / DEF_Life;
	//LifeX *= 480.0f;
	LifeScale = { LifeX,1.0f,1.0f };

	m_spriteRender[1]->SetPivot(LifePivot);
	//m_spriteRender[1]->SetScale(LifeScale);

}

void Player_Status::PostRender(CRenderContext& rc)
{
	GameData * gamedata = FindGO<GameData>("GameData");

	m_font.Begin(rc);	//フォントの描画開始。
	wchar_t text[256];
	swprintf(text, L"%d", gamedata->GetZanki());
	m_font.Draw(text, { -550.0f, 280.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.0f, 3.0);
	//m_font.SetShadowParam(true, 2.0f, { 20.0f, 0.0f, 0.0f, 0.0f });

	m_font.End(rc);		//フォントの描画終了。

}

