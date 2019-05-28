#pragma once
class PlayerUpgrade : public IGameObject
{
	static PlayerUpgrade* m_instance;
public:
	PlayerUpgrade();
	~PlayerUpgrade();
	bool Start();
	void Update();
private:
	
	void Setting();
	void CommandUpdate();
	void CommandJump();
	void CommandShake();
	void Transceiver(wchar_t text[256]);
	void TransceiverStandby();
	void commandTren();
	void A_ButtonUpdate();
	void KumoMove();

	void Point_keisan() { //����|�C���g���v�Z
		zanki_Point = 1000 + (1000 * zanki_X);
		attack_Point = 1000 + (1000 * attack_X);
		jyumyo_Point = 1000 + (1000 * jyumyo_X);
	}

	int CommandNow = 0;

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSoundSource* ss;

	int akariTimer = 0;
	int startTimer = 0;

	//����Jump
	bool jumpFlag = false;
	int jumpTimer = 0;
	
	//���ڐk����
	bool buruFlag = false;
	int buruTimer = 0;

	//�g�����V�[�o�[
	wchar_t Message[256]; //������e��ۑ�
	bool TranFlag = false;
	int TranTimer = 0;
	int T_Timer = 0;

	//�X�e�[�^�X
	int point = 0; //�����|�C���g
	int zanki = 0; //�c�@
	int attack = 0; //��������
	int jyumyo = 0; //����
	int zanki_X = 0; //�c�@������
	int attack_X = 0; //�U���͋�����
	int jyumyo_X = 0; //����������
	int zanki_Point = 0; //�c�@�����ɕK�v�ȃ|�C���g
	int attack_Point = 0;
	int jyumyo_Point = 0;

	float DEF_Mul = 0.4f; //�P�Ԃ̕s�����x
	float DEF_Mul2 = 0.0f; //�Q�Ԃ̕s�����x
	float Move_Hoge = 300.0f; //�ړ����钎

	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	//�X�e�[�^�XUP
	int StatusUpTimer = -1;
	float StatusUpAlpha = 1.0f;

	//Exit���o
	int E_MoveTimer = 0;
	bool E_MoveFlag = false;

	int A_Timer = 0;

	//�����w�
	int KumoTimer = 0;
	int Random = 0;
	int KumoLimit = 0;

	//���悤�Ȃ�
	bool DeleteFlag = false;
	int DeleteTimer = 0;

	//�萔
	const float Ypos_hoge = 720.0f; //Y�T�C�Y�i�֗��j
	const float wakuPosDefY = 140.0f; //�����g�̃|�W�V������
	const float wakuPosDEF_X = 40.0f; //�����g��X�|�W�V����
	const float statusPosY = 40.0f; //�����X�e�[�^�X�̃|�W�V������

	const int MAX_Upgrade = 10; //�ő勭����
	const int Zanki_Plus = 5; //1��̋����ŉ��Z�����c�@
	const int Attack_Plus = 20; //1��̋����ŉ��Z�����U��
	const int Life_Plus = 5; //1��̋����ŉ��Z�����c�@
	const int TranStart = 180; //�g�����V�[�o�[�̍X�V���n�܂�^�C�~���O
	const wchar_t Reset[1] = L"";
	const CVector2 StatusUP_DefPos = { 380.0f, 70.0f };
	const float KumoY_MAX = 380.0f; //�����w偂̍ő�ʒu
	const float KumoY_MIN = 300.0f; //�����w偂̍ŏ��ʒu
	const int KumoInterval = 60; //�w偂��܂������܂ł̎���
};

