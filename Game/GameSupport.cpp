#include "stdafx.h"
#include "GameSupport.h"
#include "SaveData.h"
#include "GameData.h"

GameSupport* GameSupport::m_instance = nullptr;

GameSupport::GameSupport()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}


GameSupport::~GameSupport()
{
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

}

bool GameSupport::Start() {

	f = NewGO<prefab::CFontRender>(9);
	//�\��
	text[256];
	//����
	swprintf(text, L"�e�X�g���b�Z�[�W");
	//�͂��B
	f->SetText(text);
	f->SetPosition(Def_MePos);
	f->SetScale(Me_Size);
	f->SetColor({ 1.0f,1.0f,1.0f,0.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);

	return true;
}

void GameSupport::Update() {

	GameData * gamedata = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();

	m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,0.0f }); //��x�����ɂ��܂��I

	if (gamedata->GetGameMode() != GameData::GameOver) {
		if (savedata->GetSupportFlag(0) == false) { //�_�b�V���ōU��
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			text[256];
			//����
			swprintf(text, L"A�{�^���Ń_�b�V�� ���Ȃ��� �Ă��ɂ���������");
			//�͂��B
			m_fontRender[0]->SetText(text);
		}
		else if (savedata->GetSupportFlag(1) == false) { //��イ�����_�b�V��
			if (StarDashSupportFlag == true) { //�\������
				m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
				text[256];
				//����
				if (savedata->GetSkill(false) == 0) { //Y�{�^���ɗ����_�b�V�����Z�b�g����Ă���
					swprintf(text, L"Y�{�^���� ��イ�����_�b�V���I");
				}else if (savedata->GetSkill(true) == 0) { //X�{�^���ɗ����_�b�V�����Z�b�g����Ă���
					swprintf(text, L"X�{�^���� ��イ�����_�b�V���I");
				}
				else { //�����_�b�V�����Ȃ�����
					swprintf(text, L"");
				}
				//�͂��B
				m_fontRender[0]->SetText(text);
			}
		}
		else if (savedata->GetSupportFlag(2) == false) { //�������Ȃ���̓����肵�ă{�X�Ƀ_���[�W
			if (gamedata->GetGameMode() == GameData::Battle3D_Mode) { //�\������
				m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
				text[256];
				//����
				swprintf(text, L"A�{�^���ł����� ���Ȃ��� �{�X�ɂ���������");
				//�͂��B
				m_fontRender[0]->SetText(text);
			}
		}
		else if (savedata->GetSupportFlag(3) == false) { //B�Ō����\
			if (gamedata->GetGameMode() == GameData::Battle3D_Mode) { //�\������
				m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
				text[256];
				//����
				swprintf(text, L"B�{�^���ł��񂻂� �ł��邼");
				//�͂��B
				m_fontRender[0]->SetText(text);
			}
		}
	}

	//�t���O�Ǘ�
	if (savedata->GetSupportFlag(0) == false) {
		if (gamedata->GetGekihaEnemy() >= 4) { //�G��4�̌��j������I��
			savedata->SetSupportFlag(0);
		}
	}
	if (savedata->GetSupportFlag(1) == false) {
		if (gamedata->GetGameMode() == GameData::Battle3D_Mode) { //����3D���[�h�Ȃ炱���̓X�L�b�v
			savedata->SetSupportFlag(1);
		}
		if (StarDashSupportFlag == false && gamedata->GetStar_Power() == 100) { //�����Q�[�W���}�b�N�X�Ȃ�t���O�I��
			StarDashSupportFlag = true;
		}
		else if (StarDashSupportFlag == true && gamedata->GetStar_Power() != 100) { //�����Q�[�W���}�b�N�X����Ȃ��Ȃ�ΏI��
			savedata->SetSupportFlag(1);
		}
	}
	if (savedata->GetSupportFlag(2) == false) {
		if (gamedata->GetBossDamage() >= 1) { //�{�X��1��_���[�W��^������I��
			savedata->SetSupportFlag(2);
		}
	}
	if (savedata->GetSupportFlag(3) == false) {
		if (gamedata->GetBossDamage() >= 3) { //�{�X��3��_���[�W��^������I��
			savedata->SetSupportFlag(3);
		}
	}

}

