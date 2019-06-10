#pragma once
class Tutorial : public IGameObject
{
	static Tutorial* m_instance;
public:
	Tutorial();
	~Tutorial();
	bool Start();
	void Update();

private:

	enum TutorialScene {
		scene1,//�ŏ���
		scene1_Play,//�ړ����Ă݂�
		scene2,//�����ƓG
		scene2_Play,//�G��|���Ă݂�
		scene3,//�����_�b�V��
		scene3_Play,//�A�C�e�����W�߂ė����_�b�V�����g���Ă݂悤
		scene4,//�����܂�
		END,//�}�W�ŏI��
	};

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	std::vector<prefab::CSkinModelRender*> m_skinModelRender;

	TutorialScene Tutorialscene = scene1;		 //���

	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSkinModelRender* e;
	prefab::CSoundSource* ss;

	int Timer = 0;
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };
	prefab::CDirectionLight* m_directionLig = nullptr;
	float m_tonemapDisableTimer = 1.0f;

	int PushCount = 0; //�J�E���g�p
	wchar_t text[256];
	int A_Timer = 0;

	int YazirusiTimer = 0;
	bool YazirusiFlag = false;

	bool StarFlag = false; //�X�^�[�Q�[�W�}�b�N�X�t���O
	bool GameOverFlag = false; //�Q�[���I�[�o�[�ɂȂ��Ă��܂����c

	//�萔
	const float M_PosY = 800.0f;
	const float M_PosY2 = 880.0f;
	const float M_YHosei = 30.0f;

};

