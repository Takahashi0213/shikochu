#include "stdafx.h"
#include "PlayerUpgrade.h"
#include "GameData.h"
#include "SaveData.h"
#include "StageSelect.h"
#include "TransitionMaker.h"
#include "SkillData.h"

PlayerUpgrade* PlayerUpgrade::m_instance = nullptr;

PlayerUpgrade::PlayerUpgrade()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}

PlayerUpgrade::~PlayerUpgrade()
{

	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}
	for (int i = 0; i < m_spriteRender_skill.size(); i++) {
		DeleteGO(m_spriteRender_skill[i]);
	}
	for (int i = 0; i < m_fontRender_skill.size(); i++) {
		DeleteGO(m_fontRender_skill[i]);
	}

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool PlayerUpgrade::Start() {

	//SE
	ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/SE_On.wav");
	ss->SetVolume(2.0f);
	ss->Play(false);
	ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/SE_On2.wav");
	ss->SetVolume(2.0f);
	ss->Play(false);

	Setting();

	//0番→背景
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//1番→背景
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyoka1.dds", 1280.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,DEF_Mul };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//2番→明かり差分
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyoka2.dds", 1280.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,DEF_Mul2 };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//3番→むしさん
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyoka3.dds", 1380.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetPosition({ 0.0f,720.0f,0.0f });
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//4番→枠1
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyokawaku.dds", 398.0f, 140.0f);
	MulColor = { 0.5f,0.5f,0.5f,0.5f };
	r->SetPosition({ wakuPosDEF_X,wakuPosDefY*2.0f + 720.0f ,0.0f });
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//5番→枠2
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyokawaku.dds", 398.0f, 140.0f);
	MulColor = { 0.5f,0.5f,0.5f,0.5f };
	r->SetPosition({ wakuPosDEF_X,wakuPosDefY + 720.0f ,0.0f });
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//6番→枠3
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyokawaku.dds", 398.0f, 140.0f);
	MulColor = { 0.5f,0.5f,0.5f,0.5f };
	r->SetPosition({ wakuPosDEF_X, 720.0f ,0.0f });
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//7番→トランシーバー
	r = NewGO<prefab::CSpriteRender>(4);
	r->Init(L"sprite/tr_waku.dds", 400.0f, 267.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -350.0f,-100.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 0.0f,0.0f,1.0f });
	m_spriteRender.push_back(r);
	//8番→退出アイコン
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/ExitP.dds", 300.0f, 300.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -370.0f,100.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//9番→LB
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/LB.dds", 100.0f, 100.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -380.0f,250.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//10番→Aボタン
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/A_Button.dds", 50.0f, 50.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -130.0f,wakuPosDefY*2.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//11番→くも
	r = NewGO<prefab::CSpriteRender>(6);
	r->Init(L"sprite/kumo.dds", 100.0f, 150.0f);
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetPosition({ 620.0f,360.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//12番→雑談
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/zatsudan.dds", 200.0f, 100.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -300.0f,-330.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//13番→右矢印
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyokamigi.dds", 50.0f, 300.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ 600.0f,100.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//14番→左矢印
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyokahidari.dds", 50.0f, 300.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -220.0f,100.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//15番→上矢印
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/Up.dds", 50.0f, 50.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ 440.0f,335.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//16番→下矢印
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/Down.dds", 50.0f, 50.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ 440.0f,-115.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);

	//スキル関連
	float Kakusi = 0.0f; //初期配置調整用
	//0番 枠1
	skill_r = NewGO<prefab::CSpriteRender>(4);
	skill_r->Init(L"sprite/skillwaku_Gray.dds", 400.0f, 140.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ wakuPosDEF_X_Skill + SkillMoveX,(wakuPosDefY_Skill*2.0f)+ SkillY_Hosei,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);
	//1番 枠1 アイコン
	skill_r = NewGO<prefab::CSpriteRender>(3);
	skill_r->Init(L"sprite/skillwakuUnder_Null.dds", 400.0f, 140.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ wakuPosDEF_X_Skill + SkillMoveX,(wakuPosDefY_Skill*2.0f) + SkillY_Hosei,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);
	//2番 枠2
	skill_r = NewGO<prefab::CSpriteRender>(4);
	skill_r->Init(L"sprite/skillwaku_Gray.dds", 400.0f, 140.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ wakuPosDEF_X_Skill + SkillMoveX,wakuPosDefY_Skill + SkillY_Hosei,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);
	//3番 枠2 アイコン
	skill_r = NewGO<prefab::CSpriteRender>(3);
	skill_r->Init(L"sprite/skillwakuUnder_Null.dds", 400.0f, 140.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ wakuPosDEF_X_Skill + SkillMoveX,wakuPosDefY_Skill + SkillY_Hosei,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);
	//4番 枠3
	skill_r = NewGO<prefab::CSpriteRender>(4);
	skill_r->Init(L"sprite/skillwaku_Gray.dds", 400.0f, 140.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ wakuPosDEF_X_Skill + SkillMoveX,0.0f + SkillY_Hosei,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);
	//5番 枠3 アイコン
	skill_r = NewGO<prefab::CSpriteRender>(3);
	skill_r->Init(L"sprite/skillwakuUnder_Null.dds", 400.0f, 140.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ wakuPosDEF_X_Skill + SkillMoveX,0.0f + SkillY_Hosei,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);
	//6番 Yアイコンカバー
	skill_r = NewGO<prefab::CSpriteRender>(4);
	skill_r->Init(L"sprite/skilliconWaku.dds", 150.0f, 100.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ -60.0f + SkillMoveX,-10.0f,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);
	//7番 Yアイコン
	skill_r = NewGO<prefab::CSpriteRender>(3);
	skill_r->Init(L"sprite/skillicon_0.dds", 150.0f, 100.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ -60.0f + SkillMoveX,-10.0f,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);
	//8番 Xアイコンカバー
	skill_r = NewGO<prefab::CSpriteRender>(4);
	skill_r->Init(L"sprite/skilliconWaku.dds", 150.0f, 100.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ 140.0f + SkillMoveX,-10.0f,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);
	//9番 Xアイコン
	skill_r = NewGO<prefab::CSpriteRender>(3);
	skill_r->Init(L"sprite/skillicon_0.dds", 150.0f, 100.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ 140.0f + SkillMoveX,-10.0f,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);
	//10番 Y文字
	skill_r = NewGO<prefab::CSpriteRender>(4);
	skill_r->Init(L"sprite/SkillY.dds", 50.0f,50.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ -60.0f + SkillMoveX,65.0f,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);
	//11番 X文字
	skill_r = NewGO<prefab::CSpriteRender>(4);
	skill_r->Init(L"sprite/SkillX.dds", 50.0f, 50.0f);
	MulColor = { 1.0f,1.0f,1.0f,Kakusi };
	skill_r->SetPosition({ 140.0f + SkillMoveX,65.0f,0.0f });
	skill_r->SetMulColor(MulColor);
	skill_r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(skill_r);

	//スキル用テキスト
	//1スキル名前 0番
	skill_f = NewGO<prefab::CFontRender>(5);
	//表示
	wchar_t text[256];
	//おわ
	swprintf(text, L"テストメッセージ");
	//はい。
	skill_f->SetText(text);
	skill_f->SetPosition({ wakuPosDEF_X_Skill - 150.0f + SkillMoveX,(wakuPosDefY_Skill*2.0f) + 55.0f + SkillY_Hosei });
	skill_f->SetScale(0.7f);
	skill_f->SetColor({ 1.0f,1.0f,1.0f,Kakusi });
	skill_f->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(skill_f);
	//1スキル説明 1番
	skill_f = NewGO<prefab::CFontRender>(5);
	//表示
	text[256];
	//おわ
	swprintf(text, L"はつどうちゅうは\nいんせきをはっしゃできる");
	//はい。
	skill_f->SetText(text);
	skill_f->SetPosition({ wakuPosDEF_X_Skill - 130.0f + SkillMoveX,(wakuPosDefY_Skill*2.0f) + 18.0f + SkillY_Hosei });
	skill_f->SetScale(0.7f);
	skill_f->SetColor({ 1.0f,0.4f,0.4f,Kakusi });
	skill_f->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(skill_f);
	//2スキル名前 2番
	skill_f = NewGO<prefab::CFontRender>(5);
	//表示
	text[256];
	//おわ
	swprintf(text, L"テストメッセージ");
	//はい。
	skill_f->SetText(text);
	skill_f->SetPosition({ wakuPosDEF_X_Skill - 150.0f + SkillMoveX,wakuPosDefY_Skill+ 55.0f + SkillY_Hosei });
	skill_f->SetScale(0.7f);
	skill_f->SetColor({ 1.0f,1.0f,1.0f,Kakusi });
	skill_f->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(skill_f);
	//2スキル説明 3番
	skill_f = NewGO<prefab::CFontRender>(5);
	//表示
	text[256];
	//おわ
	swprintf(text, L"テストメッセージ\nテストメッセージ");
	//はい。
	skill_f->SetText(text);
	skill_f->SetPosition({ wakuPosDEF_X_Skill - 130.0f + SkillMoveX,wakuPosDefY_Skill + 18.0f + SkillY_Hosei });
	skill_f->SetScale(0.7f);
	skill_f->SetColor({ 1.0f,0.4f,0.4f,Kakusi });
	skill_f->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(skill_f);
	//3スキル名前 4番
	skill_f = NewGO<prefab::CFontRender>(5);
	//表示
	text[256];
	//おわ
	swprintf(text, L"テストメッセージ");
	//はい。
	skill_f->SetText(text);
	skill_f->SetPosition({ wakuPosDEF_X_Skill - 150.0f + SkillMoveX, 55.0f + SkillY_Hosei });
	skill_f->SetScale(0.7f);
	skill_f->SetColor({ 1.0f,1.0f,1.0f,Kakusi });
	skill_f->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(skill_f);
	//3スキル説明 5番
	skill_f = NewGO<prefab::CFontRender>(5);
	//表示
	text[256];
	//おわ
	swprintf(text, L"テストメッセージ\nテストメッセージ");
	//はい。
	skill_f->SetText(text);
	skill_f->SetPosition({ wakuPosDEF_X_Skill - 130.0f + SkillMoveX, 18.0f + SkillY_Hosei });
	skill_f->SetScale(0.7f);
	skill_f->SetColor({ 1.0f,0.4f,0.4f,Kakusi });
	skill_f->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(skill_f);

	//テキストン
	//ポイント 0番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	swprintf(text, L"%d", point);
	//はい。
	f->SetText(text);
	f->SetPosition({ 350.0f, -50.0f + 720.0f });
	f->SetScale(1.5f);
	f->SetColor({ 1.0f,0.2f,0.8f,1.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//ポイント文字 1番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	swprintf(text, L"point");
	//はい。
	f->SetText(text);
	f->SetPosition({ 500.0f, -70.0f + 720.0f });
	f->SetScale(0.6f);
	f->SetColor({ 0.8f,0.2f,0.7f,1.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//残機 2番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	swprintf(text, L"ざんき:%d",zanki);
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f + statusPosY + Ypos_hoge });
	f->SetScale(1.0f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//残機値段 3番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	if (zanki_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", zanki_Point);
	}
	else {
		zanki_Point = -1;
		swprintf(text, L"MAX");
	}
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f - 15.0f + Ypos_hoge });
	f->SetScale(0.8f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//攻撃 4番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	swprintf(text, L"こうげき:%d", attack);
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X, wakuPosDefY + statusPosY + Ypos_hoge });
	f->SetScale(1.0f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//攻撃値段 5番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	if (attack_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", attack_Point);
	}
	else {
		attack_Point = -1;
		swprintf(text, L"MAX");
	}
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X, wakuPosDefY - 15.0f + Ypos_hoge });
	f->SetScale(0.8f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//寿命 6番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	swprintf(text, L"じゅみょう:%d", jyumyo);
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X, statusPosY + Ypos_hoge });
	f->SetScale(1.0f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//寿命値段 7番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	if (jyumyo_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", jyumyo_Point);
	}
	else {
		jyumyo_Point = -1;
		swprintf(text, L"MAX");
	}
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X,- 15.0f + Ypos_hoge });
	f->SetScale(0.8f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//コメントくん 8番
	f = NewGO<prefab::CFontRender>(4);
	//表示
	text[256];
	//おわ
	swprintf(text, L"");
	//はい。
	f->SetText(text);
	f->SetPosition({ -480.0f,15.0f });
	f->SetScale(0.8f);
	f->SetColor({ 0.2f,1.0f,0.2f,1.0f });
	f->SetPivot({ 0.0f,1.0f });
	m_fontRender.push_back(f);
	//ステータスUP演出用 9番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	swprintf(text, L"XXXXX");
	//はい。
	f->SetText(text);
	f->SetPosition({ 380.0f, 50.0f });
	f->SetScale(1.0f);
	f->SetColor({ 1.0f,0.2f,0.2f,0.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);

	//前もって更新
	CommandUpdate_Skill();

	return true;
}

void PlayerUpgrade::Update() {

	//スタート演出！
	if (startTimer >= 48 && startTimer < 72) {
		//明るく
		DEF_Mul += 0.05f;
		if (DEF_Mul > 1.0f) {
			DEF_Mul = 1.0f;
		}
		m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul });
		DEF_Mul2 += 0.1f;
		if (DEF_Mul2 > 1.0f) {
			DEF_Mul2 = 1.0f;
		}
		m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
		m_spriteRender[3]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
		m_spriteRender[7]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
		m_spriteRender[8]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
		m_spriteRender[9]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
		m_spriteRender[10]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
		float MulX = DEF_Mul2;
		if (MulX > 0.5f) {
			MulX = 0.5f;
		}
		m_spriteRender[12]->SetMulColor({ 0.5f,0.5f,0.5f,MulX });

		//動け！
		CVector3 pos = m_spriteRender[3]->GetPosition();
		pos.y -= Move_Hoge;
		Move_Hoge *= 0.6f;
		if (pos.y < 0.0f) {
			pos.y = 0.0f;
		}
		//見た目がすごく汚い更新
		m_spriteRender[3]->SetPosition(pos);
		m_fontRender[0]->SetPosition({ 350.0f,pos.y - 50.0f });
		m_fontRender[1]->SetPosition({ 500.0f,pos.y - 70.0f });
		m_spriteRender[4]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY * 2.0f ,pos.z });
		m_spriteRender[5]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY,pos.z });
		m_spriteRender[6]->SetPosition({ wakuPosDEF_X,pos.y,pos.z });
		m_fontRender[2]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY * 2.0f + statusPosY });
		m_fontRender[3]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY * 2.0f - 15.0f });
		m_fontRender[4]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY + statusPosY });
		m_fontRender[5]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY - 15.0f });
		m_fontRender[6]->SetPosition({ wakuPosDEF_X,pos.y + statusPosY });
		m_fontRender[7]->SetPosition({ wakuPosDEF_X,pos.y - 15.0f });
		//7ばん
		pos = m_spriteRender[7]->GetPosition();
		CVector3 scl = m_spriteRender[7]->GetScale();
		if(startTimer < 54) {
			pos.y += 2.0f;
			scl.x += 0.2f;
			scl.y += 0.2f;
		}
		else if(startTimer < 60){
			pos.y -= 2.0f;
			scl.x -= (0.2f / 6.0f);
			scl.y -= (0.2f / 6.0f);
		}
		m_spriteRender[7]->SetPosition(pos);
		m_spriteRender[7]->SetScale(scl);
		if (startTimer == 71) {
			Transceiver(L"ヨウコソ\nカンソクシャ");
			CommandUpdate();
		}
	}

	//挙動
	if (startTimer >= 72 && DeleteFlag==false && SkillSetMoveTimer == -1) {//セットアップ移動完了＆削除中でない＆画面遷移中でない
		if (Pad(0).IsTrigger(enButtonUp)) {
			if (NowGamen == false) { //強化画面
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/select.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				KaiwaNow = -1;
				CommandNow--;
				if (CommandNow == -1) {
					CommandNow = 2;
				}
				if (startTimer > TranStart) {
					commandTren();
				}
				A_ButtonUpdate();
				CommandUpdate();
			}
			else { //スキルセット画面			
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/select.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				if (NouSkillCursor > 0) { //場所が1以上なら動く
					NouSkillCursor--;
					KaiwaNow = -1;
					commandTren_Skill();
				}
				else { //画面カーソル位置が0で選択位置が0じゃないなら1つ上に
					if (NowSelectSkill > 0) {
						NowSelectSkill--;
						KaiwaNow = -1;
						commandTren_Skill();
					}
				}

				CommandUpdate_Skill();
			}

		}
		else if (Pad(0).IsTrigger(enButtonDown)) {
			if (NowGamen == false) { //強化画面
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/select.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				KaiwaNow = -1;
				CommandNow++;
				if (CommandNow == 3) {
					CommandNow = 0;
				}
				if (startTimer > TranStart) {
					commandTren();
				}
				A_ButtonUpdate();
				CommandUpdate();
			}
			else { //スキルセット画面
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/select.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				if (NouSkillCursor < 2) { //場所が1以下なら動く
					NouSkillCursor++;
					KaiwaNow = -1;
					commandTren_Skill();
				}
				else { //画面カーソル位置が2で選択位置が最大-3未満なら1つ下に（-3しないと虚無を読み込んでしまいます）
					if (NowSelectSkill < SkillKazu-3) {
						NowSelectSkill++;
						KaiwaNow = -1;
						commandTren_Skill();
					}
				}

				CommandUpdate_Skill();

			}

		}
		else if (Pad(0).IsTrigger(enButtonA) && NowGamen == false) { //Aボタンを使うのは強化画面だけなので
			//購入！
			//取得色々
			GameData * gamedata = GameData::GetInstance();
			SaveData * savedata = SaveData::GetInstance();
			KaiwaNow = -1;

			switch (CommandNow) {
			case 0://残機
				//もしMAXなら買えない
				if (zanki_Point == -1) {
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					TransceiverStandby();
					Transceiver(L"コレイジョウ\nナニヲ フヤスト\nイウノデス？");
					buruFlag = true;
					break;
				}
				//買えるか確認
				if (zanki_Point <= point) {
					//買える
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/powerup.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					TransceiverStandby();
					Transceiver(L"アリガトウゴザイマス");
					savedata->PlusZanki_Upgrade();
					gamedata->PlusPoint(-zanki_Point);
					gamedata->PlusDEF_Zanki(Zanki_Plus);
					StatusUpTimer = 0; //ステータス上昇演出
					StatusUpAlpha = 1.0f;
					wchar_t text[256];
					//おわ
					swprintf(text, L"ざんき+%d", Zanki_Plus);
					//はい。
					m_fontRender[9]->SetText(text);
					m_fontRender[9]->SetPosition(StatusUP_DefPos);
					m_fontRender[9]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
					Setting();
					CommandUpdate();
				}
				else {
					//買えない
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					TransceiverStandby();
					Transceiver(L"ポイントガ タリマセン");
					buruFlag = true;
				}
				break;
			case 1://攻撃
				   //もしMAXなら買えない
				if (attack_Point == -1) {
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					TransceiverStandby();
					Transceiver(L"アナタ ツヨスギデス");
					buruFlag = true;
					break;
				}
				//買えるか確認
				if (attack_Point <= point) {
					//買える
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/powerup.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					TransceiverStandby();
					Transceiver(L"アリガトウゴザイマス");
					savedata->PlusAttack_Upgrade();
					gamedata->PlusPoint(-attack_Point);
					gamedata->PlusATK(Attack_Plus);
					StatusUpTimer = 0; //ステータス上昇演出
					StatusUpAlpha = 1.0f;
					wchar_t text[256];
					//おわ
					swprintf(text, L"こうげき+%d", Attack_Plus);
					//はい。
					m_fontRender[9]->SetText(text);
					m_fontRender[9]->SetPosition(StatusUP_DefPos);
					m_fontRender[9]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
					Setting();
					CommandUpdate();
				}
				else {
					//買えない
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					TransceiverStandby();
					Transceiver(L"ポイントガ タリマセン");
					buruFlag = true;
				}	
				break;
			case 2://寿命
				   //もしMAXなら買えない
				if (jyumyo_Point == -1) {
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					TransceiverStandby();
					Transceiver(L"コレガ アナタノ\nゲンカイデスヨ");
					buruFlag = true;
					break;
				}
				//買えるか確認
				if (jyumyo_Point <= point) {
					//買える
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/powerup.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					TransceiverStandby();
					Transceiver(L"アリガトウゴザイマス");
					savedata->PlusLife_Upgrade();
					gamedata->PlusPoint(-jyumyo_Point);
					gamedata->PlusLife(Life_Plus);
					StatusUpTimer = 0; //ステータス上昇演出
					StatusUpAlpha = 1.0f;
					wchar_t text[256];
					//おわ
					swprintf(text, L"じゅみょう+%d", Life_Plus);
					//はい。
					m_fontRender[9]->SetText(text);
					m_fontRender[9]->SetPosition(StatusUP_DefPos);
					m_fontRender[9]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
					Setting();
					CommandUpdate();
				}
				else {
					//買えない
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					TransceiverStandby();
					Transceiver(L"ポイントガ タリマセン");
					buruFlag = true;
				}	
				break;
			}

		}
		else if (Pad(0).IsTrigger(enButtonLB1)) { //グッバイ
			KaiwaNow = -1;
			DeleteFlag = true;
			TransceiverStandby();
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/SE_Door.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);
			Transceiver(L"マタドウゾ");
		}
		else if (Pad(0).IsTrigger(enButtonY) && NowGamen == true) { //スキルセット画面中にYボタンが押されたらセット処理
			SaveData * savedata = SaveData::GetInstance();

			//そもそも持ってないならダメです
			if (savedata->SkillGetFlag_Get(NowSelectSkill+ NouSkillCursor) == true) {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/SkillSet.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				//既にそこにセットされているならNoSkillにする
				//別の場所にセットされているなら入れ替える
				//それ以外なら普通にセットする

				if (savedata->GetSkill(false) == NowSelectSkill + NouSkillCursor) { //もうある
					savedata->SkillSetting(false, -1);
				}
				else if(savedata->GetSkill(true) == NowSelectSkill + NouSkillCursor) { //入れ替えタイム
					int hoge = savedata->GetSkill(false);
					savedata->SkillSetting(false, NowSelectSkill + NouSkillCursor);
					savedata->SkillSetting(true, hoge);
				}
				else { //普通にセット
					savedata->SkillSetting(false, NowSelectSkill + NouSkillCursor);
				}

				CommandUpdate_Skill();

			}
			else {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/blip.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				buruFlag_s = true;
			}
		}
		else if (Pad(0).IsTrigger(enButtonX) && NowGamen == true) { //スキルセット画面中にXボタンが押されたらセット処理
			SaveData * savedata = SaveData::GetInstance();

			//そもそも持ってないならダメです
			if (savedata->SkillGetFlag_Get(NowSelectSkill + NouSkillCursor) == true) {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/SkillSet.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				//既にそこにセットされているならNoSkillにする
				//別の場所にセットされているなら入れ替える
				//それ以外なら普通にセットする

				if (savedata->GetSkill(true) == NowSelectSkill + NouSkillCursor) { //もうある
					savedata->SkillSetting(true, -1);
				}
				else if (savedata->GetSkill(false) == NowSelectSkill + NouSkillCursor) { //入れ替えタイム
					int hoge = savedata->GetSkill(true);
					savedata->SkillSetting(true, NowSelectSkill + NouSkillCursor);
					savedata->SkillSetting(false, hoge);
				}
				else { //普通にセット
					savedata->SkillSetting(true, NowSelectSkill + NouSkillCursor);
				}

				CommandUpdate_Skill();

			}
			else {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/blip.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				buruFlag_s = true;
			}

		}
		else if (Pad(0).IsTrigger(enButtonRight) && NowGamen == false) { //強化画面で右を押したらスキルセットに遷移
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/select.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);
			
			NowGamen = true;
			SkillSetMoveTimer = 0;
		}
		else if (Pad(0).IsTrigger(enButtonLeft) && NowGamen == true) { //スキルセット画面で右を押したら強化に遷移
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/select.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);

			NowGamen = false;
			SkillSetMoveTimer = 0;

		}
		else if (Pad(0).IsTrigger(enButtonB) && startTimer > TranStart) { //雑談
			m_spriteRender[12]->SetScale({ 0.9f,0.9f,0.9f }); //話題を選ぶ
			KaiwaNo = rand() % ZatsudanKazu;
			KaiwaTimer = 0;
			KaiwaNow = 0;
			TransceiverStandby();
			int len = (int)wcslen(Zatsudan_1[KaiwaNo]);
			for (int z = 0; z < len + 1; z++) {
				Kaiwa[z] = Zatsudan_1[KaiwaNo][z];
			}
			Transceiver(Kaiwa);
		}

	}

	if (KaiwaNow > -1) {

		if (KaiwaNow == 0 && KaiwaTimer == 6) {
			m_spriteRender[12]->SetScale({ 1.0f,1.0f,1.0f });
		}

		if (KaiwaTimer > KaiwaLimit) {
			KaiwaTimer = -1;
			KaiwaNow++;

			if (KaiwaNow == 1) {
				TransceiverStandby();
				int len = (int)wcslen(Zatsudan_2[KaiwaNo]);
				for (int z = 0; z < len + 1; z++) {
					Kaiwa[z] = Zatsudan_2[KaiwaNo][z];
				}
				Transceiver(Kaiwa);
			}
			else if (KaiwaNow == 2) {

				if (Zatudan_Kaisuu[KaiwaNo] == 3) {
					TransceiverStandby();
					int len = (int)wcslen(Zatsudan_3[KaiwaNo]);
					for (int z = 0; z < len + 1; z++) {
						Kaiwa[z] = Zatsudan_3[KaiwaNo][z];
					}
					Transceiver(Kaiwa);
				}

				KaiwaNow = -1;
			}
		}

		KaiwaTimer++;
	}

	//sayonara.
	if (DeleteFlag == true) {

		//トランジション
		if (DeleteTimer == 60) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 10, false);
		}

		if (DeleteTimer < 60) {
			//部屋を暗くする
			DEF_Mul -= 0.05f;
			if (DEF_Mul < 0.4f) {
				DEF_Mul = 0.4f;
			}
			m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul });
			DEF_Mul2 -= 0.1f;
			if (DEF_Mul2 < 0.0f) {
				DEF_Mul2 = 0.0f;
			}
			if (NowGamen == false) {
				m_spriteRender[4]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
				m_spriteRender[5]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
				m_spriteRender[6]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			}
			m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
			m_spriteRender[3]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
			m_spriteRender[8]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			m_spriteRender[9]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			m_spriteRender[10]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			m_spriteRender[12]->SetScale({ 1.0f,1.0f,1.0f });
			m_spriteRender[12]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			if (NowGamen == true) {
				for (int i = 0; i < m_spriteRender_skill.size(); i++) { //スキル画面のやつを透明に
					m_spriteRender_skill[i]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
				}
				for (int i = 0; i < m_fontRender_skill.size(); i++) { //もじれつ
					CVector4 hoge = m_fontRender_skill[i]->GetColor();
					hoge.a = DEF_Mul2;
					m_fontRender_skill[i]->SetColor(hoge);
				}
			}
			for(int i = 0; i < 8; i++) { //強化用文字列
				if (NowGamen == false) {
					m_fontRender[i]->SetColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
				}
			}
			CVector3 E_pos = m_spriteRender[8]->GetPosition();
			E_pos.x -= 5.0f;
			m_spriteRender[8]->SetPosition(E_pos);
		}
		else if(DeleteTimer == 84) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 10, true);
			NewGO<StageSelect>(0);
			DeleteGO(this);
		}
		DeleteTimer++;
	}

	//明かり点滅
	if (startTimer > 60 && DeleteFlag == false) {
		if (akariTimer == 6) {
			MulColor = { 1.0f,1.0f,1.0f,0.95f };
			m_spriteRender[2]->SetMulColor(MulColor);
		}if (akariTimer == 12) {
			MulColor = { 1.0f,1.0f,1.0f,1.0f };
			m_spriteRender[2]->SetMulColor(MulColor);
			akariTimer = -1;
		}
		akariTimer++;
	}

	//跳んで震える
	if (jumpFlag == true) {
		CommandJump();
	}
	if (buruFlag == true) {
		CommandShake();
	}
	if (jumpFlag_s == true) {
		CommandJump_Skill();
	}
	if (buruFlag_s == true) {
		CommandShake_Skill();
	}

	if (TranFlag == true) {
		if (T_Timer == 4) {
			Transceiver(L"");
			T_Timer = -1;
		}
		T_Timer++;
	}

	//ステアプ演出
	if (StatusUpTimer >= 0) {
		CVector2 UP_pos = m_fontRender[9]->GetPosition();
		UP_pos.y += 3.0f;
		m_fontRender[9]->SetPosition(UP_pos);
		if (StatusUpTimer > 12) {
			StatusUpAlpha -= 0.1f;
			if (StatusUpAlpha < 0.0f) {
				StatusUpAlpha = 0.0f;
			}
		}
		m_fontRender[9]->SetColor({ 1.0f,0.2f,0.2f,StatusUpAlpha });
		if (StatusUpTimer > 24) {
			StatusUpTimer = -2;
			m_fontRender[9]->SetPosition(StatusUP_DefPos);
		}
		StatusUpTimer++;
	}

	//Aボタン
	if (DeleteFlag == false) {
		if (A_Timer == 24) {
			m_spriteRender[10]->Init(L"sprite/A_Button2.dds", 50.0f, 50.0f);
		}
		else if (A_Timer == 48) {
			A_Timer = -1;
			m_spriteRender[10]->Init(L"sprite/A_Button.dds", 50.0f, 50.0f);
		}
		A_Timer++;
	}

	//エグジットの左右移動
	if (DeleteFlag == false) {
		CVector3 E_pos = m_spriteRender[8]->GetPosition();
		CVector3 E_pos2 = m_spriteRender[9]->GetPosition();
		if (E_MoveFlag == false) {
			E_pos.x -= 1.0f;
			E_pos2.y += 0.2f;
		}
		else {
			E_pos.x += 1.0f;
			E_pos2.y -= 0.2f;
		}
		m_spriteRender[8]->SetPosition(E_pos);
		m_spriteRender[9]->SetPosition(E_pos2);

		if (E_MoveTimer == 24) {
			E_MoveFlag = true;
		}
		else if (E_MoveTimer == 49) {
			E_MoveTimer = -1;
			E_MoveFlag = false;
		}
		E_MoveTimer++;
	}

	//ヨウコソの終焉
	if (startTimer == TranStart && DeleteFlag == false) {
		m_spriteRender[12]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		if (NowGamen == false) {
			commandTren();
		}
		else {
			commandTren_Skill();
		}
	}

	//うごくも
	KumoMove();
	//矢印
	YazirusiSupporter();

	//遷移処理
	if (SkillSetMoveTimer > -1) {
		if (SkillSetMoveTimer < MaxSeniMove) {
			KaiwaNow = -1;
			if (NowGamen == false) {
				GamenChange(true);
			}
			else {
				GamenChange(false);
			}
		}
		SkillSetMoveTimer++;
		if (SkillSetMoveTimer >= MaxSeniMove + 20) {
			SkillSetMoveTimer = -1;
			if (NowGamen == false) {
				CommandUpdate();
				commandTren();
			}
			else {
				CommandUpdate_Skill();
				commandTren_Skill();
			}
		}
	}

	//たいま
	startTimer++;
}

