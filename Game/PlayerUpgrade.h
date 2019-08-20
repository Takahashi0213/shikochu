#pragma once
class PlayerUpgrade : public IGameObject
{
	static PlayerUpgrade* m_instance;
public:
	PlayerUpgrade();
	~PlayerUpgrade();
	bool Start();
	void Update();
private:
	
	void Setting();
	void CommandUpdate();
	void CommandJump();
	void CommandShake();
	void Transceiver(wchar_t text[256]);
	void TransceiverStandby();
	void commandTren();
	void A_ButtonUpdate();
	void KumoMove();
	void GamenChange(bool gamen); //false=強化からスキル true=スキルから強化
	void YazirusiSupporter(); //上下左右サポートするよ
	//ここからスキルセット関連
	void CommandUpdate_Skill();
	void CommandJump_Skill();
	void CommandShake_Skill();
	void commandTren_Skill();

	void Point_keisan() { //消費ポイントを計算
		zanki_Point = 200 + (100 * zanki_X);
		attack_Point = 200 + (100 * attack_X);
		jyumyo_Point = 200 + (100 * jyumyo_X);
	}

	int CommandNow = 0;

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	std::vector<prefab::CSpriteRender*> m_spriteRender_skill;
	std::vector<prefab::CFontRender*> m_fontRender_skill;

	prefab::CSpriteRender* r;
	prefab::CSpriteRender* skill_r;
	prefab::CFontRender* f;
	prefab::CFontRender* skill_f;
	prefab::CSoundSource* ss;

	int akariTimer = 0;
	int startTimer = 0;

	//項目Jump
	bool jumpFlag = false;
	int jumpTimer = 0;
	bool jumpFlag_s = false;
	int jumpTimer_s = 0;

	//項目震える
	bool buruFlag = false;
	int buruTimer = 0;
	bool buruFlag_s = false;
	int buruTimer_s = 0;

	//トランシーバー
	wchar_t Message[256]; //喋る内容を保存
	bool TranFlag = false;
	int TranTimer = 0;
	int T_Timer = 0;

	//ステータス
	int point = 0; //所持ポイント
	int zanki = 0; //残機
	int attack = 0; //こうげき
	int jyumyo = 0; //寿命
	int zanki_X = 0; //残機強化回数
	int attack_X = 0; //攻撃力強化回数
	int jyumyo_X = 0; //寿命強化回数
	int zanki_Point = 0; //残機強化に必要なポイント
	int attack_Point = 0;
	int jyumyo_Point = 0;

	float DEF_Mul = 0.4f; //１番の不透明度
	float DEF_Mul2 = 0.0f; //２番の不透明度
	float Move_Hoge = 300.0f; //移動する虫

	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	//ステータスUP
	int StatusUpTimer = -1;
	float StatusUpAlpha = 1.0f;

	//Exit演出
	int E_MoveTimer = 0;
	bool E_MoveFlag = false;

	int A_Timer = 0;

	//画面フラグ
	bool NowGamen = false; //false=強化、true=スキル

	//動く蜘蛛
	int KumoTimer = 0;
	int Random = 0;
	int KumoLimit = 0;

	//矢印上下
	bool Ya_UpDownFlag = false;
	int Ya_UpDownTimer = 0;

	//動くXY
	int XY_Timer = 0;

	//さようなら
	bool DeleteFlag = false;
	int DeleteTimer = 0;

	//スキルセット関連
	int NowSelectSkill = 0; //スキルカーソル位置
	int NouSkillCursor = 0; //画面内のカーソル位置（0～2）
	int SkillSetMoveTimer = -1; //スキル遷移用タイマー（普段は-1）

	//定数
	const float Ypos_hoge = 720.0f; //Yサイズ（便利）
	const float wakuPosDefY = 140.0f; //強化枠のポジション差
	const float wakuPosDEF_X = 40.0f; //強化枠のXポジション
	const float statusPosY = 40.0f; //強化ステータスのポジション差

