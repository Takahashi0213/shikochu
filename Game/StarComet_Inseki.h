#pragma once
class StarComet_Inseki : public IGameObject
{
public:
	StarComet_Inseki();
	~StarComet_Inseki();
	bool Start();
	void Update();

	//���W��ݒ�B
	void StarComet_Inseki::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	//�ړ����x��ݒ�B
	void StarComet_Inseki::SetMoveSpeed(CVector3 mov)
	{
		MoveSpeed = mov;
	}

	//���W��Ԃ�
	CVector3 StarComet_Inseki::Getm_Position() {
		return m_position;
	}

	//�_���[�W�͈͂�������֐�
	float StarComet_Inseki::GetDamageLength() {
		return DamageLength;
	}

	//���s������覐Δ����I
	void StarComet_Inseki::SetDeath() {
		DeleteTimer = DeleteLimit;
	}

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B
	CVector3 MoveSpeed = CVector3::Zero; //�ړ����x

	const float MoveHosei = 30.0f; //�ړ����x�␳

	short DeleteTimer = 0;
	const short DeleteLimit = 300; //�����܂ł̎���
	const float DamageLength = 80.0f;

};

