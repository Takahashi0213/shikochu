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

	//インスタンスの取得
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

	//ジャンプスタート画像
	int JumpTimer = 0;
	float JumpPosY = 0.0f;
	float JumpSclX = 0.0f;
	float JumpSclY = 0.0f;

	//メッセージ*3
	const wchar_t Message[9][255]{
	{ L"sprite/Message/m_1_1.dds" }, //文章画像をここに
	{ L"sprite/Message/m_1_2.dds" },
	{ L"sprite/Message/m_1_3.dds" },
	{ L"sprite/Message/m_2_1.dds" },
	{ L"sprite/Message/m_2_2.dds" },
	{ L"sprite/Message/m_2_3.dds" },
	{ L"sprite/Message/m_3_1.dds" },
	{ L"sprite/Message/m_3_2.dds" },
	{ L"sprite/Message/m_3_3.dds" },

	};

	const bool MessageAcc[3]{//メッセージアクセサリの有無
		false,
		false,
		true,
	};

	const wchar_t MessageAccName[3][255]{//メッセージアクセサリの名前
		{ L"" }, 
		{ L"" }, 
		{ L"sprite/Message/m_3_a.dds" }, 

	};

	//ここからハードモード用データ

	//メッセージ*3
	const wchar_t Message_Hard[9][255]{
	{ L"sprite/Message/hm_1_1.dds" }, //文章画像をここに
	{ L"sprite/Message/hm_1_2.dds" },
	{ L"sprite/Message/hm_1_3.dds" },
	{ L"sprite/Message/m_2_1.dds" },
	{ L"sprite/Message/m_2_2.dds" },
	{ L"sprite/Message/m_2_3.dds" },
	{ L"sprite/Message/m_3_1.dds" },
	{ L"sprite/Message/m_3_2.dds" },
	{ L"sprite/Message/m_3_3.dds" },

	};

	const bool MessageAcc_Hard[3]{//メッセージアクセサリの有無
		false,
		false,
		false,
	};

	const wchar_t MessageAccName_Hard[3][255]{//メッセージアクセサリの名前
	{ L"" },
	{ L"" },
	{ L"" },
	};

};

