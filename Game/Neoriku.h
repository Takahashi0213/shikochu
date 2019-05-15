#pragma once
class Neoriku : public IGameObject
{
public:
	Neoriku();
	~Neoriku();

	enum Estete {
		Estete_Attack,  //�U��
		Estete_Move, //�ړ�
		Estete_Death, //��
		Estete_yobi	//�\������
	};

	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_move, //����
		enAnimationClip_attack, //�U��
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v

	};

	bool Start();
	void Update();

	void NeoAttack();
	void NeoMove();
	void NeoDeath();
	void Neoyobi();

	CVector3 Neoriku::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Neoriku::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Neoriku::SetDeath() {
		m_stete = Estete_Death;
		return 0;
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


private:
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	CVector3 moveVec;
	CVector3 neoVec;

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	const float followRange = 500.0f; //�ēx�ǔ����鋗���i�ǔ�����߂�܂ł̋����j
	const float followstop = 300.0f; //��~���鋗��(�߂����j
	const float followSpeed = 30.0f; //�ǔ��̑��x
	const float Speed = 0.0f; //�ǔ��̑��x
	//�\������֘A
	int timer = 0; //�U���J�n�܂ł̃^�C�}�[
	int count = 0; //�J�E���g


};

