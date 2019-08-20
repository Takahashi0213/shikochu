#pragma once
class GameOver : public IGameObject
{
	static GameOver* m_instance;
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();

	//インスタンスの取得
	static GameOver* GameOver::GetInstance() {
		return m_instance;
	}

private:
	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CSpriteRender* r;
	std::vector<prefab::CFontRender*> m_fontRender;
	prefab::CFontRender* f;
	prefab::CSoundSource* ss;

	int DeleteTimer = 0;
	bool DeleteFlag = false;

	int FinalScore = 0; //結果スコア
	int Point = 0; //所持ポイント
	int Point_Count = 0; //表示用ポイント
	bool PageFlag = false;
	bool ScoreFlag = false;

	int Timer = 0;
	int Timer2 = 0;
	bool KasanLoop = false;

	//画面遷移用アルファ
	float A_1 = 1.0f;
	float A_2 = 0.0f;

	//ゲームオーバー解説 2D
	const wchar_t Setumei_2D[3][255]{
	{ L"ダッシュは じゅみょうをしょうひする！\nてきにねらいをさだめて てきかくに つかおう！" },
	{ L"ゲージがたまったら Yボタンで りゅうせいダッシュ だ！\nてきをまとめてたおせるぞ！" },
	{ L"てきのこうげきちゅうは、\nダッシュでこうげきしてもダメージをあたえられないぞ！" },
};

	//ゲームオーバー解説 3D
	const wchar_t Setumei_3D[5][255]{
	{ L"じゅみょうがすくないほど、あたえるダメージがふえる！\nギリギリをねらおう！" },
	{ L"リンゴがおちてきて じゃまなときは\nりゅうせいダッシュ で いっきにとっぱだ！" },
	{ L"ティルオスカはすがたによって\nこうげきパターンがかわるぞ！" },
	{ L"てきがこうげきであたまをつきだした\nしゅんかんがチャンスだぞ！" },
	{ L"なかなかたおせないときは\nポイントをつかって きょうかしてみよう！" },
	};

	wchar_t HogeText[255] = { L"" };	//保管用

	//スコアだ！
	const float KeisanFontSize = 1.5f; //スコア文字サイズ
	const float ScoreFontSize = 2.0f; //スコア文字サイズ
	const int ScoreKasan = 50; //1フレームで加算される数

};

