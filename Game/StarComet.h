#pragma once
class StarComet : public IGameObject
{
	static StarComet* m_instance;
public:
	StarComet();
	~StarComet();

	//覐Δ��˃@�I
	//�������Ƀv���C���[�̈ړ����x���Ԃ����݂܂�
	//�������Ƀv���C���[�̌��ݍ��W�������݂܂�
	void Comet_Hassya(CVector3 PlayerMoveSpeed, CVector3 Player_Pos);

	//�C���X�^���X�̎擾
	static StarComet* StarComet::GetInstance() {
		return m_instance;
	}

};