void PlayerUpgrade::CommandUpdate() { //強化画面用コマンド更新

	//ジャンプフラグをオン
	jumpFlag = true;

	//数値を更新
	Point_keisan();
	wchar_t text[256];
	swprintf(text, L"%d", point);
	m_fontRender[0]->SetText(text);
	//////
	text[256];
	swprintf(text, L"ざんき:%d", zanki);
	m_fontRender[2]->SetText(text);
	text[256];
	if (zanki_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", zanki_Point);
	}
	else {
		zanki_Point = -1;
		swprintf(text, L"MAX");
	}
	m_fontRender[3]->SetText(text);
	text[256];
	//////
	swprintf(text, L"こうげき:%d", attack);
	m_fontRender[4]->SetText(text);
	text[256];
	if (attack_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", attack_Point);
	}
	else {
		attack_Point = -1;
		swprintf(text, L"MAX");
	}
	m_fontRender[5]->SetText(text);
	text[256];
	//////
	swprintf(text, L"じゅみょう:%d", jyumyo);
	m_fontRender[6]->SetText(text);
	text[256];
	if (jyumyo_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", jyumyo_Point);
	}
	else {
		jyumyo_Point = -1;
		swprintf(text, L"MAX");
	}
	m_fontRender[7]->SetText(text);

	//明るさを更新 コマンドが散らかりすぎでは？
	switch (CommandNow) {
	case 0://残機
		m_spriteRender[4]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[5]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_spriteRender[6]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[2]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		if (zanki_Point <= point) {
			m_fontRender[3]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		}
		else {
			m_fontRender[3]->SetColor({ 0.5f,0.3f,0.3f,1.0f });
		}
		m_fontRender[4]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[5]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[6]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[7]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		break;
	case 1://攻撃
		m_spriteRender[4]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_spriteRender[5]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[6]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[2]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[3]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[4]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		if (attack_Point <= point) {
			m_fontRender[5]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		}
		else {
			m_fontRender[5]->SetColor({ 0.5f,0.3f,0.3f,1.0f });
		}
		m_fontRender[6]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[7]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		break;
	case 2://寿命
		m_spriteRender[4]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_spriteRender[5]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_spriteRender[6]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_fontRender[2]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[3]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[4]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[5]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[6]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		if (jyumyo_Point <= point) {
			m_fontRender[7]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		}
		else {
			m_fontRender[7]->SetColor({ 0.5f,0.3f,0.3f,1.0f });
		}
		break;
	}

}
void PlayerUpgrade::CommandJump() { //強化画面用コマンドジャンプ
	
	if (jumpTimer == 0) {//念のためリセット
		m_spriteRender[4]->SetPosition({ wakuPosDEF_X,wakuPosDefY*2.0f,0.0f });
		m_spriteRender[5]->SetPosition({ wakuPosDEF_X,wakuPosDefY ,0.0f });
		m_spriteRender[6]->SetPosition({ wakuPosDEF_X,0.0f ,0.0f });
		m_fontRender[2]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f + statusPosY });
		m_fontRender[3]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f - 15.0f});
		m_fontRender[4]->SetPosition({ wakuPosDEF_X, wakuPosDefY + statusPosY});
		m_fontRender[5]->SetPosition({ wakuPosDEF_X, wakuPosDefY - 15.0f});
		m_fontRender[6]->SetPosition({ wakuPosDEF_X, statusPosY });
		m_fontRender[7]->SetPosition({ wakuPosDEF_X,-15.0f });;
	}

	float hoge = 0.0f;
	if (jumpTimer < 3) {
		hoge = +2.0f;
	}
	else {
		hoge = -2.0f;
	}

	CVector3 pos = CVector3::Zero;
	CVector2 pos2 = CVector2::Zero;

	switch (CommandNow) {
	case 0://残機
		pos = m_spriteRender[4]->GetPosition();
		pos.y += hoge;
		m_spriteRender[4]->SetPosition(pos);
		pos2 = m_fontRender[2]->GetPosition();
		pos2.y += hoge;
		m_fontRender[2]->SetPosition(pos2);
		pos2 = m_fontRender[3]->GetPosition();
		pos2.y += hoge;
		m_fontRender[3]->SetPosition(pos2);
		break;
	case 1://攻撃
		pos = m_spriteRender[5]->GetPosition();
		pos.y += hoge;
		m_spriteRender[5]->SetPosition(pos);
		pos2 = m_fontRender[4]->GetPosition();
		pos2.y += hoge;
		m_fontRender[4]->SetPosition(pos2);
		pos2 = m_fontRender[5]->GetPosition();
		pos2.y += hoge;
		m_fontRender[5]->SetPosition(pos2);
		break;
	case 2://寿命
		pos = m_spriteRender[6]->GetPosition();
		pos.y += hoge;
		m_spriteRender[6]->SetPosition(pos);
		pos2 = m_fontRender[6]->GetPosition();
		pos2.y += hoge;
		m_fontRender[6]->SetPosition(pos2);
		pos2 = m_fontRender[7]->GetPosition();
		pos2.y += hoge;
		m_fontRender[7]->SetPosition(pos2);
		break;
	}

	jumpTimer++;
	if (jumpTimer == 6) {
		jumpTimer = 0;
		jumpFlag = false;
	}
}
void PlayerUpgrade::CommandShake() { //強化画面用コマンドシェイク

	float hoge = 0.0f;
	static int S_Timer = 0;

	if (buruTimer == 0) {//念のためリセット
		m_spriteRender[4]->SetPosition({ wakuPosDEF_X,wakuPosDefY*2.0f,0.0f });
		m_spriteRender[5]->SetPosition({ wakuPosDEF_X,wakuPosDefY ,0.0f });
		m_spriteRender[6]->SetPosition({ wakuPosDEF_X,0.0f ,0.0f });
		m_fontRender[2]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f + statusPosY });
		m_fontRender[3]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f - 15.0f });
		m_fontRender[4]->SetPosition({ wakuPosDEF_X, wakuPosDefY + statusPosY });
		m_fontRender[5]->SetPosition({ wakuPosDEF_X, wakuPosDefY - 15.0f });
		m_fontRender[6]->SetPosition({ wakuPosDEF_X, statusPosY });
		m_fontRender[7]->SetPosition({ wakuPosDEF_X,-15.0f });
		hoge = -4.0f;
	}
	else {
		if (S_Timer % 2 == 0) {
			//偶数
			hoge = 8.0f;
		}
		else {
			//奇数
			hoge = -8.0f;
		}
		S_Timer++;
	}

	CVector3 pos = CVector3::Zero;
	CVector2 pos2 = CVector2::Zero;

	switch (CommandNow) {
	case 0://残機
		pos = m_spriteRender[4]->GetPosition();
		pos.x += hoge;
		m_spriteRender[4]->SetPosition(pos);
		pos2 = m_fontRender[2]->GetPosition();
		pos2.x += hoge;
		m_fontRender[2]->SetPosition(pos2);
		pos2 = m_fontRender[3]->GetPosition();
		pos2.x += hoge;
		m_fontRender[3]->SetPosition(pos2);
		break;
	case 1://攻撃
		pos = m_spriteRender[5]->GetPosition();
		pos.x += hoge;
		m_spriteRender[5]->SetPosition(pos);
		pos2 = m_fontRender[4]->GetPosition();
		pos2.x += hoge;
		m_fontRender[4]->SetPosition(pos2);
		pos2 = m_fontRender[5]->GetPosition();
		pos2.x += hoge;
		m_fontRender[5]->SetPosition(pos2);
		break;
	case 2://寿命
		pos = m_spriteRender[6]->GetPosition();
		pos.x += hoge;
		m_spriteRender[6]->SetPosition(pos);
		pos2 = m_fontRender[6]->GetPosition();
		pos2.x += hoge;
		m_fontRender[6]->SetPosition(pos2);
		pos2 = m_fontRender[7]->GetPosition();
		pos2.x += hoge;
		m_fontRender[7]->SetPosition(pos2);
		break;
	}

	buruTimer++;
	if (buruTimer == 6) {
		buruTimer = 0;
		buruFlag = false;
		S_Timer = 0;
		m_spriteRender[4]->SetPosition({ wakuPosDEF_X,wakuPosDefY*2.0f,0.0f });
		m_spriteRender[5]->SetPosition({ wakuPosDEF_X,wakuPosDefY ,0.0f });
		m_spriteRender[6]->SetPosition({ wakuPosDEF_X,0.0f ,0.0f });
		m_fontRender[2]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f + statusPosY });
		m_fontRender[3]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f - 15.0f });
		m_fontRender[4]->SetPosition({ wakuPosDEF_X, wakuPosDefY + statusPosY });
		m_fontRender[5]->SetPosition({ wakuPosDEF_X, wakuPosDefY - 15.0f });
		m_fontRender[6]->SetPosition({ wakuPosDEF_X, statusPosY });
		m_fontRender[7]->SetPosition({ wakuPosDEF_X,-15.0f });
	}
}

