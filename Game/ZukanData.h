#pragma once

//図鑑のデータベース

const int Monster = 33; //項目数

//モデル
const wchar_t MonsterModel[Monster][128]{
{ L"modelData/bunbo-gu0.cmo" },
{ L"modelData/neoriku_0.cmo" },
{ L"modelData/soukabuto_0.cmo" },
{ L"modelData/Neruk.cmo" },
{ L"modelData/shisokus.cmo" },
{ L"modelData/Kikochu.cmo" },
{ L"modelData/umino.cmo" },
{ L"modelData/Akoyadokari.cmo" },
{ L"modelData/Benite.cmo" },
{ L"modelData/Nibo.cmo" },
{ L"modelData/Sekuteia.cmo" },
{ L"modelData/kyozin.cmo" },
{ L"modelData/Kirabin.cmo" },
{ L"modelData/Suteira.cmo" },
{ L"modelData/Tizutyo.cmo" },
{ L"modelData/Kuubo.cmo" },
{ L"modelData/toripp.cmo" },
{ L"modelData/Teruosuka.cmo" },
{ L"modelData/Atsukaru.cmo" },
{ L"modelData/Metoporisu.cmo" },
{ L"modelData/Ekku.cmo" },
{ L"modelData/Rabbit_Level_1.cmo" },
{ L"modelData/Fairo.cmo" },
{ L"modelData/DragonTerrorBringerMesh.cmo" },
{ L"modelData/Idando.cmo" },
{ L"modelData/Kodan.cmo" },
{ L"modelData/Taidol.cmo" },
{ L"modelData/Bat_Level_1.cmo" },
{ L"modelData/Riritto.cmo" },
{ L"modelData/Arukasya.cmo" },
{ L"modelData/SS_001.cmo" },
{ L"modelData/Suroku.cmo" },
{ L"modelData/Mimitto.cmo" },

};

//アニメーション
const wchar_t MonsterAnime[Monster][128]{
{ L"animData/walk.tka" },
{ L"animData/Neowalk.tka" },
{ L"animData/souwalk.tka" },
{ L"animData/Neruwalk.tka" },
{ L"animData/sisowalk.tka" },
{ L"animData/KikoWalk.tka" },
{ L"animData/umiWalk.tka" },
{ L"animData/AkoWalk.tka" },
{ L"animData/BeniteWalk.tka" },
{ L"animData/NiboWalk.tka" },
{ L"animData/SektWalk.tka" },
{ L"animData/kyo_idle.tka" },
{ L"animData/Kira_Move.tka" },
{ L"animData/Sute_Run.tka" },
{ L"animData/Tizutyo.tka" },
{ L"animData/KuuboWalk.tka" },
{ L"animData/Toripipi.tka" },
{ L"animData/Teru_TankWait.tka" },
{ L"animData/Atsukaru.tka" },
{ L"animData/Metoporisu.tka" },
{ L"animData/Ekwalk.tka" },
{ L"animData/P_idel.tka" },
{ L"animData/Faiwalk.tka" },
{ L"animData/piro_Bigidle.tka" },
{ L"animData/Ida_Stay.tka" },
{ L"animData/Kodan_Walk.tka" },
{ L"animData/Taidol.tka" },
{ L"animData/Mori_idel.tka" },
{ L"animData/Ririwalk.tka" },
{ L"animData/Aruwalk.tka" },
{ L"animData/SSwalk.tka" },
{ L"animData/Suroku.tka" },
{ L"animData/Mimitto.tka" },

};

//攻撃アニメの有無
const bool MonsterATK_Flag[Monster]{
	true,
	false,
	false,
	false,
	true,
	false,
	false,
	true,
	true,//ベニテー
	true,
	false,
	true,//モリンチュ
	false,
	false,
	false,//チズチョウ
	true,
	false,
	true,//ティルオスカ
	false,
	false,
	true,
	true,
	false,
	true,
	true,//イーダンド
	false,
	false,
	true,
	false,
	false,
	false,
	false,//スローク
	false,

};

//攻撃アニメーション
const wchar_t MonsterAnime_ATK[Monster][128]{
{ L"animData/Bunattack_Z.tka" },
{ L"" },
{ L"" },
{ L"" },
{ L"animData/Sisoattack_Z.tka" },
{ L"" },
{ L"" },
{ L"animData/AkoFull.tka" },
{ L"animData/BeniAttackFull.tka" },
{ L"animData/NiboAttack.tka" },
{ L"" },
{ L"animData/kyo_attack.tka" },
{ L"" },
{ L"" },
{ L"" },
{ L"animData/KuuboAttack.tka" },
{ L"" },
{ L"animData/Teru_TankAttack.tka" },
{ L"" },
{ L"" },
{ L"animData/Ekattack_Z.tka" },
{ L"animData/P_attack.tka" },
{ L"" },
{ L"animData/Piro_Bigattack4.tka" },
{ L"animData/Ida_Full.tka" },
{ L"" },
{ L"" },
{ L"animData/Mori_attack.tka" },
{ L"" },
{ L"" },
{ L"" },
{ L"" },
{ L"" },

};

