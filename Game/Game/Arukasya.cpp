#include "stdafx.h"
#include "Player.h"
#include "Arukasya.h"


Arukasya::Arukasya()
{
}


Arukasya::~Arukasya()
{
}
bool Arukasya::Start() {

	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/Aruwalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//�\��
	m_animClips[enAnimationClip_back].Load(L"animData/Aruback.tka");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Arukasya.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);
	return true;
}

void Arukasya::AruAttack() {
	/*if (timecount > waittimer) {
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

	*/
}

void Arukasya::AruMove() {
	Player * player = Player::GetInstance();
	//�ʏ���
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;

	count++;

	if (count == randomCount) {
		random = rand() % 360;//�����_���ŕ���������
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 musi_mae = { 1.0f, 0.0f,0.0f };
		m_rotation.Multiply(musi_mae);
		moveVec = musi_mae * randomSpeed;
		count = 0;
		Attackcount++;
	}

	if (Attackcount > followRange) {
		//��萔�ȏ�ŗ\������Ɉڂ�B
		m_stete = Estete_Yobi;
	}
	if (m_stete == Estete_Move) {
		//stete��move�̂Ƃ��͕����A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}

}

void Arukasya::AruYobi() {
	/*timer++;
	if (timer < waittimer) {
		//�o�b�N�����
		moveVec = attackVec * back;
	}
	CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };
	//�v���C���[�̌����ɉ�]
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);
	*/
}
void Arukasya::AruDeath() {
	DeleteGO(this);
}

void Arukasya::Update() {
	switch (m_stete)
	{
	case Estete_Attack:
		AruAttack();
		break;
	case Estete_Move:
		AruMove();
		break;
	case Estete_Yobi:
		AruYobi();
		break;
	case Estete_Death:
		AruDeath();
		break;
	}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}