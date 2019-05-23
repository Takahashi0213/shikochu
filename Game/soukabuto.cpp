#include "stdafx.h"
#include "Player.h"
#include "soukabuto.h"


soukabuto::soukabuto()
{
}


soukabuto::~soukabuto()
{
	DeleteGO(m_skinModelRender);
}

bool soukabuto::Start() {
	m_animClips[enAnimationClip_move].Load(L"animData/Neruwalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/soukabuto_0.cmo");

	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}
void soukabuto::Soumove(){

	timer++;
	if(timer == randomCount){
		random = rand() % 360;//�����_���ŕ���������
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 sou_mae = { -1.0f, 0.0f,0.0f };
		m_rotation.Multiply(sou_mae);
		moveVec = sou_mae * randomSpeed;
		movecount++;
		timer = 0;
	}
	else if (movecount >3) {
		//�U��������
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		diff = P_Position - m_position;
		attackVec = diff;
		attackVec.Normalize();

		timecount = 0;
		m_stete = Estete_Attack;
	}
	m_position = m_charaCon.Execute(moveVec);
}
void soukabuto::Souattack() {
	timecount++;
		if (timecount < waittimer) {
			//�o�b�N�����
			moveVec = attackVec * back;

		}
		else if (timecount > waittimer) {
			//�ːi��
			moveVec += attackVec * rush;

		}
		if (timecount > attacktime) {
			//�����_���ړ��ɖ߂�
			moveVec = attackVec * 0.0f;
			timer = 0;
			movecount = 0;
			m_stete = Estete_Move;
		}

	CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };
	//�v���C���[�̌����ɉ�]
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);

}
void soukabuto::Soudeath() {
	DeleteGO(this);
}
void soukabuto::Update() {
	switch (m_stete) {
	case Estete_Move://�ړ�
		Soumove();
		break;
	case Estete_Attack://�U��1
		Souattack();
		break;
	case Estete_Death://���
		Soudeath();
		break;
	}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}
