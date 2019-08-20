#pragma once
class StageWait : public IGameObject
{
	static StageWait* m_instance;
public:
	StageWait();
	~StageWait();

	void WaitSet(int stage, bool flag);
	void WaitDelete();
	void Update();

	//�C���X�^���X�̎擾
	static StageWait* StageWait::GetInstance() {
		return m_instance;
	}

private:
	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CSpriteRender* r;

	void JumpStart();

	bool Flag = false;
	int Stage = 0;
	int Timer = 0;
	float MulAlpha = 0.0f;
	float MulAlpha2 = 0.0f;
	float MulAlpha3 = 0.0f;
	float MulAlpha4 = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };
	
	bool DeleteFlag = false;
	int DeleteTimer = 0;

	bool Accflag = false;
	float MulAlphaAcc = 1.0f;

	//�W�����v�X�^�[�g�摜
	int JumpTimer = 0;
	float JumpPosY = 0.0f;
	float JumpSclX = 0.0f;
	float JumpSclY = 0.0f;

	//���b�Z�[�W*3
	const wchar_t Message[16][255]{
	{ L"sprite/Message/m_1_1.dds" }, //���͉摜��������
	{ L"sprite/Message/m_1_2.dds" },
	{ L"sprite/Message/m_1_3.dds" },
	{ L"sprite/Message/m_4_1.dds" },
	{ L"sprite/Message/m_4_2.dds" },
	{ L"sprite/Message/m_4_3.dds" },
	{ L"sprite/Message/m_5_1.dds" },
	{ L"sprite/Message/m_5_2.dds" },
	{ L"sprite/Message/m_5_3.dds" },
	{ L"sprite/Message/m_2_1.dds" },
	{ L"sprite/Message/m_2_2.dds" },
	{ L"sprite/Message/m_2_3.dds" },
	{ L"sprite/Message/m_3_1.dds" },
	{ L"sprite/Message/m_3_2.dds" },
	{ L"sprite/Message/m_3_3.dds" },

	};

	const bool MessageAcc[5]{//���b�Z�[�W�A�N�Z�T���̗L��
		false,
		false,
		false,
		false,
		true,
	};

	const wchar_t MessageAccName[5][255]{//���b�Z�[�W�A�N�Z�T���̖��O
		{ L"" }, 
		{ L"" },
	{ L"" },
	{ L"" },
	{ L"sprite/Message/m_3_a.dds" },

	};

	//��������n�[�h���[�h�p�f�[�^

	//���b�Z�[�W*3
	const wchar_t Message_Hard[16][255]{
	{ L"sprite/Message/hm_1_1.dds" }, //���͉摜��������
	{ L"sprite/Message/hm_1_2.dds" },
	{ L"sprite/Message/hm_1_3.dds" },
	{ L"sprite/Message/hm_2_1.dds" }, //���͉摜��������
	{ L"sprite/Message/hm_2_2.dds" },
	{ L"sprite/Message/hm_2_3.dds" },
	{ L"sprite/Message/hm_5_1.dds" }, //���͉摜��������
	{ L"sprite/Message/hm_5_2.dds" },
	{ L"sprite/Message/hm_5_3.dds" },
	{ L"sprite/Message/hm_3_1.dds" }, //���͉摜��������
	{ L"sprite/Message/hm_3_2.dds" },
	{ L"sprite/Message/hm_3_3.dds" },
	{ L"sprite/Message/hm_4_1.dds" }, //���͉摜��������
	{ L"sprite/Message/hm_4_2.dds" },
	{ L"sprite/Message/hm_4_3.dds" },

	};

	const bool MessageAcc_Hard[5]{//���b�Z�[�W�A�N�Z�T���̗L��
		false,
		false,
		true,
		false,
		true,
	};

	const wchar_t MessageAccName_Hard[5][255]{//���b�Z�[�W�A�N�Z�T���̖��O
	{ L"" },
	{ L"" },
	{ L"sprite/Message/hm_5_a.dds" },
	{ L"" },
	{ L"sprite/Message/hm_4_a.dds" },
	};

};

