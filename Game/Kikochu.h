#pragma once
class Kikochu : public IGameObject
{
public:
	enum Estete {
		Estete_Move, //�ړ�
		Estete_Death, //��
		Estete_Death2, //��
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	Kikochu();
	~Kikochu();
	bool Start();
	void Update();

	//�|�W�V������Ԃ��֐�
	CVector3 Kikochu::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Kikochu::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Kikochu::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}

	//���������ʊ֐�2
	void Kikochu::SetDeath2() {
		m_stete = Estete_Death2;
	}

	//���W��ݒ�B
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	//��]��ݒ�B
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}
	//����Wave���Z�b�g
	void SetWave(int x) {
		waveNo = x;
	}
	//����Wave��Ԃ�
	int GetWave() {
		return waveNo;
	}

private:

	void Move();
	void Death();
	void Death2();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = { 1.0f,1.0f,1.0f }; // �g�嗦�B

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	CVector3 moveVec = CVector3::Zero;
	CVector3 diff = CVector3::Zero;
	
	int timer = 0;
	int EF_timer = 0;

	//�X�e�[�^�X
	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����
	const int Ef_Limit = 30; //�G�t�F�N�g���~�b�g
	const CVector3 SpawnEffectScale = { 40.0f,40.0f,40.0f }; //�X�|�[���G�t�F�N�g�̑傫��
	const float randomSpeed = 120.0f; //�ړ����x
	const int randomcount = 280; //�����]���̃^�C�~���O

	int waveNo = 0; //������������Wave�̔ԍ�

};