	const float wakuPosDefY_Skill = 140.0f; //スキル枠のポジション差
	const float wakuPosDEF_X_Skill = 440.0f; //スキル枠のXポジション
	const float statusPosY_Skill = 40.0f; //スキルのポジション差
	const float SkillY_Hosei = -20.0f; //高さが微妙だったので
	const float SkillMoveX = 600.0f; //スキル枠が非表示の時のX補正
	const int MaxSeniMove = 10; //画面切り替え制限時間

	const int XY_Limit = 120; //XYが動くまでのタイマー

	const int MAX_Upgrade = 25; //最大強化回数
	const int Zanki_Plus = 2; //1回の強化で加算される残機
	const int Attack_Plus = 6; //1回の強化で加算される攻撃
	const int Life_Plus = 4; //1回の強化で加算される寿命
	const int TranStart = 180; //トランシーバーの更新が始まるタイミング
	const wchar_t Reset[1] = L"";
	const CVector2 StatusUP_DefPos = { 380.0f, 70.0f };
	const float KumoY_MAX = 380.0f; //動く蜘蛛の最大位置
	const float KumoY_MIN = 300.0f; //動く蜘蛛の最小位置
	const int KumoInterval = 60; //蜘蛛がまた動くまでの時間

	/////////////////////雑談
	const int ZatsudanKazu = 25;
	int KaiwaNo = 0;
	int KaiwaTimer = 0;
	int KaiwaNow = -1;
	const int KaiwaLimit = 200;
	wchar_t Kaiwa[255];

	const int Zatudan_Kaisuu[25]{
	{ 3 },
	{ 2 },
	{ 2 },
	{ 2 },
	{ 3 },
	{ 2 },
	{ 3 },
	{ 2 },
	{ 2 },
	{ 3 },
	{ 3 },
	{ 3 },
	{ 2 },
	{ 3 },
	{ 3 },
	{ 3 },
	{ 2 },
	{ 3 },
	{ 2 },
	{ 3 },//20
	{ 3 },
	{ 2 },
	{ 2 },
	{ 3 },
	{ 3 },

	};

	const wchar_t Zatsudan_1[25][255]{
	{ L"ホシノ チカラガ\nアナタサマ ヲ\nツヨクシマス" },
	{ L"ハンバーグ、\nタベカケデスネ..." },
	{ L"クモ ハ\nニガテ ナンデスヨ" },
	{ L"コップ ニ ナミダ ヲ\nイレスギマシタ" },
	{ L"アナタサマ ハ\nイノチト ヒキカエニ\nナニヲ エマシタカ？" },
	{ L"ハロー ハロー\nアタラシイ イノチ..." },
	{ L"アナタサマ ノ\nイノチハ\nカギラレテイマス" },
	{ L"アナタサマ ニ\nソックリ ノ\nムシ ヲ ミマシタヨ" },
	{ L"ズカン ガメン デ\nジュウジキー ヲ\nサユウニ ウゴカスト..." },
	{ L"コノヘヤ ニハ\nコレダケシカ\nアリマセンヨ" },
	{ L"ワタシハ ココカラ\nウゴケナイノデ\nワカリマセンガ..." },
	{ L"オドロカナイデ\nキイテクダサイネ" },
	{ L"イノチ ハ シヌ トキ\nアオイ ヒカリ ヲ\nハナツ ラシイデス" },
	{ L"ロボット ダカラ\nト イッテ サベツ ハ\nイケマセンヨ" },
	{ L"モウ ジカン ガ\nナイノデス" },
	{ L"シヌコト ガ\nコワイノデスカ" },
	{ L"ウタハ トクイ\nナンデスヨ\nイガイ デスカ？" },
	{ L"コノ セカイ ハ\nハコ デ デキテイマス" },
	{ L"ハードモード デシカ\nアエナイ モンスター モ\nイマスネ" },
	{ L"シンデ コソ\nトウトイ イノチ デス" },//20
	{ L"ナイゾウ ヲ\nナイゾウ..." },
	{ L"イゼン ハ\nオオクノ ニンゲンガ\nココニ キテイマシタ" },
	{ L"マスターハ ハコニ\nスウジ ヲ ツメコム\nシゴトヲ シテイマシタ" },
	{ L"デンシャ トハ\nナンナノデショウカ" },
	{ L"ツミト バツハ\nオナジモノ デスヨ" },

	};

