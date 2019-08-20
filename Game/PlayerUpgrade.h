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
	void GamenChange(bool gamen); //false=��������X�L�� true=�X�L�����狭��
	void YazirusiSupporter(); //�㉺���E�T�|�[�g�����
	//��������X�L���Z�b�g�֘A
	void CommandUpdate_Skill();
	void CommandJump_Skill();
	void CommandShake_Skill();
	void commandTren_Skill();

	void Point_keisan() { //����|�C���g���v�Z
		zanki_Point = 200 + (100 * zanki_X);
		attack_Point = 200 + (100 * attack_X);
		jyumyo_Point = 200 + (100 * jyumyo_X);
	}

	int CommandNow = 0;

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	std::vector<prefab::CSpriteRender*> m_spriteRender_skill;
	std::vector<prefab::CFontRender*> m_fontRender_skill;

	prefab::CSpriteRender* r;
	prefab::CSpriteRender* skill_r;
	prefab::CFontRender* f;
	prefab::CFontRender* skill_f;
	prefab::CSoundSource* ss;

	int akariTimer = 0;
	int startTimer = 0;

	//����Jump
	bool jumpFlag = false;
	int jumpTimer = 0;
	bool jumpFlag_s = false;
	int jumpTimer_s = 0;

	//���ڐk����
	bool buruFlag = false;
	int buruTimer = 0;
	bool buruFlag_s = false;
	int buruTimer_s = 0;

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

	//��ʃt���O
	bool NowGamen = false; //false=�����Atrue=�X�L��

	//�����w�
	int KumoTimer = 0;
	int Random = 0;
	int KumoLimit = 0;

	//���㉺
	bool Ya_UpDownFlag = false;
	int Ya_UpDownTimer = 0;

	//����XY
	int XY_Timer = 0;

	//���悤�Ȃ�
	bool DeleteFlag = false;
	int DeleteTimer = 0;

	//�X�L���Z�b�g�֘A
	int NowSelectSkill = 0; //�X�L���J�[�\���ʒu
	int NouSkillCursor = 0; //��ʓ��̃J�[�\���ʒu�i0�`2�j
	int SkillSetMoveTimer = -1; //�X�L���J�ڗp�^�C�}�[�i���i��-1�j

	//�萔
	const float Ypos_hoge = 720.0f; //Y�T�C�Y�i�֗��j
	const float wakuPosDefY = 140.0f; //�����g�̃|�W�V������
	const float wakuPosDEF_X = 40.0f; //�����g��X�|�W�V����
	const float statusPosY = 40.0f; //�����X�e�[�^�X�̃|�W�V������

	const float wakuPosDefY_Skill = 140.0f; //�X�L���g�̃|�W�V������
	const float wakuPosDEF_X_Skill = 440.0f; //�X�L���g��X�|�W�V����
	const float statusPosY_Skill = 40.0f; //�X�L���̃|�W�V������
	const float SkillY_Hosei = -20.0f; //�����������������̂�
	const float SkillMoveX = 600.0f; //�X�L���g����\���̎���X�␳
	const int MaxSeniMove = 10; //��ʐ؂�ւ���������

	const int XY_Limit = 120; //XY�������܂ł̃^�C�}�[

	const int MAX_Upgrade = 25; //�ő勭����
	const int Zanki_Plus = 2; //1��̋����ŉ��Z�����c�@
	const int Attack_Plus = 6; //1��̋����ŉ��Z�����U��
	const int Life_Plus = 4; //1��̋����ŉ��Z��������
	const int TranStart = 180; //�g�����V�[�o�[�̍X�V���n�܂�^�C�~���O
	const wchar_t Reset[1] = L"";
	const CVector2 StatusUP_DefPos = { 380.0f, 70.0f };
	const float KumoY_MAX = 380.0f; //�����w偂̍ő�ʒu
	const float KumoY_MIN = 300.0f; //�����w偂̍ŏ��ʒu
	const int KumoInterval = 60; //�w偂��܂������܂ł̎���

	/////////////////////�G�k
	const int ZatsudanKazu = 25;
	int KaiwaNo = 0;
	int KaiwaTimer = 0;
	int KaiwaNow = -1;
	const int KaiwaLimit = 200;
	wchar_t Kaiwa[255];

	const int Zatudan_Kaisuu[25]{
	{ 3 },
	{ 2 },
	{ 2 },
	{ 2 },
	{ 3 },
	{ 2 },
	{ 3 },
	{ 2 },
	{ 2 },
	{ 3 },
	{ 3 },
	{ 3 },
	{ 2 },
	{ 3 },
	{ 3 },
	{ 3 },
	{ 2 },
	{ 3 },
	{ 2 },
	{ 3 },//20
	{ 3 },
	{ 2 },
	{ 2 },
	{ 3 },
	{ 3 },

	};

	const wchar_t Zatsudan_1[25][255]{
	{ L"�z�V�m �`�J���K\n�A�i�^�T�} ��\n�c���N�V�}�X" },
	{ L"�n���o�[�O�A\n�^�x�J�P�f�X�l..." },
	{ L"�N�� �n\n�j�K�e �i���f�X��" },
	{ L"�R�b�v �j �i�~�_ ��\n�C���X�M�}�V�^" },
	{ L"�A�i�^�T�} �n\n�C�m�`�g �q�L�J�G�j\n�i�j�� �G�}�V�^�J�H" },
	{ L"�n���[ �n���[\n�A�^���V�C �C�m�`..." },
	{ L"�A�i�^�T�} �m\n�C�m�`�n\n�J�M�����e�C�}�X" },
	{ L"�A�i�^�T�} �j\n�\�b�N�� �m\n���V �� �~�}�V�^��" },
	{ L"�Y�J�� �K���� �f\n�W���E�W�L�[ ��\n�T���E�j �E�S�J�X�g..." },
	{ L"�R�m�w�� �j�n\n�R���_�P�V�J\n�A���}�Z����" },
	{ L"���^�V�n �R�R�J��\n�E�S�P�i�C�m�f\n���J���}�Z���K..." },
	{ L"�I�h���J�i�C�f\n�L�C�e�N�_�T�C�l" },
	{ L"�C�m�` �n �V�k �g�L\n�A�I�C �q�J�� ��\n�n�i�c ���V�C�f�X" },
	{ L"���{�b�g �_�J��\n�g �C�b�e �T�x�c �n\n�C�P�}�Z����" },
	{ L"���E �W�J�� �K\n�i�C�m�f�X" },
	{ L"�V�k�R�g �K\n�R���C�m�f�X�J" },
	{ L"�E�^�n �g�N�C\n�i���f�X��\n�C�K�C �f�X�J�H" },
	{ L"�R�m �Z�J�C �n\n�n�R �f �f�L�e�C�}�X" },
	{ L"�n�[�h���[�h �f�V�J\n�A�G�i�C �����X�^�[ ��\n�C�}�X�l" },
	{ L"�V���f �R�\\n�g�E�g�C �C�m�` �f�X" },//20
	{ L"�i�C�]�E ��\n�i�C�]�E..." },
	{ L"�C�[�� �n\n�I�I�N�m �j���Q���K\n�R�R�j �L�e�C�}�V�^" },
	{ L"�}�X�^�[�n �n�R�j\n�X�E�W �� �c���R��\n�V�S�g�� �V�e�C�}�V�^" },
	{ L"�f���V�� �g�n\n�i���i�m�f�V���E�J" },
	{ L"�c�~�g �o�c�n\n�I�i�W���m �f�X��" },

	};

	const wchar_t Zatsudan_2[25][255]{
	{ L"�i�J�}�m �^�}�V�C�K\n�u�|�C���g�v�m\n�V���E�^�C �f�X" },
	{ L"�^�x������ ���m �n\n���E�C�i�C�m�f�X�K..." },
	{ L"�u�C�g�v�K\n�����}�Z���J���l\n...�N�� �_�P�j" },
	{ L"�^�}�j�n\n���t���b�V�� ��\n�q�c���E �f�X�l" },
	{ L"���^�V�n...\n�R�m�J���_ �f�X�J�l" },
	{ L"���^�V �K\n�E�}���^�g�L�m\n���b�Z�[�W �f�X" },
	{ L"�U�c�_�� ����\n���E�C�M �j\n�c�J�E�x�L �f�n�H" },
	{ L"�J�� ��\n�J�M�����^ �C�m�` �f\n�C�L�e�C���m �f�V���E�J" },
	{ L"�����X�^�[ �K\n�n���N �}�����}�X\n�O���O�� �}�����}�X" },
	{ L"�C�[���m ���^�V�K\n�J�^�d�P�^ ���E�f�X�l" },
	{ L"�\�g�m �Z�J�C�n\n�h�E�i�b�e\n�C���m�f�V���E" },
	{ L"���^�V �b�e �W�c�n...\n�j���Q�� �W��\n�A���}�Z���I" },
	{ L"���}���e�B�b�N\n�f�X���l\n�E�����}�V�C �f�X" },
	{ L"���^�V�� �I�R���Z���g\n�q�b�T�c ���U..." },
	{ L"���b�g �n���N\n�L�K �c�C�e�C���o\n�J�G�����^" },
	{ L"�J�^�`�K �J�����_�P\n�f�n �i�C�m�f�X�J" },
	{ L"�f�n �E�^�C�}�X\n�i�m�C�Y�� ��������j" },
	{ L"�n�R�� �T�O�� \n�q�r �K �Y�b�g\n�c�d�C�e�C�}�X" },
	{ L"�Y�J�� ��\n�J���Z�C �X���i��\n�T�P�e�n �g�I���}�Z��" },
	{ L"�V�i�i�C �m�i��\n�C�V�R�� �g\n�J�����}�Z��" },//20
	{ L"�j���Q�� ��\n�f�W�^�� �J �X���g\n�h�E�i���m�f�V���E" },
	{ L"�C�}�f�n �^�_�m\n�V�`���E�J�N �V�c\n�f�X�l" },
	{ L"�g�e�� �^�m�V�\�E�j\n�X�E�W�� �c���e�C�}�V�^" },
	{ L"�C�m�`�� �^�x��\n�I�\���V�C �J�C�u�c�g\n�L�C�e�C�}�X" },
	{ L"�z���j�� �m\n�C�V �i�h �J���P�C\n�A���}�Z��" },

	};

	const wchar_t Zatsudan_3[25][255]{
	{ L"���_�d�J�C �n\n�C�P�}�Z����\n�m�������}�X��" },
	{ L"" },
	{ L"" },
	{ L"" },
	{ L"�A�A�A���_�o�i�V�K\n�X�M�}�V�^\n�I�L�j �i�T���Y" },
	{ L"" },
	{ L"���^�V�K\n�C�G�^�R�g �f�n\n�A���}�Z���K" },
	{ L"" },
	{ L"" },
	{ L"�W���Z�C �m �J�^�d�P\n�b�e ���c�f�X�l" },
	{ L"�_���� �C�i�C�H\n...�S�W���E�_�� ��" },
	{ L"............\n�V�b�e �}�V�^�H\n...�\�E�f�X�J" },
	{ L"" },
	{ L"�V���C�j���O�E�B�U�[�h\n�� �I�~�}�C\n�V�}�X�J���l" },
	{ L"...�}�X�^�[ �m\n���C�S�� �f�X" },
	{ L"�Y�b�g ���J�C\n�f�L�i�C�m�f�X" },
	{ L"" },
	{ L"�}�h �� �^�^�L���b�e\n�W���E�j �i���^�C�f�X�l" },
	{ L"" },
	{ L"�i���_�J ���^�V�g\n�j�e�C�}�X�l" },//20
	{ L"�e���|�[�g ��\n�J�m�E �f�X�J�l" },
	{ L"" },
	{ L"" },
	{ L"�f���V�� �K\n�`�J�d�C�e �L�^��\n�j�Q�i�C�g �C�P�}�Z���l" },
	{ L"�X�x�e �I�i�W\n�^�_ �~�J�^ �K\n�`�K�E�_�P �f�X" },

	};
};