//モンスター名
const wchar_t MonsterName[Monster][128]{
{ L"ブンローグ" },
{ L"ネオリク" },
{ L"ソウカブト" },
{ L"ネルク" },
{ L"シーソークス" },
{ L"キコウチュウ" },
{ L"ウミノウシ" },
{ L"アコヤドカリ" },
{ L"ベニテー" },
{ L"ニーボー" },
{ L"セクティム" },
{ L"モリンチュ" },
{ L"キラビン" },
{ L"スティラ" },
{ L"チズチョウ" },
{ L"クーボ" },
{ L"トリピピ" },
{ L"ティルオスカ" },
{ L"アツカル" },
{ L"メトポリス" },
{ L"エック" },
{ L"ピーラビ" },
{ L"ファイロ" },
{ L"パイロドラゴ" },
{ L"イーダンド" },
{ L"コダン" },
{ L"タイドル" },
{ L"モリコン" },
{ L"リリット" },
{ L"アルカシャ" },
{ L"SS-001" },
{ L"スローク" },
{ L"ミミット" },

};

//説明文 1行14文字までがちょうどいい
const wchar_t Setumei[Monster][255]{
{ L"うでの さんかくじょうぎ で\nこちらをはさもうと\nしてくるぞ！" },
{ L"こちらときょりをとって\nまほうだん をうってくる\nうみのせいれい。" },
{ L"そうじがすきすぎて、\nときどき すごいいきおいで\nとっしんしてくるぞ！" },
{ L"シーソークスのこども。\nうまれるまでに\n８ねんかかるらしい。" },
{ L"ネコミミ のはえたサメ。\nかわいいといわれてグレた。\nシッポはチェーンソーだぞ。" },
{ L"シコウチュウのしんせき。\nたおすと ボーナススコアを\nくれる いいヤツだ。" },
{ L"うみにすむウシ。\nしぼると おいしい\nぎゅうにゅうが でてくる。" },
{ L"カニのようなヤドカリ。\nうみのなかはヒマなので\nさいきん ボクシング をはじめた。" },
{ L"こうみえて だいがく\nそつぎょうの エリート。\nそこらへんのタケとはちがうのだ。" },
{ L"かれたサボテンに たましいが\nやどったすがた。\nあたまが すごく わるい。" },
{ L"とっしんしてくる ぐんたいアリ。\nじつは いっぴきオオカミ に\nあこがれている。" },
{ L"たたずむ もりのきょじん。\nからだが おおきすぎて\nやま と まちがわれる。" },
{ L"かわいらしい なまえだが、\nしゅうねんぶかい せいかく。\nこい も こうげき も。" },
{ L"かくれんぼ をしていたら\nうっかり 2おくねん ねすごした。\nしりあいが いなくて あせっている。" },
{ L"ちぎれた ちずが\nそらを とびはじめた。\nみずが にがて。" },
{ L"すてられた ぼうしに\nたましいが やどった。\nすきなものは すいりしょうせつ。" },
{ L"こどものいる おふろに\nとつぜん あらわれる\nなぞの いきもの。" },
{ L"せんしゃ、ひこうき、にんげん\n3つのすがたを もつ\nこだいの ロボット。" },
{ L"UGメトロの せいそうロボ。\nソウカブト のことを\nライバルし している。" },
{ L"UGメトロの けいびロボ。\nこわれているが\nしゅうりする ひとがいない。" },
{ L"あやしいみためだが\nりょうりがしゅみ。\nとくいりょうりは めだまやき。" },
{ L"じつはにくしょくけいで、\nてあたりしだいに\nずつきするぞ！" },
{ L"いわをたべるドラゴン。\nダイエットのために\nとっしんする！" },
{ L"いわどころか いせきを\nたべてしまった\nファイロ の おやだま。" },
{ L"サイコロの ようさい。\nたおされると コダンを\n3たい しょうかんする。" },
{ L"イーダンドの こども。\nきままに いどうする\nきまぐれな せいかく。" },
{ L"おおむかしの ちきゅうを\nイメージして つくられた\nげいじゅつさくひん。" },
{ L"よくみるとかわいい と\nファングッズ が せいさく\nされているとか。" },
{ L"にしゅるいの まほうだん を\nうつことができる、\nAIスピーカー。" },
{ L"ものわすれ がはげしいので\nはしったあとに\nバックでもどってくるぞ！" },
{ L"うみにしずんだ せんかん に\nシーソークスのいでんしが\nあわさったすがた。" },
{ L"ロボなのに ポエムを\nかくのが しゅみ。\nベストセラーさっか。" },
{ L"みらいのロボット。\nリリットと まんざい\nコンビをくんでいる。" },

};

