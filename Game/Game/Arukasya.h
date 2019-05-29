#pragma once
class Arukasya : public IGameObject
{
public:
	enum Estete {
		Estete_Attack,  //�U��
		Estete_Move, //�ړ�
		Estete_Yobi, //�\��
		Estete_Death, //��
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_back, //���
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	Arukasya();
	~Arukasya();

	void AruAttack();
	void AruMove();
	void AruYobi();
	void AruDeath();

	bool Start();
	void Update();

private:
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = { 30.0f,30.0f,30.0f }; // �g�嗦�B

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	CVector3 moveVec;
	//�ړ��֘A
	int count = 0;
	int random = 0;
	const float randomCount = 60.0f;
	const float randomSpeed = 30.0f;
	const float followRange = 4.0f;
	int Attackcount = 0;
	//�\���֘A

	//�U���֘A
	int timer = 0;
	const float waittimer = 30.0f;
};

