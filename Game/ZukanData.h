#pragma once

//図鑑のデータベース

const int Monster = 13; //項目数

//モデル
const wchar_t MonsterModel[Monster][128]{
{ L"modelData/bunbo-gu0.cmo" },
{ L"modelData/neoriku_0.cmo" },
{ L"modelData/soukabuto_0.cmo" },
{ L"modelData/Neruk.cmo" },
{ L"modelData/shisokus.cmo" },
{ L"modelData/Ekku.cmo" },
{ L"modelData/Rabbit_Level_1.cmo" },
{ L"modelData/Fairo.cmo" },
{ L"modelData/DragonTerrorBringerMesh.cmo" },
{ L"modelData/Bat_Level_1.cmo" },
{ L"modelData/Riritto.cmo" },
{ L"modelData/Arukasya.cmo" },
{ L"modelData/SS_001.cmo" },

};

//アニメーション
const wchar_t MonsterAnime[Monster][128]{
{ L"animData/walk.tka" },
{ L"animData/Neowalk.tka" },
{ L"animData/souwalk.tka" },
{ L"animData/Neruwalk.tka" },
{ L"animData/sisowalk.tka" },
{ L"animData/Ekwalk.tka" },
{ L"animData/P_idel.tka" },
{ L"animData/Faiwalk.tka" },
{ L"animData/piro_Bigidle.tka" },
{ L"animData/Mori_idel.tka" },
{ L"animData/Ririwalk.tka" },
{ L"animData/Aruwalk.tka" },
{ L"animData/SSwalk.tka" },

};

//攻撃アニメの有無
const bool MonsterATK_Flag[Monster]{
	true,
	false,
	false,
	false,
	true,
	true,
	true,
	false,
	true,
	true,
	false,
	false,
	false,
};

//攻撃アニメーション
const wchar_t MonsterAnime_ATK[Monster][128]{
{ L"animData/Bunattack_Z.tka" },
{ L"" },
{ L"" },
{ L"" },
{ L"animData/Sisoattack_Z.tka" },
{ L"animData/Ekattack_Z.tka" },
{ L"animData/P_attack.tka" },
{ L"" },
{ L"animData/Piro_Bigattack4.tka" },
{ L"animData/Mori_attack.tka" },
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
{ L"エック" },
{ L"ピーラビ" },
{ L"ファイロ" },
{ L"パイロドラゴ" },
{ L"モリコン" },
{ L"リリット" },
{ L"アルカシャ" },
{ L"SS-001" },

};

//説明文 1行14文字までがちょうどいい
const wchar_t Setumei[Monster][255]{
{ L"うでの さんかくじょうぎ で\nこちらをはさもうと\nしてくるぞ！" },
{ L"こちらときょりをとって\nまほうだん をうってくる\nうみのせいれい。" },
{ L"そうじがすきすぎて、\nときどき すごいいきおいで\nとっしんしてくるぞ！" },
{ L"シーソークスのこども。\nうまれるまでに\n８ねんかかるらしい。" },
{ L"ネコミミ のはえたサメ。\nかわいいといわれてグレた。\nシッポはチェーンソーだぞ。" },
{ L"あやしいみためだが\nりょうりがしゅみ。\nとくいりょうりは めだまやき。" },
{ L"じつはにくしょくけいで、\nてあたりしだいに\nずつきするぞ！" },
{ L"いわをたべるドラゴン。\nダイエットのために\nとっしんする！" },
{ L"いわどころか いせきを\nたべてしまった\nファイロ の おやだま。" },
{ L"よくみるとかわいい と\nファングッズ が せいさく\nされているとか。" },
{ L"にしゅるいの まほうだん を\nうつことができる、\nAIスピーカー。" },
{ L"ものわすれ がはげしいので\nはしったあとに\nバックでもどってくるぞ！" },
{ L"うみにしずんだ せんかん に\nシーソークスのいでんしが\nあわさったすがた。" },

};

//図鑑用スケール
const CVector3 M_Scale[Monster]{
	{ 2.0f,2.0f,2.0f },
	{ 2.0f,2.0f,2.0f },
	{ 2.0f,2.0f,2.0f },
	{ 2.0f,2.0f,2.0f },
	{ 0.5f,0.5f,0.5f },
	{ 2.0f,2.0f,2.0f },
	{ 30.0f,30.0f,30.0f },
	{ 1.0f,1.0f,1.0f },
	{ 20.0f, 20.0f, 20.0f },
{ 20.0f, 20.0f, 20.0f },
{ 1.0f,1.0f,1.0f },
{ 2.0f,2.0f,2.0f },
{ 0.5f,0.5f,0.5f },

};

//図鑑用X補正
const float X_Hosei[Monster]{
	{ 0.0f },
{ 0.0f },
{ 50.0f },
{ 0.0f },
{ 0.0f },
{ 50.0f },
{ 20.0f },
{ 20.0f },
{ 20.0f },
{ 50.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },

};

//図鑑用Y補正
const float Y_Hosei[Monster]{
	{ 0.0f },
	{ 0.0f },
	{ -60.0f },
	{ 0.0f },
	{ 0.0f },
	{ -50.0f },
	{ -50.0f },
	{ -50.0f },
	{ -100.0f },
{ -160.0f },
{ 0.0f },
{ -60.0f },
{ 0.0f },

};

//図鑑用Z補正
const float Z_Hosei[Monster]{
	{ 0.0f },
{ 0.0f },
{ -100.0f },
{ 0.0f },
{ 0.0f },
{ -100.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },

};