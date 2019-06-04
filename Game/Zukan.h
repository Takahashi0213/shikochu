#pragma once
class Zukan : public IGameObject
{
	static Zukan* m_instance;
public:
	enum EnAnimationClip {
		enAnimationClip_Num,  //アニメーションクリップ
		enAnimationClip_ATK,  //アニメーションクリップ
	};

	Zukan();
	~Zukan();
	bool Start();
	void Update();

	//インスタンスの取得
	static Zukan* Zukan::GetInstance() {
		return m_instance;
	}
private:

	void KoumokuUpdate();
	void AttackAnime(int i);

	CAnimationClip m_mo0anim[2];
	CAnimationClip m_mo1anim[2];
	CAnimationClip m_mo2anim[2];
	CAnimationClip m_mo3anim[2];
	CAnimationClip m_mo4anim[2];
	CAnimationClip m_mo5anim[2];
	CAnimationClip m_mo6anim[2];
	CAnimationClip m_mo7anim[2];
	CAnimationClip m_mo8anim[2];
	CAnimationClip m_mo9anim[2];
	CAnimationClip m_mo10anim[2];
	CAnimationClip m_mo11anim[2];
	CAnimationClip m_mo12anim[2];

	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CQuaternion m_rotation2 = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	std::vector<prefab::CSkinModelRender*> m_skinModelRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSkinModelRender* e;

	float BMG_V = 1.0f;

	//実行用
	float MulAlpha = 1.0f;
	float MulAlpha2 = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	int Timer = 0;
	bool DeleteFlag = false;
	
	//Exit演出
	int E_MoveTimer = 0;
	bool E_MoveFlag = false;

	//名前
	wchar_t ModelName[255] = { L"" };	//モデル名保管用

	//現在の項目
	int SelectNow = 0;

	//攻撃アニメ
	bool AttackAnimeFlag = false;

	//定数
	const wchar_t Reset[1] = L"";

};