//図鑑用スケール
const CVector3 M_Scale[Monster]{
{ 2.0f,2.0f,2.0f },
{ 2.0f,2.0f,2.0f },
{ 2.0f,2.0f,2.0f },
{ 2.0f,2.0f,2.0f },
{ 0.5f,0.5f,0.5f },//シーソークス
{ 2.0f,2.0f,2.0f },
{ 1.0f,1.0f,1.0f },
{ 2.0f,2.0f,2.0f },
{ 0.5f,0.5f,0.5f },//ベニテー
{ 2.0f,2.0f,2.0f },
{ 50.0f,50.0f,50.0f },
{ 4.0f,4.0f,4.0f },//モリンチュ
{ 1.0f,1.0f,1.0f },
{ 50.0f,50.0f,50.0f },
{ 2.0f,2.0f,2.0f },//チズチョウ
{ 1.5f,1.5f,1.5f },
{ 2.0f,2.0f,2.0f },
{ 10.0f,10.0f,10.0f },//ティルオスカ
{ 3.0f,3.0f,3.0f },
{ 3.0f,3.0f,3.0f },
{ 2.0f,2.0f,2.0f },
{ 30.0f,30.0f,30.0f },
{ 1.0f,1.0f,1.0f },
{ 20.0f, 20.0f, 20.0f },
{ 1.0f,1.0f,1.0f },//イーダンド
{ 1.0f,1.0f,1.0f },
{ 1.5f,1.5f,1.5f },
{ 20.0f, 20.0f, 20.0f },
{ 1.0f,1.0f,1.0f },
{ 2.0f,2.0f,2.0f },
{ 0.5f,0.5f,0.5f },
{ 2.0f,2.0f,2.0f },//スローク
{ 150.0f,150.0f,150.0f },

};

//図鑑用X補正
const float X_Hosei[Monster]{
	{ 0.0f },
{ 0.0f },
{ 50.0f },
{ 0.0f },
{ 0.0f },//シーソークス
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 20.0f },//ベニテー
{ 20.0f },
{ 0.0f },
{ 40.0f },//モリンチュ
{ 20.0f },
{ 0.0f },
{ 0.0f },//チズチョウ
{ 0.0f },
{ 0.0f },
{ 0.0f },//ティルオスカ
{ 20.0f },
{ 20.0f },
{ 50.0f },
{ 20.0f },
{ 20.0f },
{ 20.0f },
{ 0.0f },//イーダンド
{ 0.0f },
{ 10.0f },
{ 50.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 20.0f },
{ 20.0f },

};

//図鑑用Y補正
const float Y_Hosei[Monster]{
	{ 0.0f },
	{ 0.0f },
	{ -60.0f },
	{ 0.0f },
	{ 0.0f },
	{ -10.0f },
	{ 0.0f },
	{ -30.0f },
{ -40.0f },//ベニテー
{ -50.0f },
{ -30.0f },
{ -100.0f },//モリンチュ
{ -40.0f },
{ 0.0f },
{ 0.0f },//チズチョウ
{ 0.0f },
{ 0.0f },
{ -50.0f },//ティルオスカ
{ -50.0f },
{ -70.0f },
{ -50.0f },
	{ -50.0f },
	{ -50.0f },
	{ -100.0f },
{ -30.0f },//イーダンド
{ 0.0f },
{ -50.0f },
{ -160.0f },
{ 0.0f },
{ -60.0f },
{ 0.0f },
{ -30.0f },
{ -60.0f },

};

//図鑑用Z補正
const float Z_Hosei[Monster]{
	{ 0.0f },
{ 0.0f },
{ -100.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },//ベニテー
{ 0.0f },
{ 0.0f },
{ 0.0f },//モリンチュ
{ 0.0f },
{ 0.0f },
{ 0.0f },//チズチョウ
{ 0.0f },
{ 0.0f },
{ 0.0f },//ティルオスカ
{ 0.0f },
{ 0.0f },
{ -100.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },//イーダンド
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },

};