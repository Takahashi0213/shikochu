#include "stdafx.h"
#include "shisokus.h"
#include "Player.h"


shisokus::shisokus()
{
}


shisokus::~shisokus()
{
}

bool shisokus::Start() {
	
	//�A�j���[�V����
	m_animClips[enAnimationClip_move].Load(L"animData/sisowalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);
	//�\��
	m_animClips[enAnimationClip_attack1].Load(L"animData/attack_1.tka");
	//�U��
	m_animClips[enAnimationClip_yobi1].Load(L"animData/attack_01.tka");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/shisokus.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->SetForwardRenderFlag(true);
	m_rotation.SetRotationDeg(CVector3::AxisY, -90.0f);
	m_position = { 0.0f,500.0f,3500.0f };
	m_skinModelRender->SetPosition(m_position);

	m_scale = { 10.0f,10.0f,10.0f };
	m_charaCon.Init(
		100.0f,  //�L�����N�^�[�̔��a�B
		300.0f,  //�L�����N�^�[�̍����B
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
	if (shisoVec.Length() < yobi1Range) {
		//�������߂��̂ŗ\������
		m_stete = Estete_Yobi1;
	}


	//�v���C���[�̌����ɉ�]
	CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, shisoVec);
	m_rotation = qRot;
	//m_position.m_charaCon.Execute(shisoVec);

}
void shisokus::shisoYobi1() {
	if (keisanflag == false) {
		m_skinModelRender->PlayAnimation(enAnimationClip_yobi1);
		yobitimer++;
		if (yobitimer <= yobiwait) {
			keisanflag = true;
		}
	}
	else {
		m_stete = Estete_Attack1;

	}
}
void shisokus::shisoAttack1() {
	m_skinModelRender->PlayAnimation(enAnimationClip_attack1);
}
void shisokus::shisoYobi2() {

}
void shisokus::shisoAttack2() {
	
}
void shisokus::shisoDeath() {
	//�������
	DeleteGO(this);
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
	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}

