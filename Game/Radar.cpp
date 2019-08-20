#include "stdafx.h"
#include "Radar.h"
#include "GameData.h"
#include "SaveData.h"

#include "Player.h"

//�G�l�~�[
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
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


Radar::~Radar()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
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

	//�u���{�[�O�Ƃ̋������v�Z
	QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
		if (bunbogu->IsActive() == false) {
			//Active����Ȃ��B
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

	//�N���I�l�Ƃ̋������v�Z
	QueryGOs<Neoriku>("neo", [&](Neoriku* neoriku) {
		if (neoriku->IsActive() == false) {
			//Active����Ȃ��B
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

	//�\�E�J�u�g�Ƃ̋������v�Z
	QueryGOs<soukabuto>("sou", [&](soukabuto* souka) {
		if (souka->IsActive() == false) {
			//Active����Ȃ��B
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

	//�G�b�N�Ƃ̋������v�Z
	QueryGOs<Ekku>("Ekku", [&](Ekku* ekku) {
		if (ekku->IsActive() == false) {
			//Active����Ȃ��B
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

	//�s�[���r�Ƃ̋������v�Z
	QueryGOs<Pi_rabi>("Pi_rabi", [&](Pi_rabi* pi_rabi) {
		if (pi_rabi->IsActive() == false) {
			//Active����Ȃ��B
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

	//�t�@�C���Ƃ̋������v�Z
	QueryGOs<Fairo>("Fairo", [&](Fairo* fairo) {
		if (fairo->IsActive() == false) {
			//Active����Ȃ��B
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

	//�����R���Ƃ̋������v�Z
	QueryGOs<Morikon>("Morikon", [&](Morikon* morikon) {
		if (morikon->IsActive() == false) {
			//Active����Ȃ��B
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

	//�����b�g�Ƃ̋������v�Z
	QueryGOs<Riritto>("Riritto", [&](Riritto* riritto) {
		if (riritto->IsActive() == false) {
			//Active����Ȃ��B
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

	//�A���J�V���Ƃ̋������v�Z
	QueryGOs<Arukasya>("Arukasya", [&](Arukasya* arukasya) {
		if (arukasya->IsActive() == false) {
			//Active����Ȃ��B
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

	//�E�~�m�E�V�Ƃ̋������v�Z
	QueryGOs<Uminoushi>("Uminoushi", [&](Uminoushi* uminoushi) {
		if (uminoushi->IsActive() == false) {
			//Active����Ȃ��B
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

	//�A�R���h�J���Ƃ̋������v�Z
	QueryGOs<Akoyadokari>("Akoyadokari", [&](Akoyadokari* akoyadokari) {
		if (akoyadokari->IsActive() == false) {
			//Active����Ȃ��B
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

	//�x�j�e�[�Ƃ̋������v�Z
	QueryGOs<Benite>("Benite", [&](Benite* benite) {
		if (benite->IsActive() == false) {
			//Active����Ȃ��B
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

	//�j�[�{�[�Ƃ̋������v�Z
	QueryGOs<Nibo>("Nibo", [&](Nibo* nibo) {
		if (nibo->IsActive() == false) {
			//Active����Ȃ��B
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

	//�Z�N�e�B���Ƃ̋������v�Z
	QueryGOs<Sekuteimu>("Sekuteimu", [&](Sekuteimu* sekuteimu) {
		if (sekuteimu->IsActive() == false) {
			//Active����Ȃ��B
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

	//�L���r���Ƃ̋������v�Z
	QueryGOs<Kirabi>("Kirabi", [&](Kirabi* kirabi) {
		if (kirabi->IsActive() == false) {
			//Active����Ȃ��B
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

	//�X�e�B���Ƃ̋������v�Z
	QueryGOs<Suteira>("Suteira", [&](Suteira* suteira) {
		if (suteira->IsActive() == false) {
			//Active����Ȃ��B
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

	//�C�[�_���h�Ƃ̋������v�Z
	QueryGOs<Idando>("Idando", [&](Idando* idando) {
		if (idando->IsActive() == false) {
			//Active����Ȃ��B
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

	//�R�_���Ƃ̋������v�Z
	QueryGOs<Kodan>("Kodan", [&](Kodan* kodan) {
		if (kodan->IsActive() == false) {
			//Active����Ȃ��B
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

	//�^�C�h���Ƃ̋������v�Z
	QueryGOs<Taidol>("Taidol", [&](Taidol* taidol) {
		if (taidol->IsActive() == false) {
			//Active����Ȃ��B
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

	//�X���[�N�Ƃ̋������v�Z
	QueryGOs<Suroku>("Suroku", [&](Suroku* suroku) {
		if (suroku->IsActive() == false) {
			//Active����Ȃ��B
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

	//�~�~�b�g�Ƃ̋������v�Z
	QueryGOs<Mimitto>("Mimitto", [&](Mimitto* mimitto) {
		if (mimitto->IsActive() == false) {
			//Active����Ȃ��B
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

	//�`�Y�`���E�Ƃ̋������v�Z
	QueryGOs<Tizutyo>("Tizutyo", [&](Tizutyo* tizutyo) {
		if (tizutyo->IsActive() == false) {
			//Active����Ȃ��B
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

	//�N�[�{�Ƃ̋������v�Z
	QueryGOs<Kuubo>("Kuubo", [&](Kuubo* kuubo) {
		if (kuubo->IsActive() == false) {
			//Active����Ȃ��B
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

	//�g���s�s�Ƃ̋������v�Z
	QueryGOs<Toripipi>("Toripipi", [&](Toripipi* toripipi) {
		if (toripipi->IsActive() == false) {
			//Active����Ȃ��B
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

	//�A�c�J���Ƃ̋������v�Z
	QueryGOs<Atsukaru>("Atsukaru", [&](Atsukaru* atsukaru) {
		if (atsukaru->IsActive() == false) {
			//Active����Ȃ��B
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

	//���g�|���X�Ƃ̋������v�Z
	QueryGOs<Metoporisu>("Metoporisu", [&](Metoporisu* metoporisu) {
		if (metoporisu->IsActive() == false) {
			//Active����Ȃ��B
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

	if (player->GetNowSkill() == 22) { //�L�R�T�[�`������
		QueryGOs<Kikochu>("Kikochu", [&](Kikochu* kikochu) {
			if (kikochu->IsActive() == false) {
				//Active����Ȃ��B
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

	if (savedata->GetSkill(false) == 23 || savedata->GetSkill(true) == 23) { //�A�C�e�����[�_�[
		QueryGOs<StarItem>("Item", [&](StarItem* staritem) {
			if (staritem->IsActive() == false) {
				//Active����Ȃ��B
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
