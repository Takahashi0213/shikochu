#include "stdafx.h"
#include "StarComet.h"
#include "StarComet_Inseki.h"

StarComet* StarComet::m_instance = nullptr;

StarComet::StarComet()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}


StarComet::~StarComet()
{	
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void StarComet::Comet_Hassya(CVector3 PlayerMoveSpeed, CVector3 Player_Pos) {

	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/Comet.wav");
	ss->SetVolume(1.0f);
	ss->Play(false);

	//�|�W�V�����ƈړ����x�̌v�Z
	PlayerMoveSpeed.Normalize();

	//覐ΐ���
	StarComet_Inseki*comet = NewGO<StarComet_Inseki>(0, "StarComet_Inseki");
	comet->SetPosition(Player_Pos);
	comet->SetMoveSpeed(PlayerMoveSpeed);
}