void PlayerUpgrade::CommandUpdate_Skill() { //スキル画面用コマンド更新

	if (NowGamen == true) {
		//ジャンプフラグをオン
		jumpFlag_s = true;
	}

	//数値を更新
	wchar_t text[256];
	SaveData * savedata = SaveData::GetInstance();
	//画像位置計算用
	int S_Waku = 0;

	for (int P=0; P < 3; P++) {
		if (savedata->SkillGetFlag_Get(NowSelectSkill+P) == true) { //持ってる～～
			 //枠を更新する！
			if (Skill_Data[NowSelectSkill + P].StarPower > 0) { //発動型
				m_spriteRender_skill[S_Waku]->Init(L"sprite/skillwaku_Red.dds", 400.0f, 140.0f);
			}
			else { //パッシブスキル
				m_spriteRender_skill[S_Waku]->Init(L"sprite/skillwaku_Blue.dds", 400.0f, 140.0f);
			}
			//名前の取得
			for (int i = 0; i < 256; i++) { //リセット
				text[i] = Reset[0];
			}
			int len = (int)wcslen(Skill_Data[NowSelectSkill + P].SkillName);
			for (int z = 0; z < len + 1; z++) { //名前の取得
				text[z] = Skill_Data[NowSelectSkill + P].SkillName[z];
			}
			swprintf(text, text);
			//はい。
			m_fontRender_skill[S_Waku]->SetText(text);
			//説明文を引っ張ってくる
			for (int i = 0; i < 256; i++) { //リセット
				text[i] = Reset[0];
			}
			len = (int)wcslen(Skill_Data[NowSelectSkill + P].SkillSetumei);
			for (int z = 0; z < len + 1; z++) { //名前の取得
				text[z] = Skill_Data[NowSelectSkill + P].SkillSetumei[z];
			}
			swprintf(text, text);
			//はい。
			m_fontRender_skill[S_Waku+1]->SetText(text);
			//設定フラグ確認
			if (savedata->GetSkill(false) == NowSelectSkill + P) { //Yに設定済み
				m_spriteRender_skill[S_Waku + 1]->Init(L"sprite/skillwakuUnder_Y.dds", 400.0f, 140.0f);
			}
			else if (savedata->GetSkill(true) == NowSelectSkill + P) { //Xに設定済み
				m_spriteRender_skill[S_Waku + 1]->Init(L"sprite/skillwakuUnder_X.dds", 400.0f, 140.0f);
			}
			else {
				m_spriteRender_skill[S_Waku + 1]->Init(L"sprite/skillwakuUnder_Null.dds", 400.0f, 140.0f);
			}
		}
		else { //持ってないんかい
			m_spriteRender_skill[S_Waku]->Init(L"sprite/skillwaku_Gray.dds", 400.0f, 140.0f);
			for (int i = 0; i < 256; i++) { //リセット
				text[i] = Reset[0];
			}
			swprintf(text, L"？？？？？");
			m_fontRender_skill[S_Waku]->SetText(text);
			//ヒント文を引っ張ってくる
			for (int i = 0; i < 256; i++) { //リセット
				text[i] = Reset[0];
			}
			int len = (int)wcslen(Skill_Data[NowSelectSkill+P].SkillHint);
			for (int z = 0; z < len + 1; z++) { //名前の取得
				text[z] = Skill_Data[NowSelectSkill+P].SkillHint[z];
			}
			swprintf(text, text);
			//はい。
			m_fontRender_skill[S_Waku+1]->SetText(text);
			//アンダー部分は確定でNull
			m_spriteRender_skill[S_Waku+1]->Init(L"sprite/skillwakuUnder_Null.dds", 400.0f, 140.0f);
		}
		S_Waku += 2;
	}
	//枠更新
	if (savedata->GetSkill(false) == -1) { //スキル未設定
		m_spriteRender_skill[7]->Init(L"sprite/skillicon_0.dds", 150.0f, 100.0f);
	}
	else { //あった～～～
		for (int i = 0; i < 256; i++) { //リセット
			text[i] = Reset[0];
		}
		int len = (int)wcslen(Skill_Data[savedata->GetSkill(false)].SkillIcon);
		for (int z = 0; z < len + 1; z++) { //名前の取得
			text[z] = Skill_Data[savedata->GetSkill(false)].SkillIcon[z];
		}
		m_spriteRender_skill[7]->Init(text, 150.0f, 100.0f);
	}
	if (savedata->GetSkill(true) == -1) { //スキル未設定
		m_spriteRender_skill[9]->Init(L"sprite/skillicon_0.dds", 150.0f, 100.0f);
	}
	else { //あった～～～
		for (int i = 0; i < 256; i++) { //リセット
			text[i] = Reset[0];
		}
		int len = (int)wcslen(Skill_Data[savedata->GetSkill(true)].SkillIcon);
		for (int z = 0; z < len + 1; z++) { //名前の取得
			text[z] = Skill_Data[savedata->GetSkill(true)].SkillIcon[z];
		}
		m_spriteRender_skill[9]->Init(text, 150.0f, 100.0f);
	}

	if (NowGamen == true) { //これがないと初回表示時に明るさがァ！！！
		CVector4 MulC = { 0.0f,0.0f,0.0f,0.0f };
		//明るさを更新 コマンドが散らかりすぎでは？
		switch (NouSkillCursor) {
		case 0://一番上
			//見える部分
			MulC = m_spriteRender_skill[0]->GetMulColor();
			MulC.a = 1.0f;
			m_spriteRender_skill[0]->SetMulColor(MulC);
			MulC = m_spriteRender_skill[1]->GetMulColor();
			MulC.a = 1.0f;
			m_spriteRender_skill[1]->SetMulColor(MulC);
			MulC = m_fontRender_skill[0]->GetColor();
			MulC.a = 1.0f;
			m_fontRender_skill[0]->SetColor(MulC);
			MulC = m_fontRender_skill[1]->GetColor();
			MulC.a = 1.0f;
			m_fontRender_skill[1]->SetColor(MulC);
			//半透明ゾーン
			MulC = m_spriteRender_skill[2]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[2]->SetMulColor(MulC);
			MulC = m_spriteRender_skill[3]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[3]->SetMulColor(MulC);
			MulC = m_fontRender_skill[2]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[2]->SetColor(MulC);
			MulC = m_fontRender_skill[3]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[3]->SetColor(MulC);
			//
			MulC = m_spriteRender_skill[4]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[4]->SetMulColor(MulC);
			MulC = m_spriteRender_skill[5]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[5]->SetMulColor(MulC);
			MulC = m_fontRender_skill[4]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[4]->SetColor(MulC);
			MulC = m_fontRender_skill[5]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[5]->SetColor(MulC);

			break;
		case 1://真ん中
			//見える部分
			MulC = m_spriteRender_skill[2]->GetMulColor();
			MulC.a = 1.0f;
			m_spriteRender_skill[2]->SetMulColor(MulC);
			MulC = m_spriteRender_skill[3]->GetMulColor();
			MulC.a = 1.0f;
			m_spriteRender_skill[3]->SetMulColor(MulC);
			MulC = m_fontRender_skill[2]->GetColor();
			MulC.a = 1.0f;
			m_fontRender_skill[2]->SetColor(MulC);
			MulC = m_fontRender_skill[3]->GetColor();
			MulC.a = 1.0f;
			m_fontRender_skill[3]->SetColor(MulC);
			//半透明ゾーン
			MulC = m_spriteRender_skill[0]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[0]->SetMulColor(MulC);
			MulC = m_spriteRender_skill[1]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[1]->SetMulColor(MulC);
			MulC = m_fontRender_skill[0]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[0]->SetColor(MulC);
			MulC = m_fontRender_skill[1]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[1]->SetColor(MulC);
			//
			MulC = m_spriteRender_skill[4]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[4]->SetMulColor(MulC);
			MulC = m_spriteRender_skill[5]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[5]->SetMulColor(MulC);
			MulC = m_fontRender_skill[4]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[4]->SetColor(MulC);
			MulC = m_fontRender_skill[5]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[5]->SetColor(MulC);

			break;
		case 2://下
			//見える部分
			MulC = m_spriteRender_skill[4]->GetMulColor();
			MulC.a = 1.0f;
			m_spriteRender_skill[4]->SetMulColor(MulC);
			MulC = m_spriteRender_skill[5]->GetMulColor();
			MulC.a = 1.0f;
			m_spriteRender_skill[5]->SetMulColor(MulC);
			MulC = m_fontRender_skill[4]->GetColor();
			MulC.a = 1.0f;
			m_fontRender_skill[4]->SetColor(MulC);
			MulC = m_fontRender_skill[5]->GetColor();
			MulC.a = 1.0f;
			m_fontRender_skill[5]->SetColor(MulC);
			//半透明ゾーン
			MulC = m_spriteRender_skill[2]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[2]->SetMulColor(MulC);
			MulC = m_spriteRender_skill[3]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[3]->SetMulColor(MulC);
			MulC = m_fontRender_skill[2]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[2]->SetColor(MulC);
			MulC = m_fontRender_skill[3]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[3]->SetColor(MulC);
			//
			MulC = m_spriteRender_skill[0]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[0]->SetMulColor(MulC);
			MulC = m_spriteRender_skill[1]->GetMulColor();
			MulC.a = 0.5f;
			m_spriteRender_skill[1]->SetMulColor(MulC);
			MulC = m_fontRender_skill[0]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[0]->SetColor(MulC);
			MulC = m_fontRender_skill[1]->GetColor();
			MulC.a = 0.5f;
			m_fontRender_skill[1]->SetColor(MulC);

			break;
		}
	}

}
void PlayerUpgrade::CommandJump_Skill() { //スキル画面用コマンドジャンプ

	if (jumpTimer_s == 0) {//念のためリセット
		m_spriteRender_skill[0]->SetPosition({ wakuPosDEF_X_Skill,(wakuPosDefY_Skill*2.0f) + SkillY_Hosei,0.0f });
		m_spriteRender_skill[1]->SetPosition({ wakuPosDEF_X_Skill,(wakuPosDefY_Skill*2.0f) + SkillY_Hosei,0.0f });
		m_spriteRender_skill[2]->SetPosition({ wakuPosDEF_X_Skill,wakuPosDefY_Skill + SkillY_Hosei,0.0f });
		m_spriteRender_skill[3]->SetPosition({ wakuPosDEF_X_Skill,wakuPosDefY_Skill + SkillY_Hosei,0.0f });
		m_spriteRender_skill[4]->SetPosition({ wakuPosDEF_X_Skill,0.0f + SkillY_Hosei,0.0f });
		m_spriteRender_skill[5]->SetPosition({ wakuPosDEF_X_Skill,0.0f + SkillY_Hosei,0.0f });
		m_fontRender_skill[0]->SetPosition({ wakuPosDEF_X_Skill - 150.0f,(wakuPosDefY_Skill*2.0f) + 55.0f + SkillY_Hosei });
		m_fontRender_skill[1]->SetPosition({ wakuPosDEF_X_Skill - 130.0f,(wakuPosDefY_Skill*2.0f) + 18.0f + SkillY_Hosei });
		m_fontRender_skill[2]->SetPosition({ wakuPosDEF_X_Skill - 150.0f,wakuPosDefY_Skill + 55.0f + SkillY_Hosei });
		m_fontRender_skill[3]->SetPosition({ wakuPosDEF_X_Skill - 130.0f,wakuPosDefY_Skill + 18.0f + SkillY_Hosei });
		m_fontRender_skill[4]->SetPosition({ wakuPosDEF_X_Skill - 150.0f, 55.0f + SkillY_Hosei });
		m_fontRender_skill[5]->SetPosition({ wakuPosDEF_X_Skill - 130.0f, 18.0f + SkillY_Hosei });
	}

	float hoge = 0.0f;
	if (jumpTimer_s < 3) {
		hoge = +2.0f;
	}
	else {
		hoge = -2.0f;
	}

	CVector3 pos = CVector3::Zero;
	CVector2 pos2 = CVector2::Zero;

	switch (NouSkillCursor) {
	case 0://上
		pos = m_spriteRender_skill[0]->GetPosition();
		pos.y += hoge;
		m_spriteRender_skill[0]->SetPosition(pos);
		pos = m_spriteRender_skill[1]->GetPosition();
		pos.y += hoge;
		m_spriteRender_skill[1]->SetPosition(pos);
		pos2 = m_fontRender_skill[0]->GetPosition();
		pos2.y += hoge;
		m_fontRender_skill[0]->SetPosition(pos2);
		pos2 = m_fontRender_skill[1]->GetPosition();
		pos2.y += hoge;
		m_fontRender_skill[1]->SetPosition(pos2);
		break;
	case 1://中央
		pos = m_spriteRender_skill[2]->GetPosition();
		pos.y += hoge;
		m_spriteRender_skill[2]->SetPosition(pos);
		pos = m_spriteRender_skill[3]->GetPosition();
		pos.y += hoge;
		m_spriteRender_skill[3]->SetPosition(pos);
		pos2 = m_fontRender_skill[2]->GetPosition();
		pos2.y += hoge;
		m_fontRender_skill[2]->SetPosition(pos2);
		pos2 = m_fontRender_skill[3]->GetPosition();
		pos2.y += hoge;
		m_fontRender_skill[3]->SetPosition(pos2);

		break;
	case 2://下
		pos = m_spriteRender_skill[4]->GetPosition();
		pos.y += hoge;
		m_spriteRender_skill[4]->SetPosition(pos);
		pos = m_spriteRender_skill[5]->GetPosition();
		pos.y += hoge;
		m_spriteRender_skill[5]->SetPosition(pos);
		pos2 = m_fontRender_skill[4]->GetPosition();
		pos2.y += hoge;
		m_fontRender_skill[4]->SetPosition(pos2);
		pos2 = m_fontRender_skill[5]->GetPosition();
		pos2.y += hoge;
		m_fontRender_skill[5]->SetPosition(pos2);

		break;
	}

	jumpTimer_s++;
	if (jumpTimer_s == 6) {
		jumpTimer_s = 0;
		jumpFlag_s = false;
	}
}
void PlayerUpgrade::CommandShake_Skill() { //スキル画面用コマンドシェイク

	float hoge = 0.0f;
	static int S_Timer = 0;

	if (buruTimer_s == 0) {//念のためリセット
		m_spriteRender_skill[0]->SetPosition({ wakuPosDEF_X_Skill,(wakuPosDefY_Skill*2.0f) + SkillY_Hosei,0.0f });
		m_spriteRender_skill[1]->SetPosition({ wakuPosDEF_X_Skill,(wakuPosDefY_Skill*2.0f) + SkillY_Hosei,0.0f });
		m_spriteRender_skill[2]->SetPosition({ wakuPosDEF_X_Skill,wakuPosDefY_Skill + SkillY_Hosei,0.0f });
		m_spriteRender_skill[3]->SetPosition({ wakuPosDEF_X_Skill,wakuPosDefY_Skill + SkillY_Hosei,0.0f });
		m_spriteRender_skill[4]->SetPosition({ wakuPosDEF_X_Skill,0.0f + SkillY_Hosei,0.0f });
		m_spriteRender_skill[5]->SetPosition({ wakuPosDEF_X_Skill,0.0f + SkillY_Hosei,0.0f });
		m_fontRender_skill[0]->SetPosition({ wakuPosDEF_X_Skill - 150.0f,(wakuPosDefY_Skill*2.0f) + 55.0f + SkillY_Hosei });
		m_fontRender_skill[1]->SetPosition({ wakuPosDEF_X_Skill - 130.0f,(wakuPosDefY_Skill*2.0f) + 18.0f + SkillY_Hosei });
		m_fontRender_skill[2]->SetPosition({ wakuPosDEF_X_Skill - 150.0f,wakuPosDefY_Skill + 55.0f + SkillY_Hosei });
		m_fontRender_skill[3]->SetPosition({ wakuPosDEF_X_Skill - 130.0f,wakuPosDefY_Skill + 18.0f + SkillY_Hosei });
		m_fontRender_skill[4]->SetPosition({ wakuPosDEF_X_Skill - 150.0f, 55.0f + SkillY_Hosei });
		m_fontRender_skill[5]->SetPosition({ wakuPosDEF_X_Skill - 130.0f, 18.0f + SkillY_Hosei });
	}

	else {
		if (S_Timer % 2 == 0) {
			//偶数
			hoge = 4.0f;
		}
		else {
			//奇数
			hoge = -4.0f;
		}
		S_Timer++;
	}

	CVector3 pos = CVector3::Zero;
	CVector2 pos2 = CVector2::Zero;

	switch (NouSkillCursor) {
	case 0://上
		pos = m_spriteRender_skill[0]->GetPosition();
		pos.x += hoge;
		m_spriteRender_skill[0]->SetPosition(pos);
		pos = m_spriteRender_skill[1]->GetPosition();
		pos.x += hoge;
		m_spriteRender_skill[1]->SetPosition(pos);
		pos2 = m_fontRender_skill[0]->GetPosition();
		pos2.x += hoge;
		m_fontRender_skill[0]->SetPosition(pos2);
		pos2 = m_fontRender_skill[1]->GetPosition();
		pos2.x += hoge;
		m_fontRender_skill[1]->SetPosition(pos2);
		break;
	case 1://中央
		pos = m_spriteRender_skill[2]->GetPosition();
		pos.x += hoge;
		m_spriteRender_skill[2]->SetPosition(pos);
		pos = m_spriteRender_skill[3]->GetPosition();
		pos.x += hoge;
		m_spriteRender_skill[3]->SetPosition(pos);
		pos2 = m_fontRender_skill[2]->GetPosition();
		pos2.x += hoge;
		m_fontRender_skill[2]->SetPosition(pos2);
		pos2 = m_fontRender_skill[3]->GetPosition();
		pos2.x += hoge;
		m_fontRender_skill[3]->SetPosition(pos2);

		break;
	case 2://下
		pos = m_spriteRender_skill[4]->GetPosition();
		pos.x += hoge;
		m_spriteRender_skill[4]->SetPosition(pos);
		pos = m_spriteRender_skill[5]->GetPosition();
		pos.x += hoge;
		m_spriteRender_skill[5]->SetPosition(pos);
		pos2 = m_fontRender_skill[4]->GetPosition();
		pos2.x += hoge;
		m_fontRender_skill[4]->SetPosition(pos2);
		pos2 = m_fontRender_skill[5]->GetPosition();
		pos2.x += hoge;
		m_fontRender_skill[5]->SetPosition(pos2);

		break;
	}

	buruTimer_s++;
	if (buruTimer_s == 6) {
		buruTimer_s = 0;
		buruFlag_s = false;
		S_Timer = 0;
		m_spriteRender_skill[0]->SetPosition({ wakuPosDEF_X_Skill,(wakuPosDefY_Skill*2.0f) + SkillY_Hosei,0.0f });
		m_spriteRender_skill[1]->SetPosition({ wakuPosDEF_X_Skill,(wakuPosDefY_Skill*2.0f) + SkillY_Hosei,0.0f });
		m_spriteRender_skill[2]->SetPosition({ wakuPosDEF_X_Skill,wakuPosDefY_Skill + SkillY_Hosei,0.0f });
		m_spriteRender_skill[3]->SetPosition({ wakuPosDEF_X_Skill,wakuPosDefY_Skill + SkillY_Hosei,0.0f });
		m_spriteRender_skill[4]->SetPosition({ wakuPosDEF_X_Skill,0.0f + SkillY_Hosei,0.0f });
		m_spriteRender_skill[5]->SetPosition({ wakuPosDEF_X_Skill,0.0f + SkillY_Hosei,0.0f });
		m_fontRender_skill[0]->SetPosition({ wakuPosDEF_X_Skill - 150.0f,(wakuPosDefY_Skill*2.0f) + 55.0f + SkillY_Hosei });
		m_fontRender_skill[1]->SetPosition({ wakuPosDEF_X_Skill - 130.0f,(wakuPosDefY_Skill*2.0f) + 18.0f + SkillY_Hosei });
		m_fontRender_skill[2]->SetPosition({ wakuPosDEF_X_Skill - 150.0f,wakuPosDefY_Skill + 55.0f + SkillY_Hosei });
		m_fontRender_skill[3]->SetPosition({ wakuPosDEF_X_Skill - 130.0f,wakuPosDefY_Skill + 18.0f + SkillY_Hosei });
		m_fontRender_skill[4]->SetPosition({ wakuPosDEF_X_Skill - 150.0f, 55.0f + SkillY_Hosei });
		m_fontRender_skill[5]->SetPosition({ wakuPosDEF_X_Skill - 130.0f, 18.0f + SkillY_Hosei });

	}
}

