#pragma once
class TransitionMaker : public IGameObject
{
	static TransitionMaker* m_instance;
public:

	//�g�����W�V�����̎��
	enum Transition {
		Fade, //�t�F�[�h
		Toziru, //����
	};

	TransitionMaker();
	~TransitionMaker();
	bool Start();
	void Update();

	void TransitionSetting(Transition tran, int frame, int wait, bool flag);


	//�C���X�^���X�̎擾
	static TransitionMaker* TransitionMaker::GetInstance() {
		return m_instance;
	}

private:
	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CSpriteRender* r;

	int TransitionTimer = -1; //�g�����W�V�����p�^�C�}�[
	int TransitionLimit = -1; //�g�����W�V�����p��������
	int TransitionFrame = -1; //�g�����W�V�����̎��s�t���[��
	int TransitionWait = -1; //�g�����W�V�����̃E�F�C�g
	int TransitionNo = -1; //���s���̃g�����W�V����
	bool TransitionFlag = false; //false�Ȃ�\���Atrue�Ȃ����

	//���s�p
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	//�萔





	/*
	
	
�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�
�\�\�\�\�\�\�\�\�\�\�\�\�\�]����
�@�@�@�@�@�@�@�@ �@ �@   �@ |
�@�@ �Q�Q�Q�Q.�Q�Q�Q�Q�Q    |  �@.�Q�Q�@ ����Ȃ��o�b��
�@�@|�@ �@ �@ | �@ �@  �@|  |  �@|�_�Q�_�@�@������
�@�@|�@ �@ �@ |  �ȁQ�ȁ@|  |  �@| |.���b�@�����̂Ă�
�@�@|�@ �@ �@ |�i �L�́M�j��| �~ | |.�F�b
�@�@|�@ �@ �@ |/ ���@ Ɂ@|  |�@  �_|.�߁b
�@ �@�P�P�P�P'�P�P�P�P�@ �@ |�@�@�@ �P�P
	
	*/
};