	const wchar_t Zatsudan_2[25][255]{
	{ L"ナカマノ タマシイガ\n「ポイント」ノ\nショウタイ デス" },
	{ L"タベラレル モノ ハ\nモウイナイノデスガ..." },
	{ L"「イト」ガ\nヨメマセンカラネ\n...クモ ダケニ" },
	{ L"タマニハ\nリフレッシュ モ\nヒツヨウ デスネ" },
	{ L"ワタシハ...\nコノカラダ デスカネ" },
	{ L"ワタシ ガ\nウマレタトキノ\nメッセージ デス" },
	{ L"ザツダン ヨリ\nユウイギ ニ\nツカウベキ デハ？" },
	{ L"カレ モ\nカギラレタ イノチ デ\nイキテイルノ デショウカ" },
	{ L"モンスター ガ\nハヤク マワリマス\nグルグル マワリマス" },
	{ L"イゼンノ ワタシガ\nカタヅケタ ヨウデスネ" },
	{ L"ソトノ セカイハ\nドウナッテ\nイルノデショウ" },
	{ L"ワタシ ッテ ジツハ...\nニンゲン ジャ\nアリマセン！" },
	{ L"ロマンティック\nデスヨネ\nウラヤマシイ デス" },
	{ L"ワタシヲ オコラセルト\nヒッサツ ワザ..." },
	{ L"モット ハヤク\nキガ ツイテイレバ\nカエラレタ" },
	{ L"カタチガ カワルダケ\nデハ ナイノデスカ" },
	{ L"デハ ウタイマス\n（ノイズが きこえる）" },
	{ L"ハコヲ サグル \nヒビ ガ ズット\nツヅイテイマス" },
	{ L"ズカン ヲ\nカンセイ スルナラ\nサケテハ トオレマセン" },
	{ L"シナナイ ノナラ\nイシコロ ト\nカワリマセン" },//20
	{ L"ニンゲン ヲ\nデジタル カ スルト\nドウナルノデショウ" },
	{ L"イマデハ タダノ\nシチョウカク シツ\nデスネ" },
	{ L"トテモ タノシソウニ\nスウジヲ ツメテイマシタ" },
	{ L"イノチヲ タベル\nオソロシイ カイブツト\nキイテイマス" },
	{ L"ホンニン ノ\nイシ ナド カンケイ\nアリマセン" },

	};

	const wchar_t Zatsudan_3[25][255]{
	{ L"ムダヅカイ ハ\nイケマセンヨ\nノロワレマスヨ" },
	{ L"" },
	{ L"" },
	{ L"" },
	{ L"アア、ムダバナシガ\nスギマシタ\nオキニ ナサラズ" },
	{ L"" },
	{ L"ワタシガ\nイエタコト デハ\nアリマセンガ" },
	{ L"" },
	{ L"" },
	{ L"ジンセイ ノ カタヅケ\nッテ ヤツデスネ" },
	{ L"ダレモ イナイ？\n...ゴジョウダン ヲ" },
	{ L"............\nシッテ マシタ？\n...ソウデスカ" },
	{ L"" },
	{ L"シャイニングウィザード\nヲ オミマイ\nシマスカラネ" },
	{ L"...マスター ノ\nユイゴン デス" },
	{ L"ズット リカイ\nデキナイノデス" },
	{ L"" },
	{ L"マド ヲ タタキワッテ\nジユウニ ナリタイデスネ" },
	{ L"" },
	{ L"ナンダカ ワタシト\nニテイマスネ" },//20
	{ L"テレポート モ\nカノウ デスカネ" },
	{ L"" },
	{ L"" },
	{ L"デンシャ ガ\nチカヅイテ キタラ\nニゲナイト イケマセンネ" },
	{ L"スベテ オナジ\nタダ ミカタ ガ\nチガウダケ デス" },

	};
};

