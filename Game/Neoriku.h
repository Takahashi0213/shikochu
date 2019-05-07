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


private:
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	Estete m_Neostete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

};

