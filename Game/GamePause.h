#pragma once
class GamePause : public IGameObject
{
	static GamePause* m_instance;
public:
	GamePause();
	~GamePause();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static GamePause* GamePause::GetInstance() {
		return m_instance;
	}

private:

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;

	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSoundSource* ss;

	int Timer = 0;
	bool CommandNow = false; //false�Ȃ�Back�Atrue�Ȃ烊�^�C�A

	//���O
	wchar_t StageName_hoge[255] = { L"" };	//���f�����ۊǗp

	//�ꎞ�p
	CVector3 position = CVector3::Zero;
	CVector3 scale = { 1.0f,0.0f,1.0f };
	CVector2 CV2_position = CVector2::Zero;
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	//�J�[�\���ړ�
	int CursorCount = 0;
	bool CursorFlag = false;

	//�萔
	const int SetWaitLimit = 60; //���������܂ł̎���/����ł���悤�ɂȂ鎞��

	const float AccPos_Hosei = 300.0f; //�㉺�g�̈ړ�����
	const float StagePos_Hosei = 500.0f; //�X�e�[�W�g�̈ړ�����
};

