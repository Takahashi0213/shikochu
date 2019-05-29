#include "stdafx.h"
#include "shisokus.h"
#include "Player.h"
#include "GameData.h"
#include "NerukGenerator.h"
#include "BossHPGage.h"

shisokus::shisokus()
{
}


shisokus::~shisokus()
{
	DeleteGO(m_skinModelRender);

}

bool shisokus::Start() {

	NewGO<NerukGenerator>(0, "nerukGenerator");

	//�A�j���[�V����
	m_animClips[enAnimationClip_move].Load(L"animData/sisowalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);
	//�\��
	m_animClips[enAnimationClip_yobi1].Load(L"animData/sesoyobi1.tka");
	//�U��
	m_animClips[enAnimationClip_attack1].Load(L"animData/sesoattack1.tka");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/shisokus.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->SetForwardRenderFlag(true);
	m_rotation.SetRotationDeg(CVector3::AxisY, -90.0f);

	m_skinModelRender->SetPosition(m_position);

	m_scale = { 10.0f,10.0f,10.0f };
	m_charaCon.Init(
		350.0f,  //�L�����N�^�[�̔��a�B
		100.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}
void shisokus::shisoMove() {
	//�{�X�������
	//������Ƃ����ړ������
	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	shisoVec = diff;
	//�����_���Ȏ��ԂōU�����郈
	if (count == 0) {
		random = rand() % 6;
		if (random >= 2) {
			count = 1;

		}
		random = random * time;//�����_������
	}
	timer++;
	if (timer > random) {
		attacktimer = 0;
		m_stete = Estete_Yobi1;
	}
	if (m_stete == Estete_Move) {
		//stete��move�̂Ƃ��͕����A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_move);

	}


	////�v���C���[�̌����ɉ�]
	//CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };
	//shisoVec.y = 0.0f;
	//shisoVec.Normalize();
	//CQuaternion qRot;
	//qRot.SetRotation(enemyForward, shisoVec);
	//m_rotation = qRot;
	//m_position = m_charaCon.Execute(shisoVec);

}
void shisokus::shisoYobi1() {

	if (keisanflag == false) {
		m_skinModelRender->PlayAnimation(enAnimationClip_yobi1);
		yobitimer++;
		if (yobitimer >= yobiwait) {
			keisanflag = true;
		}
	}
	else {
		m_stete = Estete_Attack1;

	}
}
void shisokus::shisoAttack1() {

	attacktimer++;
	if (attacktimer <= 60) {
		//�U���A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_attack1);

	}
	else {
		//�ʏ��Ԃɖ߂�
		count = 0;
		yobitimer = 0;
		timer = 0;
		keisanflag = false;
		m_stete = Estete_Move;
	}
}
void shisokus::shisoYobi2() {

}
void shisokus::shisoAttack2() {

}
void shisokus::shisoDeath() {
	//�������
	if (DeathTimer == 0) {
		//��Ԃ����U���g�ɁI
		GameData * gamedata = GameData::GetInstance();
		BossHPGage * bossHPGage = BossHPGage::GetInstance();
		gamedata->SetGameMode(GameData::Result);
		bossHPGage->DeleteGage();
		NerukGenerator * nerukGenerator = NerukGenerator::GetInstance();
		DeleteGO(nerukGenerator);
	}

	if (ToumeiTimeMAX == DeathTimer) {
		m_scale = CVector3::Zero;
	}

	if (DeathTimeMAX == DeathTimer) {
		GameData * gamedata = GameData::GetInstance();
		gamedata->EnemyCounterGensyou();
		DeleteGO(this);
	}

	DeathTimer++;
}

void shisokus::Update() {
	switch (m_stete) {
	case Estete_Move://�ړ�
		shisoMove();
		break;
	case Estete_Yobi1://�\������1
		shisoYobi1();
		break;
	case Estete_Attack1://�U��1
		shisoAttack1();
		break;
	case Estete_Yobi2://�\������2
		shisoYobi2();
		break;
	case Estete_Attack2://�U��2
		shisoAttack2();
		break;
	case Estete_Death://���
		shisoDeath();
		break;
	}
	//HP��0�Ȃ玀��
	if (NowHP == 0) {
		m_stete = Estete_Death;
	}
	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}
