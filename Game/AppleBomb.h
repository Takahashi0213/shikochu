#pragma once
class AppleBomb : public IGameObject
{
public:
	AppleBomb();
	~AppleBomb();
	bool Start();
	void Update();

	enum Estete {
		Estete_Move,	//�ړ�
		Estete_Death,	 //���
		Estete_Death2,	 //���
	};
	enum EnAnimationClip {
		enAnimationClip_move, //����
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	//���W��ݒ�B
	void AppleBomb::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	//�ڕW���W��ݒ�B
	void AppleBomb::SetTargetPos(CVector3 pos)
	{
		Target_position = pos;
	}


	//�|�W�V������Ԃ��֐�
	CVector3 AppleBomb::Getm_Position() {
		return m_position;
	}
	//���������ʊ֐�
	void AppleBomb::SetDeath() {
		m_stete = Estete_Death;
	}
	//���������ʊ֐�2
	void AppleBomb::SetDeath2() {
		m_stete = Estete_Death2;
	}

	float GetDamageLength();

	//����Wave���Z�b�g
	void SetWave(int x) {
		waveNo = x;
	}
	//����Wave��Ԃ�
	int GetWave() {
		return waveNo;
	}

private:
	void AppleMove();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_�[	
	CVector3 m_scale = CVector3::One; // �g�嗦�B
	CVector3 m_position = CVector3::Zero;	//���W�B
	const float DamageLength = 50.0f; //�_�����[�W���󂯂���͔͈͂�����
	Estete m_stete = Estete_Move; //���
	int waveNo = 0; //������������Wave�̔ԍ�
	CVector3 Target_position = CVector3::Zero;	//�ڕW���W

	const float MoveSpeed = 50.0f;//�ړ����x

};

