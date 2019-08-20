#include "stdafx.h"
#include "RockGenerator.h"
#include "Rock.h"

RockGenerator* RockGenerator::m_instance = nullptr;

RockGenerator::RockGenerator()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


RockGenerator::~RockGenerator()
{
	QueryGOs<Rock>("Rock", [&](Rock* rock) {
		rock->SetActiveFlag(true);
		rock->DeleteNow();
		return true;
		});

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool RockGenerator::Start() {

	int RockKazu = rand() % 4;

	for (int i = 0; i < 3 + RockKazu; i++) {
		RockSeisei(true);
	}

	return true;
}

void RockGenerator::Update() {

	if (Timer >= RockLimit) {//��𐶐�����

		RockSeisei(false);

		RockLimit = rand() % 300;

		Timer = 0;
	}

	Timer++;

}

//������ture���Ə����p�_�C�i�~�b�N����
void RockGenerator::RockSeisei(bool Flag) {

	//����Y�ʒu�������_���Ɍ��߂�
	float PosY = 0.0f;
	random = rand() % 500;
	PosY = (float)random;
	random = rand() % 2;
	if (random == 1) {
		PosY = -1.0f;
	}
	PosY -= 250.0f;

	if (Flag == false) {
		Rock *rock = NewGO<Rock>(0, "Rock");
		rock->SetPosition({ -2000.0f,PosY,-800.0f });
	}
	else if (Flag == true) {
		Rock *rock = NewGO<Rock>(0, "Rock");

		float PosX = -1500.0f;
		random = rand() % 2000;
		PosX += (float)random;
		PosY += 100.0f;

		rock->SetPosition({ PosX,PosY,-800.0f });

	}

}