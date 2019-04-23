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

	//流星ゲージ土台
	prefab::CSpriteRender* r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/StarBar_base.dds", 20.0f, 300.0f);
	CVector3 Position = { -550.0f, -10.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//流星ゲージ
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/StarBar.dds", 20.0f, 300.0f);
	Position = { -550.0f, -160.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//流星ゲージ上部分
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/StarBarUe.dds", 20.0f, 300.0f);
	Position = { -550.0f, -10.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);


	//寿命土台
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/LifeBar_base.dds", 120.0f, 480.0f);
	Position = { -600.0f, -20.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//バー
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/LifeBar.dds", 120.0f, 480.0f);
	Position = { -600.0f, -215.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//寿命上部分
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/LifeBarUe.dds", 120.0f, 480.0f);
	Position = { -600.0f, -20.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);

	//ソウルアイコン
	r = NewGO<prefab::CSpriteRender>(1);
	r->Init(L"sprite/soulIC.dds", 100.0f, 100.0f);
	Position = { -600.0f, -220.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//残機アンダー
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Zanki.dds", 300.0f, 300.0f);
	Position = { -550.0f, 280.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);


	m_fontRender = NewGO<prefab::CFontRender>(1);
	return true;

}

void Player_Status::Update() {

	CVector3 LifeScale = CVector3::Zero;
	CVector3 StarScale = CVector3::Zero;
	Player * player = Player::GetInstance();
	GameData * gamedata = GameData::GetInstance();

	//寿命ゲージを動かす
	float DEF_Life = (float)gamedata->GetDEF_Life();
	float NOW_Life = (float)player->GetLife();

	//寿命の拡大率を計算
	float LifeY = NOW_Life / DEF_Life;
	//LifeY *= 480.0f;
	LifeScale = { 1.0f,LifeY,1.0f };
	//寿命バーの色が変わる基準は？
	float RED_Life = DEF_Life / 2.0f;
	//寿命バーの色変え
	if (NOW_Life < RED_Life) {
		LifeColor = { 255.0f,0.5f,0.5f,1.0f };
	}else {
		LifeColor = { 1.0f,1.0f,1.0f,1.0f };
	}

	m_spriteRender[4]->SetPivot(LifePivot);
	m_spriteRender[4]->SetScale(LifeScale);
	m_spriteRender[4]->SetMulColor(LifeColor);

	//流星ゲージを動かす
	float NOW_StarPower = (float)gamedata->GetStar_Power();
	float DEF_StarPower = (float)gamedata->GetMAXStar_Power();

	//ゲージの拡大率を計算
	float StarY = NOW_StarPower / DEF_StarPower;
	StarScale = { 1.0f,StarY,1.0f };
	//流星バーの色変え
	if (NOW_StarPower == DEF_StarPower) {
		StarColor = { 1.0f,1.0f,1.0f,1.0f };
	}
	else {
		StarColor = { 0.5f,0.5f,255.0f,1.0f };
	}

	m_spriteRender[1]->SetPivot(StarPivot);
	m_spriteRender[1]->SetScale(StarScale);
	m_spriteRender[1]->SetMulColor(StarColor);

	//残機を更新
	wchar_t text[256];

	swprintf(text, L"%d", gamedata->GetZanki());

	m_fontRender->SetText(text);
	m_fontRender->SetPosition(ZankiPos);
	m_fontRender->SetScale(ZankiScale);
	
}


