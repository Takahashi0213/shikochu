#pragma once
class GameResult : public IGameObject
{
	static GameResult* m_instance;
public:
	GameResult();
	~GameResult();
	bool Start();
	void Update();
private:

	//�J�E���g�ϐ��ǂ������Z�b�g
	void CountReset() {
		Hoge_Couneter = 0;
		MulAlpha = 0.0f;
		MulColor = { 1.0f,1.0f,1.0f,1.0f };
		HogePosition1 = 0.0f;
		HogePosition2 = 0.0f;
		HogeFlag = false;
	}

	//MulAlpha�ϐ������������ɂ��܂�
	void GameResult::MulPuls() {
		MulAlpha += 0.05f;
		if (MulAlpha > 1.0f) {
			MulAlpha = 1.0f;
		}
	}

	//�����Ă��܂��`�`�`�`
	void DeleteAllSpriteRender() {
		for (int i = 0; i < m_spriteRender.size(); i++) {
			DeleteGO(m_spriteRender[i]);
		}
	}

	//�����Ă��܂��`�`�`�`�I�I�I
	void DeleteAllFontRender() {
		for (int i = 0; i < m_fontRender.size(); i++) {
			DeleteGO(m_fontRender[i]);
		}
	}

	//�X�L���l������
	void SkillGetSetup();
	//�X�L���l�����o
	//�������Ɋl�������X�L��No
	void SkillGet(short SetPos);

	enum resultscene {
		scene1,
		scene2,
	};
	enum resultturn {
		scene1_Background,
		scene1_ResultMozi,
		scene1_ZankiBonus,
		scene1_GiriBonus,
		scene1_ItemBonus,
		scene1_MatometeScore,
		scene1_Runk,
		scene2_Seni,
		scene2_ScoreUp,
		scene2_ScoreIdou,
		scene2_ScoreKasan,
	};

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	std::vector<prefab::CSpriteRender*> m_spriteRender_skill;
	std::vector<prefab::CFontRender*> m_fontRender_skill;

	resultscene ResultScene = scene1;		 //���
	resultturn ResultTurn = scene1_Background;		 //���

	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSpriteRender* r_skill;
	prefab::CFontRender* f_skill;
	prefab::CSoundSource* ss;
	float BMG_V = 2.0f;

	int FinalScore = 0; //���ʃX�R�A
	int Point = 0; //�����|�C���g
	int Point_Count = 0; //�\���p�|�C���g

	int NowStage = 0;

	bool OK_Flag = false; //����L�[�������܂ő҂��Ȃ���
	bool FinalFlag = false;
	int FinalCount = 0;

