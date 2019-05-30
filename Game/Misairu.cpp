#include "stdafx.h"
#include "Misairu.h"
#include "Player.h"
#include "EffectManager.h"

Misairu::Misairu()
{
}


Misairu::~Misairu()
{
	DeleteGO(m_skinModelRender);
}

bool Misairu::Start() {

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Misairu.cmo");

	m_scale = { 100.0f,100.0f,100.0f };
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	return true;
}

void Misairu::Update() {

	//�ړ����čU�����Ď���

	switch (m_stete) {
	case Estete_Move://�ړ�

		//���[�u�X�s�[�h������
		m_position += moveSpeed;

		//�����ړ����ԃ��~�b�g�Ȃ�
		if (Timer >= MoveLimit) {
			m_stete = Estete_Attack; //�U���I
			Timer = 0; //�^�C�}�[��0�ɂ���
		}

		break;
	case Estete_Attack://�U��
		if (Timer >= 10 && Timer < 120) {//�����҂��Ă���ړ��J�n
			Player* player = FindGO<Player>("Bug");
			int state = player->GetState();
			if (state != Player::Estate_Death) {
				CVector3 P_Position = player->Getm_Position();
				CVector3 diff = P_Position - m_position;
				atmove = diff;
				atmove.Normalize();

				CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };

				//�@���������������̃x�N�g�����v�Z����B
				CVector3 targetVector = P_Position - m_position;
				targetVector.Normalize();
				CQuaternion qRot;
				qRot.SetRotation(enemyForward, targetVector);
				m_rotation = qRot;
			}
		}

		m_position += atmove * AttackMoveSpeed;

		//�����U�����ԃ��~�b�g�Ȃ�
		if (Timer >= AttackLimit) {
			m_stete = Estete_Death; //�U���I
			Timer = 0; //�^�C�}�[��0�ɂ���
		}

		break;
	case Estete_Death://���

		//Effect�Đ�
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 30.0f,30.0f,30.0f });

		DeleteGO(this);

		break;
	}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);
	//�^�C�}�[���Z
	Timer++;

}