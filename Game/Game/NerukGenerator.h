#pragma once
class NerukGenerator : public  IGameObject
{
	static NerukGenerator* m_instance;

public:
	NerukGenerator();
	~NerukGenerator();
	void Update();

	
	//�C���X�^���X�̎擾
	static NerukGenerator* NerukGenerator::GetInstance() {
		return m_instance;
	}
	int GetMoveRandom();
	int GetAnimesionRandom();

private:
	//����
	int  moverandom = 0; //�����ꏊ�����p
	int  animesionrandom = 0; //�A�j���[�V���������p
	int timer = 0;	//�l���N�̐����p
	int oldmovecount = 3;
	const float newtimer = 90.0f;//���������܂ł̎���

	int timer1 = 0;	//�l���N�̐����p
	int oldmovecount1 = 3;
	const float newtimer1 = 90.0f;//���������܂ł̎���
	
	bool flag = false;
	
};