//取得色々
void PlayerUpgrade::Setting() {

	GameData * gamedata = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();
	point = gamedata->GetPoint();
	zanki = gamedata->GetDEF_Zanki();
	attack = gamedata->GetATK();
	jyumyo = gamedata->GetDEF_Life();
	zanki_X = savedata->GetZanki_Upgrade();
	attack_X = savedata->GetAttack_Upgrade();
	jyumyo_X = savedata->GetLife_Upgrade();
	Point_keisan();
}

//引数に設定したテキストを喋るよ
void PlayerUpgrade::Transceiver(wchar_t text[256]) {

	static int len;
	if (TranTimer == 0) {//ぶっこむ
		TranFlag = true;
		for (int i = 0; i < 256; i++) {
			Message[i] = Reset[0];
		}
		len = (int)wcslen(text);
		for (int z = 0; z < len + 1; z++) {
			Message[z] = text[z];
		}
	}

	//表示
	ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/SE_Message.wav");
	ss->SetVolume(0.5f);
	ss->Play(false);
	wchar_t hoge[256] = L"";

	for (int n = 0; n < TranTimer+1; n++) {
		hoge[n] = Message[n];
	}

	swprintf(hoge, hoge);
	//はい。
	m_fontRender[8]->SetText(hoge);

	TranTimer++;
	if (TranTimer == len) {
		TranFlag = false;
		TranTimer = 0;
	}
}

