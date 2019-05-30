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
	DeleteGO(m_fontRender);

}

bool Player_Status::Start() {

	//�����Q�[�W�y�� 0
	prefab::CSpriteRender* r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/StarBar_base.dds", 20.0f, 300.0f);
	CVector3 Position = { -550.0f, -10.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//�����Q�[�W 1
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/StarBar.dds", 20.0f, 300.0f);
	Position = { -550.0f, -160.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//�����Q�[�W�㕔�� 2
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/StarBarUe.dds", 20.0f, 300.0f);
	Position = { -550.0f, -10.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);


	//�����y�� 3
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/LifeBar_base.dds", 120.0f, 480.0f);
	Position = { -600.0f, -20.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//�o�[ 4
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/LifeBar.dds", 120.0f, 480.0f);
	Position = { -600.0f, -215.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//�����㕔�� 5
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/LifeBarUe.dds", 120.0f, 480.0f);
	Position = { -600.0f, -20.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);

	//�\�E���A�C�R�� 6
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/soulIC.dds", 100.0f, 100.0f);
	Position = { -600.0f, -220.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//�c�@�A���_�[ 7
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/Zanki.dds", 300.0f, 300.0f);
	Position = { -550.0f, 280.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);

	//�Q�[�W�}�b�N�X�A�C�R�� 8
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/starMax.dds", 150.0f, 100.0f);
	Position = { -480.0f, -150.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);

	m_fontRender = NewGO<prefab::CFontRender>(8);
	return true;

}

void Player_Status::Update() {

	CVector3 LifeScale = CVector3::Zero;
	CVector3 StarScale = CVector3::Zero;
	Player * player = Player::GetInstance();
	GameData * gamedata = GameData::GetInstance();

	//�����Q�[�W�𓮂���
	float DEF_Life = (float)gamedata->GetDEF_Life();
	float NOW_Life = (float)player->GetLife();

	//�����̊g�嗦���v�Z
	float LifeY = NOW_Life / DEF_Life;
	//LifeY *= 480.0f;
	LifeScale = { 1.0f,LifeY,1.0f };
	//�����o�[�̐F���ς���́H
	float RED_Life = DEF_Life / 2.0f;
	//�����o�[�̐F�ς�
	if (NOW_Life < RED_Life) {
		LifeColor = { 255.0f,0.5f,0.5f,1.0f };
	}else {
		LifeColor = { 1.0f,1.0f,1.0f,1.0f };
	}

	m_spriteRender[4]->SetPivot(LifePivot);
	m_spriteRender[4]->SetScale(LifeScale);
	m_spriteRender[4]->SetMulColor(LifeColor);

	//�����Q�[�W�𓮂���
	float NOW_StarPower = (float)gamedata->GetStar_Power();
	float DEF_StarPower = (float)gamedata->GetMAXStar_Power();

	//�Q�[�W�̊g�嗦���v�Z
	float StarY = NOW_StarPower / DEF_StarPower;
	StarScale = { 1.0f,StarY,1.0f };
	//�����o�[�̐F�ς�
	if (NOW_StarPower == DEF_StarPower) {
		StarColor = { 1.0f,1.0f,1.0f,1.0f };
		StarMaxFlag = true;
	}
	else {
		StarColor = { 0.5f,0.5f,255.0f,1.0f };
		StarMaxFlag = false;
	}

	m_spriteRender[1]->SetPivot(StarPivot);
	m_spriteRender[1]->SetScale(StarScale);
	m_spriteRender[1]->SetMulColor(StarColor);

	//�����Q�[�W�ɉ����Č������茩���Ȃ������肵��
	if (StarMaxFlag == true) {
		//�����違�_�ł���
		if (StarMaxColorFlag == false) {
			StarMaxColor += 0.05f;
			StarMaxScale += 0.01f;
			if (StarMaxColor > 2.0f) {
				StarMaxColor = 2.0f;
				StarMaxColorFlag = true;
			}
		}
		else if (StarMaxColorFlag == true) {
			StarMaxColor -= 0.05f;
			StarMaxScale -= 0.01f;
			if (StarMaxColor < 1.0f) {
				StarMaxColor = 1.0f;
				StarMaxColorFlag = false;
			}
			m_spriteRender[8]->SetMulColor({ StarMaxColor,StarMaxColor,StarMaxColor,0.8f });
			m_spriteRender[8]->SetScale({ StarMaxScale ,StarMaxScale ,StarMaxScale });
		}
	}
	else {
		//��\��
		m_spriteRender[8]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	}

	//�c�@���X�V
	wchar_t text[256];
	//����
	swprintf(text, L"%d", gamedata->GetZanki());
	//�͂��B
	m_fontRender->SetText(text);
	if (gamedata->GetZanki() <= 9) {
		m_fontRender->SetPosition({ ZankiPos.x + ZankiPosXHosei ,ZankiPos.y});
	}
	else {
		m_fontRender->SetPosition(ZankiPos);
	}
	m_fontRender->SetScale(ZankiScale);
	
}


