#pragma once
class Train2 : public IGameObject
{
public:
	Train2();
	~Train2();
	bool Start();
	void Update();

	//�|�W�V������Ԃ��֐�
	CVector3 Train2::Getm_Position() {
		return m_position;
	}

	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}

	//���W��ݒ�B
	void Train2::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	void Train2::SetSE_Flag(bool flag) {
		SE_Flag = flag;
	}


	void Train2::DeleteNow();

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_�[	

	CVector3 m_position = CVector3::Zero;	//���W�B
	CVector3 m_scale = { 5.0f,5.0f,5.0f };//�傫��
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B

	std::vector<prefab::CSoundSource*> m_soundRender;
	prefab::CSoundSource* ss;

	const float DamageLength = 800.0f; //�_�����[�W���󂯂���͔͈͂�����

	int Timer = 0;

	const float Speed = 200.0f;
	const int Limit = 1000;

	const int LoopLimit = 20; //�T�E���h�\�[�X�̐ݒu��
	const float TrainNagasa = 4000.0f; //�d�Ԃ̑S��
	CVector3 SE_Pos = CVector3::Zero;
	const float PosZHosei = 400.0f;

	bool SE_Flag = false;

};