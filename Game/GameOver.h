#pragma once
class GameOver : public IGameObject
{
	static GameOver* m_instance;
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static GameOver* GameOver::GetInstance() {
		return m_instance;
	}

private:
	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CSpriteRender* r;
	std::vector<prefab::CFontRender*> m_fontRender;
	prefab::CFontRender* f;
	prefab::CSoundSource* ss;

	int DeleteTimer = 0;
	bool DeleteFlag = false;

	int FinalScore = 0; //���ʃX�R�A
	int Point = 0; //�����|�C���g
	int Point_Count = 0; //�\���p�|�C���g
	bool PageFlag = false;
	bool ScoreFlag = false;

	int Timer = 0;
	int Timer2 = 0;
	bool KasanLoop = false;

	//��ʑJ�ڗp�A���t�@
	float A_1 = 1.0f;
	float A_2 = 0.0f;

	//�Q�[���I�[�o�[��� 2D
	const wchar_t Setumei_2D[3][255]{
	{ L"�_�b�V���� ����݂傤�����傤�Ђ���I\n�Ă��ɂ˂炢�������߂� �Ă������� �������I" },
	{ L"�Q�[�W�����܂����� Y�{�^���� ��イ�����_�b�V�� ���I\n�Ă����܂Ƃ߂Ă������邼�I" },
	{ L"�Ă��̂����������イ�́A\n�_�b�V���ł����������Ă��_���[�W�����������Ȃ����I" },
};

	//�Q�[���I�[�o�[��� 3D
	const wchar_t Setumei_3D[5][255]{
	{ L"����݂傤�������Ȃ��قǁA��������_���[�W���ӂ���I\n�M���M�����˂炨���I" },
	{ L"�����S�������Ă��� ����܂ȂƂ���\n��イ�����_�b�V�� �� �������ɂƂ��ς��I" },
	{ L"�e�B���I�X�J�͂������ɂ����\n���������p�^�[��������邼�I" },
	{ L"�Ă������������ł����܂���������\n����񂩂񂪃`�����X�����I" },
	{ L"�Ȃ��Ȃ��������Ȃ��Ƃ���\n�|�C���g�������� ���傤�����Ă݂悤�I" },
	};

	wchar_t HogeText[255] = { L"" };	//�ۊǗp

	//�X�R�A���I
	const float KeisanFontSize = 1.5f; //�X�R�A�����T�C�Y
	const float ScoreFontSize = 2.0f; //�X�R�A�����T�C�Y
	const int ScoreKasan = 50; //1�t���[���ŉ��Z����鐔

};