void PlayerUpgrade::TransceiverStandby() {
	for (int i = 0; i < 256; i++) {
		Message[i] = Reset[0];
	}
	TranFlag = false;
	TranTimer = 0;
	T_Timer = 0;
}

void PlayerUpgrade::commandTren() {
	switch (CommandNow) {
	case 0://残機
		TransceiverStandby();
		Transceiver(L"アナタサマノ\nナカマ ヲ フヤシマス");
		break;
	case 1://攻撃
		TransceiverStandby();
		Transceiver(L"オソロシイ テキニ\nアタエル ダメージ ガ\nオオキクナリマス");
		break;
	case 2://寿命
		TransceiverStandby();
		Transceiver(L"ミジカイ イノチ ヲ\nノバシマショウ");
		break;
	}

}

void PlayerUpgrade::commandTren_Skill() {

	//コマンド位置のトランシーバー呼び出し
	wchar_t text[256];
	SaveData * savedata = SaveData::GetInstance();

	if (savedata->SkillGetFlag_Get(NowSelectSkill + NouSkillCursor) == true) { //持ってるならテキスト読み込み

		for (int i = 0; i < 256; i++) { //リセット
			text[i] = Reset[0];
		}
		int len = (int)wcslen(Skill_Data[NowSelectSkill + NouSkillCursor].SkillTran);
		for (int z = 0; z < len + 1; z++) { //名前の取得
			text[z] = Skill_Data[NowSelectSkill + NouSkillCursor].SkillTran[z];
		}

		TransceiverStandby();
		Transceiver(text);
	}
	else { //まだ持ってないスキルです
		TransceiverStandby();
		Transceiver(L"テニイレテ イナイ\nスキル デス");
	}
}

