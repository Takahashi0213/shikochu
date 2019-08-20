#pragma once
#include "tkEngine/light/tkPointLight.h"

class StageSelect : public IGameObject
{
	static StageSelect* m_instance;
public:
	enum EnAnimationClip {
		enAnimationClip_motion1, //動く1
		enAnimationClip_motion2, //動く2
		enAnimationClip_motion3, //動く3
		enAnimationClip_motion4, //動く4
		enAnimationClip_motion5, //動く5
		enAnimationClip_Num,  //アニメーションクリップ
	};

	StageSelect();
	~StageSelect();
	bool Start();
	void Update();

	//インスタンスの取得
	static StageSelect* StageSelect::GetInstance() {
		return m_instance;
	}

private:

	void StageSelect::TextUpdate(); //文章の更新
	void StageSelect::BoxUpdate(); //箱の配置変更
	void StageSelect::STARTUpdate(); //スタートが点滅する

	CAnimationClip m_animClips[enAnimationClip_Num];
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	std::vector<prefab::CSkinModelRender*> m_skinModelRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSkinModelRender* e;
	prefab::CPointLight* m_pointLig;	//点光源。

	int SelectStageNow = 0; //現在選択中のステージ

	wchar_t BOX_Name[255] = { L"" };	//ボックス名保管用

	float BugPosY = -10.0f; //虫が上下移動するのでその１
	bool BugPosSet = false; //虫が上下移動するのでその２

	float BoxPosZ = 0.0f;
	bool IdouFlag = false; //移動中フラグ
	bool SelectedFlag = false; //選択中フラグ
	int Selected_Counter = 0; //選択演出後のカウンター

	int MAX_Stage = 0; //今遊べるステージの数

	float RotBox = 3.0f;

	float BMG_V = 2.0f;

	//ハードノーマル
	bool HardFlag = false; //ハードモードフラグ
	bool HardChangeFlag = false; //切り替え演出フラグ

	bool StartFlag = false;
	int StartCount = 0;

	//強化画面
	bool KyokaFlag = false;

	//図鑑画面
	bool ZukanFlag = false;

	//点滅スタート
	int TenmetuTimer = 0;

	int TranTimer = 0;

	//定数
	const CVector3 BoxPosDEF = { -100.0f,-120.0f,0.0f }; //選択中のボックスが移動する場所
	const float BoXMoveZ = 200.0f; //非選択中のボックスの移動差
	const float BoXDownY = -170.0f; //移動中のボックスY座標下限
	const float HighScoreFontSize = 2.0f; //ハイスコアのフォントサイズ
	const float StageFontSize = 1.5f; //ステージ番号のフォントサイズ
	const float StageNameFontSize = 1.0f; //ステージ名のフォントサイズ
	const int TranLimit = 40; //トランジション待ち

	const int HardChangeLimit = 40; //モード切替演出制限時間

	float resetToneMapTimer = 1.0f;
};

