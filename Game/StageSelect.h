#pragma once
#include "tkEngine/light/tkPointLight.h"

class StageSelect : public IGameObject
{
	static StageSelect* m_instance;
public:
	enum EnAnimationClip {
		enAnimationClip_motion1, //����1
		enAnimationClip_motion2, //����2
		enAnimationClip_motion3, //����3
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	StageSelect();
	~StageSelect();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static StageSelect* StageSelect::GetInstance() {
		return m_instance;
	}

private:

	void StageSelect::TextUpdate(); //���͂̍X�V
	void StageSelect::BoxUpdate(); //���̔z�u�ύX
	void StageSelect::STARTUpdate(); //�X�^�[�g���_�ł���

	CAnimationClip m_animClips[enAnimationClip_Num];
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	std::vector<prefab::CSkinModelRender*> m_skinModelRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSkinModelRender* e;
	prefab::CPointLight* m_pointLig;	//�_�����B

	int SelectStageNow = 0; //���ݑI�𒆂̃X�e�[�W

	wchar_t BOX_Name[255] = { L"" };	//�{�b�N�X���ۊǗp

	float BugPosY = -10.0f; //�����㉺�ړ�����̂ł��̂P
	bool BugPosSet = false; //�����㉺�ړ�����̂ł��̂Q

	float BoxPosZ = 0.0f;
	bool IdouFlag = false; //�ړ����t���O
	bool SelectedFlag = false; //�I�𒆃t���O
	int Selected_Counter = 0; //�I�����o��̃J�E���^�[

	int MAX_Stage = 0; //���V�ׂ�X�e�[�W�̐�

	float RotBox = 3.0f;

	float BMG_V = 2.0f;

	//�n�[�h�m�[�}��
	bool HardFlag = false; //�n�[�h���[�h�t���O
	bool HardChangeFlag = false; //�؂�ւ����o�t���O

	bool StartFlag = false;
	int StartCount = 0;

	//�������
	bool KyokaFlag = false;

	//�}�Ӊ��
	bool ZukanFlag = false;

	//�_�ŃX�^�[�g
	int TenmetuTimer = 0;

	int TranTimer = 0;

	//�萔
	const CVector3 BoxPosDEF = { -100.0f,-120.0f,0.0f }; //�I�𒆂̃{�b�N�X���ړ�����ꏊ
	const float BoXMoveZ = 200.0f; //��I�𒆂̃{�b�N�X�̈ړ���
	const float BoXDownY = -170.0f; //�ړ����̃{�b�N�XY���W����
	const float HighScoreFontSize = 2.0f; //�n�C�X�R�A�̃t�H���g�T�C�Y
	const float StageFontSize = 1.5f; //�X�e�[�W�ԍ��̃t�H���g�T�C�Y
	const float StageNameFontSize = 1.0f; //�X�e�[�W���̃t�H���g�T�C�Y
	const int TranLimit = 40; //�g�����W�V�����҂�

	const int HardChangeLimit = 40; //���[�h�ؑ։��o��������
};

