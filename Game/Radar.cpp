#include "stdafx.h"
#include "Radar.h"
#include "GameData.h"
#include "SaveData.h"

#include "Player.h"

//エネミー
#include "Bunbogu.h"
#include "Neoriku.h"
#include "soukabuto.h"
#include "Ekku.h"
#include "Pi_rabi.h"
#include "Fairo.h"
#include "Morikon.h"
#include "Riritto.h"
#include "Arukasya.h"
#include "Uminoushi.h"
#include "Akoyadokari.h"
#include "Benite.h"
#include "Nibo.h"
#include "Sekuteimu.h"
#include "Kirabi.h"
#include "Suteira.h"
#include "Idando.h"
#include "Kodan.h"
#include "Taidol.h"
#include "Suroku.h"
#include "Mimitto.h"
#include "Tizutyo.h"
#include "Kuubo.h"
#include "Toripipi.h"
#include "Atsukaru.h"
#include "Metoporisu.h"

#include "Kikochu.h"

#include "StarItem.h"

Radar* Radar::m_instance = nullptr;

Radar::Radar()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


Radar::~Radar()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

	DeleteGO(m_skinModelRender);
}

bool Radar::Start() {

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0, "pointa");
	m_skinModelRender->Init(L"modelData/pointa.cmo", nullptr, 0, enFbxUpAxisZ, 1000);
	m_skinModelRender->SetEmissionColor({ 100.0f, 100.0f, 100.0f });
	return true;
}



void Radar::Update() {

	Player * player = Player::GetInstance();
	SaveData * savedata = SaveData::GetInstance();

	//ブンボーグとの距離を計算
	QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
		if (bunbogu->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position= player->Getm_Position();
		CVector3 enemy_position = bunbogu->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//クリオネとの距離を計算
	QueryGOs<Neoriku>("neo", [&](Neoriku* neoriku) {
		if (neoriku->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = neoriku->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//ソウカブトとの距離を計算
	QueryGOs<soukabuto>("sou", [&](soukabuto* souka) {
		if (souka->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = souka->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//エックとの距離を計算
	QueryGOs<Ekku>("Ekku", [&](Ekku* ekku) {
		if (ekku->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = ekku->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//ピーラビとの距離を計算
	QueryGOs<Pi_rabi>("Pi_rabi", [&](Pi_rabi* pi_rabi) {
		if (pi_rabi->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = pi_rabi->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//ファイロとの距離を計算
	QueryGOs<Fairo>("Fairo", [&](Fairo* fairo) {
		if (fairo->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = fairo->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//モリコンとの距離を計算
	QueryGOs<Morikon>("Morikon", [&](Morikon* morikon) {
		if (morikon->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = morikon->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//リリットとの距離を計算
	QueryGOs<Riritto>("Riritto", [&](Riritto* riritto) {
		if (riritto->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = riritto->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//アルカシャとの距離を計算
	QueryGOs<Arukasya>("Arukasya", [&](Arukasya* arukasya) {
		if (arukasya->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = arukasya->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//ウミノウシとの距離を計算
	QueryGOs<Uminoushi>("Uminoushi", [&](Uminoushi* uminoushi) {
		if (uminoushi->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = uminoushi->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//アコヤドカリとの距離を計算
	QueryGOs<Akoyadokari>("Akoyadokari", [&](Akoyadokari* akoyadokari) {
		if (akoyadokari->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = akoyadokari->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//ベニテーとの距離を計算
	QueryGOs<Benite>("Benite", [&](Benite* benite) {
		if (benite->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = benite->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//ニーボーとの距離を計算
	QueryGOs<Nibo>("Nibo", [&](Nibo* nibo) {
		if (nibo->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = nibo->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//セクティムとの距離を計算
	QueryGOs<Sekuteimu>("Sekuteimu", [&](Sekuteimu* sekuteimu) {
		if (sekuteimu->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = sekuteimu->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//キラビンとの距離を計算
	QueryGOs<Kirabi>("Kirabi", [&](Kirabi* kirabi) {
		if (kirabi->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = kirabi->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//スティラとの距離を計算
	QueryGOs<Suteira>("Suteira", [&](Suteira* suteira) {
		if (suteira->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = suteira->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//イーダンドとの距離を計算
	QueryGOs<Idando>("Idando", [&](Idando* idando) {
		if (idando->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = idando->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//コダンとの距離を計算
	QueryGOs<Kodan>("Kodan", [&](Kodan* kodan) {
		if (kodan->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = kodan->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//タイドルとの距離を計算
	QueryGOs<Taidol>("Taidol", [&](Taidol* taidol) {
		if (taidol->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = taidol->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//スロークとの距離を計算
	QueryGOs<Suroku>("Suroku", [&](Suroku* suroku) {
		if (suroku->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = suroku->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//ミミットとの距離を計算
	QueryGOs<Mimitto>("Mimitto", [&](Mimitto* mimitto) {
		if (mimitto->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = mimitto->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//チズチョウとの距離を計算
	QueryGOs<Tizutyo>("Tizutyo", [&](Tizutyo* tizutyo) {
		if (tizutyo->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = tizutyo->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//クーボとの距離を計算
	QueryGOs<Kuubo>("Kuubo", [&](Kuubo* kuubo) {
		if (kuubo->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = kuubo->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//トリピピとの距離を計算
	QueryGOs<Toripipi>("Toripipi", [&](Toripipi* toripipi) {
		if (toripipi->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = toripipi->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//アツカルとの距離を計算
	QueryGOs<Atsukaru>("Atsukaru", [&](Atsukaru* atsukaru) {
		if (atsukaru->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = atsukaru->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//メトポリスとの距離を計算
	QueryGOs<Metoporisu>("Metoporisu", [&](Metoporisu* metoporisu) {
		if (metoporisu->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = metoporisu->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		CVector3 RotHoge = diff;

		diff.Normalize();

		CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
		CQuaternion qRot;
		qRot.SetRotation(RadarForward, diff);

		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	if (player->GetNowSkill() == 22) { //キコサーチ中だけ
		QueryGOs<Kikochu>("Kikochu", [&](Kikochu* kikochu) {
			if (kikochu->IsActive() == false) {
				//Activeじゃない。
				return true;
			}
			CVector3 player_position = player->Getm_Position();
			CVector3 enemy_position = kikochu->Getm_Position();
			CVector3 diff = enemy_position - player_position;
			CVector3 RotHoge = diff;

			diff.Normalize();

			CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
			CQuaternion qRot;
			qRot.SetRotation(RadarForward, diff);

			diff *= 40.0f;

			CVector3 pointPos = player_position + diff;

			m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.2f, 0.2f, 0.2f });
			return true;
			});
	}

	if (savedata->GetSkill(false) == 23 || savedata->GetSkill(true) == 23) { //アイテムレーダー
		QueryGOs<StarItem>("Item", [&](StarItem* staritem) {
			if (staritem->IsActive() == false) {
				//Activeじゃない。
				return true;
			}
			CVector3 player_position = player->Getm_Position();
			CVector3 enemy_position = staritem->Getm_Position();
			CVector3 diff = enemy_position - player_position;
			CVector3 RotHoge = diff;

			diff.Normalize();

			CVector3 RadarForward = { 0.0f, 0.0f, 1.0f };
			CQuaternion qRot;
			qRot.SetRotation(RadarForward, diff);

			diff *= 30.0f;

			CVector3 pointPos = player_position + diff;

			m_skinModelRender->UpdateInstancingData(pointPos, qRot, { 0.1f, 0.1f, 0.1f });
			return true;
			});
	}

}
