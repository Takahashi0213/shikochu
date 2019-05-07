#include "stdafx.h"
#include "Neoriku.h"


Neoriku::Neoriku()
{
}


Neoriku::~Neoriku()
{
	DeleteGO(m_skinModelRender);
}

bool Neoriku::Start() {
	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/Neowalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//m_animClips[enAnimationClip_attack1].SetLoopFlag(true);
	//�X�L�����f��
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/neoriku_0.cmo", m_animClips, enAnimationClip_Num);
	//m_position = { 100.0f,0.0f,0.0f };
	//m_skinModelRender->SetPosition(m_position);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		35.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);


	return true;
}

void Neoriku::NeoAttack() {
	//�U����

}

void Neoriku::NeoMove() {
	//�ړ���

}
void Neoriku::NeoDeath() {
	//����......��...

}
void Neoriku::Neoyobi() {
	//�\������


}

void Neoriku::Update() {
	switch (m_Neostete) {
	case Estete_Attack://�U��
		NeoAttack();
		break;
	case Estete_Move://�ړ�
		NeoMove();
		break;
	case Estete_Death:
		NeoDeath();//��
		break;
	case Estete_yobi:
		Neoyobi();//�\������
		break;
	}
	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}