	//�ȉ��J�E���g�p
	int Hoge_Couneter = 0; //�^�C�}�[
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };
	float HogePosition1 = 0.0f;
	float HogePosition2 = 0.0f;

	//�ȉ��A�j���[�V�����p
	float ResultIconMoveY = 210.0f; //���U���g�A�C�R�����㉺�ړ����邼
	bool ResultIconUpDownFlag = false; //false�Ȃ��Atrue�Ȃ牺
	int ResultIconTimer = 0; //���Flag��؂�ւ���܂ł̃^�C�}�[
	bool ResultIconMoveFlag = false; //���ꂪtrue�̊ԃA�j���[�V��������
	
	//�ȉ��A�N�Z���[�v�p
	float AccPosY1 = 0; //�A�N�Z�T���[1��Y���W
	float AccPosY2 = -720; //�A�N�Z�T���[2��Y���W
	float AccPosY1m = 360; //�A�N�Z�T���[1M��Y���W
	float AccPosY2m = -360; //�A�N�Z�T���[2M��Y���W

	//�ȉ����U���g�����p
	int ZankiBonus = 0;
	int GiriBonus = 0;
	int ItemBonus = 0;

	//�t���O
	bool HogeFlag = false; //�ėp�t���O
	bool RunkFlag = false; //�����N�\���p�t���O
	bool PointFlag = false; //�|�C���g���㉺�ړ����鎞�̃t���O
	bool HardFlag = false; //�n�[�h���[�h�t���O

	float HardHosei = 0.0f; //�n�[�h���[�h�̃X�R�A�␳
	int hoge = 0; //�t�F�C�Y�U�Ŏg���܂�
	int hoge2 = 0; //�t�F�C�Y�U�Ŏg���܂�
	int hoge3 = 0; //�t�F�C�Y�U�Ŏg���܂�
	bool KikoFlag = false;
	int KikoBonus = 0;
	bool SkillFlag = false;

	//�X�L���擾�p
	bool SkillGetFlag[24]{ //true�Ȃ�Ō�Ɏ擾���o�I
		false,
	};	
	bool Skill_EffectNow = false; //�X�L���擾���o����
	bool Skill_EffectEnd = false; //1�G�t�F�N�g���I�������true
	short CheckSkillNow = 0; //���m�F���̃X�L��No
	short SkillTimer = 0; //�X�L���ړ��^�C�}�[
	bool SkillMove = false; //�X�L���ړ���ԃt���O
	
	//////////////////////////////////////////�萔�F�X///////////////////////////////////////
	//�t�F�C�Y�P �w�i�\��
	const int PhaseTimer1 = 40; //����̐�������
	const float WakuPositon = 600.0f; //���E�g�̍ŏI�|�W�V����
	const float WakuMoveSpeed = 20.0f; //���E�g�̈ړ����x
	const float WakuSpeedDown = 700.0f; //���E�g�̑��x��������|�W�V����
	const float WakuSpeedDownHosei = 0.6; //���E�g�̌������x�i���E�g�̈ړ����x�ɏ�Z�����j
	const float ACCPositionX = -500.0f; //���̑�����X���W �Œ�

	//�t�F�C�Y�Q ���U���g�ړ�
	const int PhaseTimer2 = 80; //����̐�������
	const float ResultMoziHigh = 200.0f; //���U���g�̕\������
	const float ResultMoziMoveSpeed = 20.0f; //���U���g�̈ړ����x
	const float ResultMoziMove = 40.0f; //���U���g���߂钷��
	const int ResultMoziModoriTime = 20; //���U���g���߂鎞��
	const float ResultMoziMoveX = ResultMoziMove / (float)ResultMoziModoriTime; //���U���g�̈ړ�����
	const float ResultIconMove = 1.0f; //���U���g�A�C�R���̈ړ�����
	const int ResultIconMoveTime = 48; //���U���g�A�C�R����1���[�v����Ԋu

	//�t�F�C�Y�R �c�@�{�[�i�X�I
	const int PhaseTimer3 = 30; //����̐�������
	const int BonusAverage = 10; //�\�������܂ł̎��ԁi�t�F�C�Y�T�܂ŗ��p�j
	const float BonusFontSize = 1.2f; //�{�[�i�X�̕����T�C�Y�i�t�F�C�Y�T�܂ŗ��p�j

	//�t�F�C�Y�S �M���M���{�[�i�X�I
	const int PhaseTimer4 = 30; //����̐�������
	const float BonusMoziIdou = 80.0f; //�t�F�C�Y3��艺�Ɉړ�����ʁi�t�F�C�Y�T�܂ŗ��p�j

	//�t�F�C�Y�T �A�C�e���{�[�i�X�I
	const int PhaseTimer5 = 30; //����̐�������

	//�t�F�C�Y�U �ŏI�X�R�A
	const int PhaseTimer6 = 40; //����̐�������
	const int ScoreAverage = 30; //�\�������܂ł̎���
	const float ScoreFontSize = 2.0f; //�X�R�A�̕����T�C�Y�i�t�F�C�Y�X�ł��g�p�j
	const float ScoreYHosei = 40.0f; //�X�R�A�̕\������������̂ŏ�ɓ�����
	const int HardTimerHosei = 80; //�n�[�h���[�h���̂ݎ��Ԃɕ␳��������
	const int PhaseTimer6_Hard = 80; //�n�[�h�{�[�i�X��\������^�C�~���O

	//�t�F�C�Y�V �]�����Ă�낤
	const int PhaseTimer7 = 90; //����̐�������
	const int RunkAverage = 30; //�\�������܂ł̎���
	const CVector3 RunkPos = { 230.0f,200.0f,1.0f };
	const float RunkKakudaiMin = 0.5f; //�]���̃T�C�Y�k������
	const float RunkScaleSpeed = 0.4f; //�]���̊g�嗦�ύX���x

	//�t�F�C�Y�W �J��
	const int PhaseTimer8 = 40; //����̐�������
	const float SeniMove = 30.0f; //�X�R�A�������̈ړ����x�i�t�F�C�Y�X�ł��g�p�j

	//�t�F�C�Y�X �ŏI���� �`�ړ�������Y���ā`
	const int PhaseTimer9 = 60; //����̐�������
	const float KeisanFontSize = 1.5f; //�X�R�A�����T�C�Y
	const float SeniMoveHosei = 5.0f; //�X�R�A�������̈ړ����x�␳

	//�t�F�C�Y�P�O ����͈ړ�����X�R�A������
	const int PhaseTimer10 = 14; //����̐�������

	//�t�F�C�Y�P�P ����łق�Ƃ��ɃT���i��
	const int ScoreKasan = 100; //1�t���[���ŉ��Z����鐔
	const int DeleteTime = 80; //�I�����o�̎���

	//�X�L���Q�b�g
	const float SkillX_Hosei = 2000.0f; //�X�L���Q�b�g�E�B���h�E�̏����ʒuX�␳
	const int SkillMoveSpeed = 20; //�X�L���g�̈ړ����x
	const int SkillMoveWait = 20; //�X�L���g�̈ړ��E�F�C�g
	const wchar_t Reset[1] = L"";

};