void PlayerUpgrade::A_ButtonUpdate() {
	switch (CommandNow) {
	case 0://残機
		m_spriteRender[10]->SetPosition({ -130.0f,wakuPosDefY*2.0f,0.0f });
		break;
	case 1://攻撃
		m_spriteRender[10]->SetPosition({ -130.0f,wakuPosDefY,0.0f });
		break;
	case 2://寿命
		m_spriteRender[10]->SetPosition({ -130.0f, 0.0f ,0.0f });
		break;
	}

}

void PlayerUpgrade::KumoMove() { //動きますよ蜘蛛が

	if (KumoTimer == 0) {
		Random = rand() % 4;
		int hoge = rand() % 2;
		if (hoge == 0) {
			KumoLimit = 60;
		}
		else if (hoge == 1) {
			KumoLimit = 30;
		}
		else if (hoge == 2) {
			KumoLimit = 12;
		}
	}
	CVector3 K_pos = m_spriteRender[11]->GetPosition();
	if (Random == 0) {//上へ
		K_pos.y += 0.2f;
		if (K_pos.y > KumoY_MAX) {
			K_pos.y = KumoY_MAX;
		}
	}
	else if (Random == 1) {//下へ
		K_pos.y -= 0.2f;
		if (K_pos.y < KumoY_MIN) {
			K_pos.y = KumoY_MIN;
		}

	}//待機

	m_spriteRender[11]->SetPosition(K_pos);

	KumoTimer++;

	if (KumoTimer == KumoLimit) {
		KumoTimer = -KumoInterval;
	}

}

