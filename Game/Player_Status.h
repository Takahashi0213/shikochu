#pragma once

class Player_Status : public IGameObject
{
	static Player_Status* m_instance;
public:
	Player_Status();
	~Player_Status();

	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static Player_Status* Player_Status::GetInstance() {
		return m_instance;
	}

private:

	void SkillSetUp();
	void SkillUpdate(); //�X�L���F�X�X�V�p

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CSpriteRender*> m_spriteRenderBar;
	prefab::CFontRender* m_fontRender; //�c�@�p
	prefab::CFontRender* m_fontRender_bonus; //�{�[�i�X�����p

	const CVector2 LifePivot = { 0.5f, 0.9f };//HP�̊�_
	const CVector2 LifePivot2 = { 0.5f, 0.1f };//HP�̊�_
	const CVector2 StarPivot = { 0.5f, 0.0f };//�����o�[�̊�_

	bool StarMaxFlag = false; //�}�b�N�X�A�C�R���\���t���O
	float StarMaxColor = 1.0f; //�}�b�N�X�A�C�R���̔���
	bool StarMaxColorFlag = false; //�}�b�N�X�A�C�R���̐F�����������[�v����̂�
	float StarMaxScale = 1.0f; //�}�b�N�X�A�C�R���̊g�嗦

	const CVector2 ZankiPos = { -565.0f, 300.0f }; //�c�@���\���ʒu
	const float ZankiPosXHosei = 0.0f; //�c�@���P���̎�X�ʒu��␳
	CVector4 LifeColor = { 1.0f,1.0f,1.0f,1.0f }; //HP�o�[�̐F
	CVector4 StarColor = { 1.0f,1.0f,1.0f,1.0f }; //�����o�[�̐F
	const float ZankiScale = 3.0f; //�c�@���\���T�C�Y
	float ZankiScaleNow = 3.0f; //�c�@���\���T�C�Y

	bool StarMaxSE = false; //�����Q�[�W�}�b�N�X���ʉ��t���O
	bool StarMaxSE2 = false; //�����Q�[�W�}�b�N�X���ʉ��t���O

	bool WhiteGage = false; //�������鎞�̃E�F�C�g�t���O
	int WhiteTimer = 0;
	const int WhiteLimit = 20;

	//�c�@���������Ƃ���u�傫������p
	int BeforeZanki = 0;
	bool ZankiAnimeFlag = false;
	int ZankiAnimeTimer = 0;
	const int ZankiAnimeLimit = 12; //�\������

	//�L�R�E�`���E���j���̉��o�p
	bool KikoFlag = false;
	int KikoTimer = 0;
	const int KikoLimit = 40; //�\������
	const int KikoWait = 60;
	const float KikoMoveX = 6.0f; //1�t���[���̈ړ���
	float Kiko_Alpha = 0.0f;
	const float Kiko_AlphaSpeed = 0.05f; //1�t���[���̉�����

	//�X�L���o�[
	const float SkillScale = 0.5f; //�X�L���g�̑傫��
	const float StarMAX = 286.0f; //�X�^�[�Q�[�W�̑傫��
	const float StarPOS = -156.0f; //�ڈ󂪈�ԉ��̎��̍���
	short SkillIconMAX_Timer = 0; //�X�L���A�C�R���}�b�N�X�^�C�}�`

	//�X�L���f�[�^�i�ŏ��ɕۊǁj
	int SkillNoY = -1;
	int SkillNoX = -1;

};

