#include "stdafx.h"
#include "StageSelect.h"
#include "Game.h"
#include "GameData.h"
#include "LevelData.h"
#include "UICamera.h"
#include "SaveData.h"
#include "TransitionMaker.h"
#include "StageWait.h"
#include "PlayerUpgrade.h"
#include "Zukan.h"

StageSelect* StageSelect::m_instance = nullptr;
SaveData savedata;
GameData Gamedata;

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

	{
		FILE* fp = fopen("save.bin", "w");
		fwrite(&savedata, sizeof(savedata), 1, fp);
		fwrite(&Gamedata, sizeof(Gamedata), 1, fp);
		fclose(fp);
	}
	ss = NewGO<prefab::CSoundSource>(0);
	//SE再生
	ss->Init(L"sound/stageselect.wav");
	ss->SetVolume(2.0f);
	ss->Play(true);

	//準備
	DisableSpecialLigRange();
	NewGO<StageWait>(0,"stagewait");
	GameData * gamedata = GameData::GetInstance();
	SelectStageNow = gamedata->GetStageNo(); //ステージNoを取得するぜ
	SelectStageNow -= 1;
	SaveData * savedata = SaveData::GetInstance();
	MAX_Stage = savedata->GetClearedStage();
	MAX_Stage++;

	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_motion1].Load(L"animData/StageMini1.tka");
	m_animClips[enAnimationClip_motion1].SetLoopFlag(true);
	m_animClips[enAnimationClip_motion2].Load(L"animData/StageMini2.tka");
	m_animClips[enAnimationClip_motion2].SetLoopFlag(true);
	m_animClips[enAnimationClip_motion3].Load(L"animData/StageMini3.tka");
	m_animClips[enAnimationClip_motion3].SetLoopFlag(true);

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
	//2番 クリア済？
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Clear.dds", 640.0f/2, 200.0f/2);
	r->SetPosition({ 250.0f , -200.0f ,0.0f });
	m_spriteRender.push_back(r);
	//3番 START
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/start.dds", 146.0f, 72.0f);
	r->SetPosition({ 250.0f , -300.0f ,0.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//4番 強化ボタン
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Kyoka.dds", 403.0f, 288.0f);
	r->SetPosition({ 550.0f , 300.0f ,0.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//5番 図鑑ボタン
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Zukan.dds", 403.0f, 288.0f);
	r->SetPosition({ -550.0f , 300.0f ,0.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);

	//虫も出る…ムシモデル… 0番
	e = NewGO<prefab::CSkinModelRender>(10);
	e->Init(L"modelData/bug.cmo", nullptr, 0);
	e->SetPosition({ -100.0f,BugPosY,20.0f });
	e->SetScale(CVector3::One);	
	m_rotation.SetRotation(CVector3::AxisY, 3.1f);
	e->SetRotation(m_rotation);
	//e->SetEmissionColor({ 1.0f,0.5f,0.5f });
	m_skinModelRender.push_back(e);
	//背景 1番
	e = NewGO<prefab::CSkinModelRender>(0);
	e->Init(L"modelData/StageSelect_Back.cmo", nullptr, 0);
	e->SetPosition({ 0.0f,-50.0f,-1000.0f });
	e->SetScale({ 15.0f,15.0f,15.0f });
	e->SetRotation(CQuaternion::Identity);
	m_skinModelRender.push_back(e);

	/////////////////////////
	/////////箱並べ//////////
	/////////////////////////

	float HogePosZ = BoxPosDEF.z;

	int SettingCount = 0;
	//始点となる箱座標を決める
	while (SettingCount < SelectStageNow)
	{
		HogePosZ += BoXMoveZ;
		SettingCount++;
	}

	for (int i = 0; i < MAX_Stage; i++) {
		e = NewGO<prefab::CSkinModelRender>(0);
		int len = (int)wcslen(StageMiniName[i]);
		for (int z = 0; z < len + 1; z++) {
			BOX_Name[z] = StageMiniName[i][z];
		}
		e->Init(BOX_Name, m_animClips, enAnimationClip_Num);
		e->SetPosition({ BoxPosDEF.x,BoxPosDEF.y,HogePosZ });
		e->SetScale({ 4.0f,4.0f,3.0f });
		m_rotation.SetRotation(CVector3::AxisY, RotBox);
		e->SetRotation(m_rotation);
		e->PlayAnimation(i);
		m_skinModelRender.push_back(e);
		HogePosZ -= BoXMoveZ;
	}

	//ハイスコア 0番
	f = NewGO<prefab::CFontRender>(11);
	//表示
	wchar_t text[256];
	//おわ
	swprintf(text, L"11037");
	//はい。
	f->SetText(text);
	f->SetPosition({ -470.0f,-120.0f });
	f->SetScale(HighScoreFontSize);
	f->SetColor({ 0.2f,1.0f,0.2f,1.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//ステージ番号 1番
	f = NewGO<prefab::CFontRender>(11);
	//表示
	text[256];
	//おわ
	swprintf(text, L"STAGE 1");
	//はい。
	f->SetText(text);
	f->SetPosition({ 250.0f,150.0f });
	f->SetScale(StageFontSize);
	f->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//ステージ名 2番
	f = NewGO<prefab::CFontRender>(11);
	//表示
	text[256];
	//おわ
	swprintf(text, L"「これはテストメッセージ」");
	//はい。
	f->SetText(text);
	f->SetPosition({ 250.0f,70.0f });
	f->SetScale(StageNameFontSize);
	f->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);

	return true;
}

void StageSelect::Update(){

	if (SelectedFlag == true && KyokaFlag == false && ZukanFlag == false) {

		BMG_V -= 0.1f;
		if (BMG_V < 0.0f) {
			BMG_V = 0.0f;
		}
		ss->SetVolume(BMG_V);

		if (Selected_Counter < 14) {//くるりんぱ
			int x = 2 + SelectStageNow;
			RotBox += 0.4f;
			m_rotation.SetRotation(CVector3::AxisY, RotBox);
			m_skinModelRender[x]->SetRotation(m_rotation);
			m_skinModelRender[x]->SetPosition({ -100.0f,-100.0f,0.0f });
		}
		else if (Selected_Counter == 14) {
			int x = 2 + SelectStageNow;
			RotBox += 0.2f;
			m_rotation.SetRotation(CVector3::AxisY, RotBox);
			m_skinModelRender[x]->SetRotation(m_rotation);
			m_skinModelRender[x]->SetPosition({ -100.0f,-100.0f,0.0f });
		}
		else {
			int x = 2 + SelectStageNow;
			RotBox += 0.01f;
			m_rotation.SetRotation(CVector3::AxisY, RotBox);
			m_skinModelRender[x]->SetRotation(m_rotation);
			m_skinModelRender[x]->SetPosition({ -100.0f,-100.0f,0.0f });
		}
		//ステージ名バウンド
		if (Selected_Counter < 7) {//上に
			CVector2 pos = m_fontRender[1]->GetPosition();
			pos.y += 2.0f;
			m_fontRender[1]->SetPosition(pos);
			pos = m_fontRender[2]->GetPosition();
			pos.y += 2.0f;
			m_fontRender[2]->SetPosition(pos);
		}else if (Selected_Counter < 15) {//下に
			CVector2 pos = m_fontRender[1]->GetPosition();
			pos.y -= 2.0f;
			m_fontRender[1]->SetPosition(pos);
			pos = m_fontRender[2]->GetPosition();
			pos.y -= 2.0f;
			m_fontRender[2]->SetPosition(pos);
		}

		//遷移
		if (Selected_Counter == 60) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 0, false);
		}
		//アレ
		if (Selected_Counter == 80) {
			StageWait * sw = StageWait::GetInstance();
			sw->WaitSet(SelectStageNow);
		}
		//ボタンスタンバーイ
		if (Selected_Counter > 120) {
			if (StartFlag == false) {
				if (Pad(0).IsPress(enButtonA)) {
					StageWait * sw = StageWait::GetInstance();
					sw->WaitDelete();
					TransitionMaker * tm = TransitionMaker::GetInstance();
					tm->TransitionSetting(TransitionMaker::Toziru, 12, 30, true);
					StartFlag = true;
				}
			}
		}

		if (StartFlag == true) {
			if (StartCount == 30) {
				//れっつご
				NewGO<Game>(0, "Game");
				DeleteGOs("UICamera");
				DeleteGOs("stagewait");
				DeleteGO(this);
			}
			StartCount++;
		}

		Selected_Counter++;
	}
	else if (SelectedFlag == true && KyokaFlag == true) {//強化画面へ

		BMG_V -= 0.1f;
		if (BMG_V < 0.0f) {
			BMG_V = 0.0f;
		}
		ss->SetVolume(BMG_V);

		if (Selected_Counter < 25) {//選択アニメーション
			if (Selected_Counter < 7) {
				CVector3 scl = m_spriteRender[4]->GetScale();
				scl.x += 0.01f;
				scl.y += 0.01f;
				m_spriteRender[4]->SetScale(scl);
			}
			else if (Selected_Counter < 13) {
				CVector3 scl = m_spriteRender[4]->GetScale();
				scl.x -= 0.01f;
				scl.y -= 0.01f;
				m_spriteRender[4]->SetScale(scl);

			}
		}
		else if (Selected_Counter == 25) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 0, false);
		}
		else if (Selected_Counter == 40) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 10, true);
			NewGO<PlayerUpgrade>(0);
			DeleteGOs("stagewait");
			DeleteGO(this);
		}

		Selected_Counter++;
	}
	else if (SelectedFlag == true && ZukanFlag == true) {//図鑑画面へ

		BMG_V -= 0.1f;
		if (BMG_V < 0.0f) {
			BMG_V = 0.0f;
		}
		ss->SetVolume(BMG_V);

		if (Selected_Counter < 25) {//選択アニメーション
			if (Selected_Counter < 7) {
				CVector3 scl = m_spriteRender[5]->GetScale();
				scl.x += 0.01f;
				scl.y += 0.01f;
				m_spriteRender[5]->SetScale(scl);
			}
			else if (Selected_Counter < 13) {
				CVector3 scl = m_spriteRender[5]->GetScale();
				scl.x -= 0.01f;
				scl.y -= 0.01f;
				m_spriteRender[5]->SetScale(scl);

			}
		}
		else if (Selected_Counter == 25) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 0, false);
		}
		else if (Selected_Counter == 40) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 10, true);
			UICamera * UIcamera = UICamera::GetInstance();
			UIcamera->CameraFlag(true);
			NewGO<Zukan>(0);
			DeleteGOs("stagewait");
			DeleteGO(this);
		}

		Selected_Counter++;
	}
	else if (SelectedFlag == false) { //操作中のみ実行する

		//上下移動
		if (IdouFlag == false && TranTimer >= TranLimit) {
			if (Pad(0).IsTrigger(enButtonUp)) {
				if (SelectStageNow < MAX_Stage - 1) {
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/SS.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					SelectStageNow++;
					IdouFlag = true;
				}
			}
			if (Pad(0).IsTrigger(enButtonDown)) {
				if (SelectStageNow != 0) {
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/SS.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					SelectStageNow--;
					IdouFlag = true;
				}
			}

			//これでおけ
			if (Pad(0).IsTrigger(enButtonStart)) {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/stageStart.wav");
				ss->SetVolume(0.5f);
				ss->Play(false);

				SelectedFlag = true;
				GameData * gamedata = GameData::GetInstance();
				gamedata->SetStageNo(SelectStageNow+1); //ステージNoを決めるね
			}

			//強化画面へ…
			if (Pad(0).IsTrigger(enButtonRB1)) {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				//SE再生
				ss->Init(L"sound/kettei.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				SelectedFlag = true;
				KyokaFlag = true;
			}
			//図鑑画面へ…
			if (Pad(0).IsTrigger(enButtonLB1)) {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				//SE再生
				ss->Init(L"sound/kettei.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				SelectedFlag = true;
				ZukanFlag = true;
			}

		}

		//文章表示
		TextUpdate();

	}

	//上下する虫さん
	if (BugPosSet == false) {
		BugPosY -= 0.1f;
		if (BugPosY < -12.0f) {
			BugPosSet = true;
		}
	}
	else {
		BugPosY += 0.1f;
		if (BugPosY > -7.0f) {
			BugPosSet = false;
		}
	}
	m_skinModelRender[0]->SetPosition({ -100.0f,BugPosY,20.0f });

	//箱配置
	BoxUpdate();
	//スタート点滅
	STARTUpdate();

	TranTimer++;

}

void StageSelect::TextUpdate() {

	SaveData * savedata = SaveData::GetInstance();

	int highscore = savedata->GetHighScore(SelectStageNow);
	//ハイスコア更新
	wchar_t text[256];
	//おわ
	swprintf(text, L"%d", highscore);
	//はい。
	m_fontRender[0]->SetText(text);
	text[256];
	//おわ
	swprintf(text, L"STAGE %d", SelectStageNow+1);
	//はい。
	m_fontRender[1]->SetText(text);
	text[256];
	//おわ
	int len = (int)wcslen(StageName[SelectStageNow]);
	for (int z = 0; z < len + 1; z++) {
		text[z] = StageName[SelectStageNow][z];
	}
	swprintf(text, text);
	//はい。
	m_fontRender[2]->SetText(text);
	//クリア文字
	if (highscore > 0) {
		m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	}
	else {
		m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	}

}

void StageSelect::BoxUpdate() {
	//現在の位置と本来いるべき位置が違っていたらそこへ向かって移動するんだ！！！！！
	int Sansyo = 2; //参照する始点
	int SettingCount = 0;
	BoxPosZ = BoxPosDEF.z;
	CVector3 Hoge_Pos;

	//始点となる箱座標を決める
	while (SettingCount < SelectStageNow)
	{
		BoxPosZ += BoXMoveZ;
		SettingCount++;
	}

	for (int i = 0; i < MAX_Stage; i++) {

		//現在座標と本来いるべき座標を比べるﾝダブステップ
		Hoge_Pos = m_skinModelRender[Sansyo]->GetPosition();

		if (Hoge_Pos.z < BoxPosZ) { //Zが小さい
			Hoge_Pos.z += 10.0f;
			Hoge_Pos.y -= 10.0f;
			if (Hoge_Pos.y < BoXDownY) {
				Hoge_Pos.y = BoXDownY;
			}
			if (Hoge_Pos.z >= BoxPosZ) {
				Hoge_Pos.z = BoxPosZ;
			}
			m_skinModelRender[Sansyo]->SetPosition(Hoge_Pos);
		}
		else if (Hoge_Pos.z > BoxPosZ) { //Zが大きい
			Hoge_Pos.z -= 10.0f;
			Hoge_Pos.y -= 10.0f;
			if (Hoge_Pos.y < BoXDownY) {
				Hoge_Pos.y = BoXDownY;
			}
			if (Hoge_Pos.z <= BoxPosZ) {
				Hoge_Pos.z = BoxPosZ;
			}
			m_skinModelRender[Sansyo]->SetPosition(Hoge_Pos);
		}
		else if(Hoge_Pos.z == BoxPosZ&& Hoge_Pos.y < BoxPosDEF.y){
			Hoge_Pos.y += 10.0f;
			if (Hoge_Pos.y > BoxPosDEF.y) {
				Hoge_Pos.y = BoxPosDEF.y;
			}
			m_skinModelRender[Sansyo]->SetPosition(Hoge_Pos);
		}
		else {
			if (IdouFlag == true) {
				IdouFlag = false;
			}
		}

		//はい次
		BoxPosZ -= BoXMoveZ;
		Sansyo++;
	}

}

void StageSelect::STARTUpdate() {

	if (TenmetuTimer == 30) {
		m_spriteRender[3]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	}else if(TenmetuTimer==60){
		m_spriteRender[3]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		TenmetuTimer = -1;
	}

	TenmetuTimer++;
}