void PlayerUpgrade::GamenChange(bool gamen) { //遷移演出！

	if (gamen == false) { //強化からスキル
		float Seni_XMove = SkillMoveX / (float)MaxSeniMove; //1フレームの移動距離を計算
		//見えるやつ
		for (int i = 0; i < m_spriteRender_skill.size(); i++) {
			CVector3 Hoge = m_spriteRender_skill[i]->GetPosition();
			Hoge.x -= Seni_XMove;
			m_spriteRender_skill[i]->SetPosition(Hoge);
			CVector4 Hoge2 = m_spriteRender_skill[i]->GetMulColor();
			Hoge2.a += 0.1f;
			if (i < 6) {
				if (Hoge2.a > 0.5f) {
					Hoge2.a = 0.5f;
				}
			}
			else {
				if (Hoge2.a > 1.0f) {
					Hoge2.a = 1.0f;
				}
			}
			m_spriteRender_skill[i]->SetMulColor(Hoge2);
		}
		for (int i = 0; i < m_fontRender_skill.size(); i++) {
			CVector2 Hoge = m_fontRender_skill[i]->GetPosition();
			Hoge.x -= Seni_XMove;
			m_fontRender_skill[i]->SetPosition(Hoge);
			CVector4 Hoge2 = m_fontRender_skill[i]->GetColor();
			Hoge2.a += 0.1f;
			if (Hoge2.a > 0.5f) {
				Hoge2.a = 0.5f;
			}
			m_fontRender_skill[i]->SetColor(Hoge2);
		}
		//みえんやつ
		for (int i = 4; i < 7; i++) {
			CVector3 Hoge = m_spriteRender[i]->GetPosition();
			Hoge.x -= Seni_XMove;
			m_spriteRender[i]->SetPosition(Hoge);
			CVector4 Hoge2 = m_spriteRender[i]->GetMulColor();
			Hoge2.a -= 0.5f;
			if (Hoge2.a < 0.0f) {
				Hoge2.a = 0.0f;
			}
			m_spriteRender[i]->SetMulColor(Hoge2);
		}
		for (int i = 0; i < 8; i++) {
			CVector2 Hoge = m_fontRender[i]->GetPosition();
			Hoge.x -= Seni_XMove;
			m_fontRender[i]->SetPosition(Hoge);
			CVector4 Hoge2 = m_fontRender[i]->GetColor();
			Hoge2.a -= 0.5f;
			if (Hoge2.a < 0.0f) {
				Hoge2.a = 0.0f;
			}
			m_fontRender[i]->SetColor(Hoge2);
		}
		//Aボタン
		CVector3 Hoge = m_spriteRender[10]->GetPosition();
		Hoge.x -= Seni_XMove;
		m_spriteRender[10]->SetPosition(Hoge);
		CVector4 Hoge2 = m_spriteRender[10]->GetMulColor();
		Hoge2.a -= 0.5f;
		if (Hoge2.a < 0.0f) {
			Hoge2.a = 0.0f;
		}
		m_spriteRender[10]->SetMulColor(Hoge2);
		//死光虫の画像を左上へ持っていくZOY
		Hoge = m_spriteRender[3]->GetPosition();
		Hoge.x -= 29.0f;
		Hoge.y += 4.0f;
		m_spriteRender[3]->SetPosition(Hoge);

	}
	else { //スキルから強化
		float Seni_XMove = SkillMoveX / (float)MaxSeniMove; //1フレームの移動距離を計算
		//見えるやつ
		for (int i = 4; i < 7; i++) {
			CVector3 Hoge = m_spriteRender[i]->GetPosition();
			Hoge.x += Seni_XMove;
			m_spriteRender[i]->SetPosition(Hoge);
			CVector4 Hoge2 = m_spriteRender[i]->GetMulColor();
			if (SkillSetMoveTimer > MaxSeniMove - 3) { //可視化タイミングを遅らせる
				Hoge2.a += 0.5f;
			}
			if (Hoge2.a > 0.5f) {
				Hoge2.a = 0.5f;
			}
			m_spriteRender[i]->SetMulColor(Hoge2);
		}
		for (int i = 0; i < 8; i++) {
			CVector2 Hoge = m_fontRender[i]->GetPosition();
			Hoge.x += Seni_XMove;
			m_fontRender[i]->SetPosition(Hoge);
			CVector4 Hoge2 = m_fontRender[i]->GetColor();
			if (SkillSetMoveTimer > MaxSeniMove - 3) { //可視化タイミングを遅らせる
				Hoge2.a += 0.5f;
			}			if (i < 2) {
				if (Hoge2.a > 1.0f) {
					Hoge2.a = 1.0f;
				}
			}
			else {
				if (Hoge2.a > 0.5f) {
					Hoge2.a = 0.5f;
				}
			}
			m_fontRender[i]->SetColor(Hoge2);
		}
		//見えんやつ
		for (int i = 0; i < m_spriteRender_skill.size(); i++) {
			CVector3 Hoge = m_spriteRender_skill[i]->GetPosition();
			Hoge.x += Seni_XMove;
			m_spriteRender_skill[i]->SetPosition(Hoge);
			CVector4 Hoge2 = m_spriteRender_skill[i]->GetMulColor();
			Hoge2.a -= 0.1f;
			if (Hoge2.a < 0.0f) {
				Hoge2.a = 0.0f;
			}
			m_spriteRender_skill[i]->SetMulColor(Hoge2);
		}
		for (int i = 0; i < m_fontRender_skill.size(); i++) {
			CVector2 Hoge = m_fontRender_skill[i]->GetPosition();
			Hoge.x += Seni_XMove;
			m_fontRender_skill[i]->SetPosition(Hoge);
			CVector4 Hoge2 = m_fontRender_skill[i]->GetColor();
			Hoge2.a -= 0.1f;
			if (Hoge2.a < 0.0f) {
				Hoge2.a = 0.0f;
			}
			m_fontRender_skill[i]->SetColor(Hoge2);
		}
		//Aボタン
		CVector3 Hoge = m_spriteRender[10]->GetPosition();
		Hoge.x += Seni_XMove;
		m_spriteRender[10]->SetPosition(Hoge);
		CVector4 Hoge2 = m_spriteRender[10]->GetMulColor();
		if (SkillSetMoveTimer > MaxSeniMove - 3) { //可視化タイミングを遅らせる
			Hoge2.a += 0.5f;
		}
		if (Hoge2.a > 1.0f) {
			Hoge2.a = 1.0f;
		}
		m_spriteRender[10]->SetMulColor(Hoge2);
		//死光虫の画像を右下へ持っていくZOY
		Hoge = m_spriteRender[3]->GetPosition();
		Hoge.x += 29.0f;
		Hoge.y -= 4.0f;
		m_spriteRender[3]->SetPosition(Hoge);

	}

}

