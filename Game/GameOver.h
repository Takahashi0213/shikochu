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

	int DeleteTimer = 0;
	bool DeleteFlag = false;

	//ゲームオーバー解説 2D
	const wchar_t Setumei_2D[3][255]{
	{ L"ダッシュは じゅみょうをしょうひする！\nてきにねらいをさだめて てきかくに つかおう！" },
	{ L"ゲージがたまったら Yボタンで りゅうせいダッシュ だ！\nてきをまとめてたおせるぞ！" },
	{ L"てきのこうげきちゅうは、\nダッシュでこうげきしてもダメージをあたえられないぞ！" },
};

	//ゲームオーバー解説 3D
	const wchar_t Setumei_3D[3][255]{
	{ L"じゅみょうがすくないほど、あたえるダメージがふえる！\nギリギリをねらおう！" },
	{ L"てきがこうげきであたまをつきだした\nしゅんかんがチャンスだぞ！" },
	{ L"なかなかたおせないときは\nポイントをつかって きょうかしてみよう！" },
	};

	wchar_t HogeText[255] = { L"" };	//保管用

};

