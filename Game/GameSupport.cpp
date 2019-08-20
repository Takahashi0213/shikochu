#include "stdafx.h"
#include "GameSupport.h"
#include "SaveData.h"
#include "GameData.h"

GameSupport* GameSupport::m_instance = nullptr;

GameSupport::GameSupport()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


GameSupport::~GameSupport()
{
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}

bool GameSupport::Start() {

	f = NewGO<prefab::CFontRender>(9);
	//表示
	text[256];
	//おわ
	swprintf(text, L"テストメッセージ");
	//はい。
	f->SetText(text);
	f->SetPosition(Def_MePos);
	f->SetScale(Me_Size);
	f->SetColor({ 1.0f,1.0f,1.0f,0.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);

	return true;
}

void GameSupport::Update() {

	GameData * gamedata = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();

	m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,0.0f }); //一度透明にします！

	if (gamedata->GetGameMode() != GameData::GameOver) {
		if (savedata->GetSupportFlag(0) == false) { //ダッシュで攻撃
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			text[256];
			//おわ
			swprintf(text, L"Aボタンでダッシュ しながら てきにたいあたり");
			//はい。
			m_fontRender[0]->SetText(text);
		}
		else if (savedata->GetSupportFlag(1) == false) { //りゅうせいダッシュ
			if (StarDashSupportFlag == true) { //表示する
				m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
				text[256];
				//おわ
				if (savedata->GetSkill(false) == 0) { //Yボタンに流星ダッシュがセットされている
					swprintf(text, L"Yボタンで りゅうせいダッシュ！");
				}else if (savedata->GetSkill(true) == 0) { //Xボタンに流星ダッシュがセットされている
					swprintf(text, L"Xボタンで りゅうせいダッシュ！");
				}
				else { //流星ダッシュがないだと
					swprintf(text, L"");
				}
				//はい。
				m_fontRender[0]->SetText(text);
			}
		}
		else if (savedata->GetSupportFlag(2) == false) { //加速しながら体当たりしてボスにダメージ
			if (gamedata->GetGameMode() == GameData::Battle3D_Mode) { //表示する
				m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
				text[256];
				//おわ
				swprintf(text, L"Aボタンでかそく しながら ボスにたいあたり");
				//はい。
				m_fontRender[0]->SetText(text);
			}
		}
		else if (savedata->GetSupportFlag(3) == false) { //Bで減速可能
			if (gamedata->GetGameMode() == GameData::Battle3D_Mode) { //表示する
				m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
				text[256];
				//おわ
				swprintf(text, L"Bボタンでげんそく できるぞ");
				//はい。
				m_fontRender[0]->SetText(text);
			}
		}
	}

	//フラグ管理
	if (savedata->GetSupportFlag(0) == false) {
		if (gamedata->GetGekihaEnemy() >= 4) { //敵を4体撃破したら終了
			savedata->SetSupportFlag(0);
		}
	}
	if (savedata->GetSupportFlag(1) == false) {
		if (gamedata->GetGameMode() == GameData::Battle3D_Mode) { //もし3Dモードならここはスキップ
			savedata->SetSupportFlag(1);
		}
		if (StarDashSupportFlag == false && gamedata->GetStar_Power() == 100) { //流星ゲージがマックスならフラグオン
			StarDashSupportFlag = true;
		}
		else if (StarDashSupportFlag == true && gamedata->GetStar_Power() != 100) { //流星ゲージがマックスじゃなくなれば終了
			savedata->SetSupportFlag(1);
		}
	}
	if (savedata->GetSupportFlag(2) == false) {
		if (gamedata->GetBossDamage() >= 1) { //ボスに1回ダメージを与えたら終了
			savedata->SetSupportFlag(2);
		}
	}
	if (savedata->GetSupportFlag(3) == false) {
		if (gamedata->GetBossDamage() >= 3) { //ボスに3回ダメージを与えたら終了
			savedata->SetSupportFlag(3);
		}
	}

}