void PlayerUpgrade::YazirusiSupporter() { //上下左右矢印の移動と表示切替をする
	
	//準備
	CVector4 hoge;
	CVector3 hogePos;

	//シェイクする
	hogePos = m_spriteRender[13]->GetPosition();
	if (Ya_UpDownFlag == false) {
		hogePos.x += 0.2f;
	}
	else {
		hogePos.x -= 0.2f;
	}
	m_spriteRender[13]->SetPosition(hogePos);
	hogePos = m_spriteRender[14]->GetPosition();
	if (Ya_UpDownFlag == false) {
		hogePos.x += 0.2f;
	}
	else {
		hogePos.x -= 0.2f;
	}
	m_spriteRender[14]->SetPosition(hogePos);
	hogePos = m_spriteRender[15]->GetPosition();
	if (Ya_UpDownFlag == false) {
		hogePos.y += 0.2f;
	}
	else {
		hogePos.y -= 0.2f;
	}
	m_spriteRender[15]->SetPosition(hogePos);
	hogePos = m_spriteRender[16]->GetPosition();
	if (Ya_UpDownFlag == false) {
		hogePos.y -= 0.2f;
	}
	else {
		hogePos.y += 0.2f;
	}
	m_spriteRender[16]->SetPosition(hogePos);
	//タイマー加算
	if (Ya_UpDownTimer == 30) {
		Ya_UpDownFlag = true;
	}
	else if (Ya_UpDownTimer == 60) {
		Ya_UpDownTimer = -1;
		Ya_UpDownFlag = false;
	}
	Ya_UpDownTimer++;

	if (NowGamen == true && SkillSetMoveTimer == -1) {
		//XYが動く

		if (XY_Timer >= XY_Limit - 5) {
			hogePos = m_spriteRender_skill[10]->GetScale();
			hogePos.x -= 0.02f;
			hogePos.y -= 0.02f;
			m_spriteRender_skill[10]->SetScale(hogePos);
			hogePos = m_spriteRender_skill[11]->GetScale();
			hogePos.x -= 0.02f;
			hogePos.y -= 0.02f;
			m_spriteRender_skill[11]->SetScale(hogePos);
		}
		else if (XY_Timer >= XY_Limit - 10) {
			hogePos = m_spriteRender_skill[10]->GetScale();
			hogePos.x += 0.02f;
			hogePos.y += 0.02f;
			m_spriteRender_skill[10]->SetScale(hogePos);
			hogePos = m_spriteRender_skill[11]->GetScale();
			hogePos.x += 0.02f;
			hogePos.y += 0.02f;
			m_spriteRender_skill[11]->SetScale(hogePos);
		}

		XY_Timer++;
		if (XY_Timer == XY_Limit) {
			XY_Timer = 0;
		}
	}

	if (startTimer >= 72 && SkillSetMoveTimer == -1 && DeleteFlag == false) { //セットアップ中と遷移中はしない


		//右矢印は強化画面だけ
		if (NowGamen == false) {
			hoge = m_spriteRender[13]->GetMulColor();
			hoge.a += 0.1f;
			if (hoge.a > 1.0f) {
				hoge.a = 1.0f;
			}
			m_spriteRender[13]->SetMulColor(hoge);
		}
		else {
			hoge = m_spriteRender[13]->GetMulColor();
			hoge.a -= 0.1f;
			if (hoge.a < 0.0f) {
				hoge.a = 0.0f;
			}
			m_spriteRender[13]->SetMulColor(hoge);
		}
		//左上下はスキル画面だけ
		if (NowGamen == true) {
			hoge = m_spriteRender[14]->GetMulColor();
			hoge.a += 0.1f;
			if (hoge.a > 1.0f) {
				hoge.a = 1.0f;
			}
			m_spriteRender[14]->SetMulColor(hoge);
			//項目が一番上でなければ上矢印表示
			if (NowSelectSkill > 0) {
				m_spriteRender[15]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
			else {
				m_spriteRender[15]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
			}
			//項目が一番下でなければ下矢印表示
			if (NowSelectSkill < SkillKazu - 3) {
				m_spriteRender[16]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
			else {
				m_spriteRender[16]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
			}
		}
		else {
			hoge = m_spriteRender[14]->GetMulColor();
			hoge.a -= 0.1f;
			if (hoge.a < 0.0f) {
				hoge.a = 0.0f;
			}
			m_spriteRender[14]->SetMulColor(hoge);
			hoge = m_spriteRender[15]->GetMulColor();
			hoge.a -= 0.1f;
			if (hoge.a < 0.0f) {
				hoge.a = 0.0f;
			}
			m_spriteRender[15]->SetMulColor(hoge);
			hoge = m_spriteRender[16]->GetMulColor();
			hoge.a -= 0.1f;
			if (hoge.a < 0.0f) {
				hoge.a = 0.0f;
			}
			m_spriteRender[16]->SetMulColor(hoge);
		}
	}
	else{ //ぜんけし
		hoge = m_spriteRender[13]->GetMulColor();
		hoge.a -= 0.1f;
		if (hoge.a < 0.0f) {
			hoge.a = 0.0f;
		}
		m_spriteRender[13]->SetMulColor(hoge);
		hoge = m_spriteRender[14]->GetMulColor();
		hoge.a -= 0.1f;
		if (hoge.a < 0.0f) {
			hoge.a = 0.0f;
		}
		m_spriteRender[14]->SetMulColor(hoge);
		hoge = m_spriteRender[15]->GetMulColor();
		hoge.a -= 0.1f;
		if (hoge.a < 0.0f) {
			hoge.a = 0.0f;
		}
		m_spriteRender[15]->SetMulColor(hoge);
		hoge = m_spriteRender[16]->GetMulColor();
		hoge.a -= 0.1f;
		if (hoge.a < 0.0f) {
			hoge.a = 0.0f;
		}
		m_spriteRender[16]->SetMulColor(hoge);

	}

}