#pragma once
class EffectManager : public IGameObject
{
	static EffectManager* m_instance;
public:

	//エフェクト名前
	enum Effect {
		Null,
		ItemGet, //アイテム入手時のエフェクト
		spawn,//出現時のエフェクト
		star,//移動後に出すやつ5
		enemySpawn,//敵がすっぽんぽん
		ItemSpawn, //アイテムが出たり消えたり！
		Bakuhatu, //どかーん
		Beam, //ビーム準備
		BeamHassya, //ビーム発射
		Gao,//がおー]
		Dash, //ダッシュエフェクト
		Bonus,//ギリギリボーナス
	};

	EffectManager();
	~EffectManager();

	//引数1→再生するエフェクト（種類はヘッダーに）
	//引数2→position
	//引数3→scale
	void EffectPlayer(Effect EF, CVector3 position, CVector3 scale);
	void EffectPlayer(Effect EF, CVector3 position, CVector3 scale,bool flag);

	//インスタンスの取得
	static EffectManager* EffectManager::GetInstance() {
		return m_instance;
	}

private:

	//エフェクトファイル名
	wchar_t DetaBase[12][30]{
		{ L"" },//Nullなので何もない
		{ L"effect/Item.efk" },
		{ L"effect/spawn.efk" },
		{ L"effect/star.efk" },
		{ L"effect/enemySpawn.efk" },
		{ L"effect/itemSpawn.efk" },
		{ L"effect/bakuha.efk" },
		{ L"effect/beam.efk" },
		{ L"effect/beam_hassya.efk" },
		{ L"effect/gao.efk" },
		{ L"effect/dash.efk" },
		{ L"effect/Bonus.efk" },

	};

	CVector3 m_scale = CVector3::One;
	CVector3 m_position = CVector3::Zero;

	Effect m_stete = Null;		 //エフェクト状態
	wchar_t EF_Name[30] = { L"" };	//エフェクト名保管用
};

