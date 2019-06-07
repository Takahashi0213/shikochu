#pragma once

const int Stage = 3; //ステージ数

//各ステージのWave数
const int Stage_Wave[Stage]{
	4,
	4,
	4,
};

//レベルファイル名
//テストプレイ用レベル名→level/level_Test.tkl
const wchar_t LevelName[12][255]{
{ L"level/level_00.tkl" },	//ステージ１
{ L"level/level_01.tkl" },
{ L"level/level_02.tkl" },
{ L"level/level_03.tkl" },	//Boss1
{ L"level/level_04.tkl" },	//ステージ２
{ L"level/level_05.tkl" },
{ L"level/level_06.tkl" },
{ L"level/level_07.tkl" },	//Boss2
{ L"level/level_08.tkl" },	//ステージ３
{ L"level/level_09.tkl" },
{ L"level/level_10.tkl" },
{ L"level/level_11.tkl" },	//Boss3

};

//ハードモード用レベルファイル名
//テストプレイ用レベル名→level/level_Test.tkl
const wchar_t LevelName_Hard[12][255]{
{ L"level/level_Test.tkl" },	//ステージ１
{ L"level/level_Test.tkl" },
{ L"level/level_Test.tkl" },
{ L"level/level_03.tkl" },	//Boss1
{ L"level/level_Test.tkl" },	//ステージ２
{ L"level/level_Test.tkl" },
{ L"level/level_Test.tkl" },
{ L"level/level_07.tkl" },	//Boss2
{ L"level/level_Test.tkl" },	//ステージ３
{ L"level/level_Test.tkl" },
{ L"level/level_Test.tkl" },
{ L"level/level_11.tkl" },	//Boss3

};

//ステージ別ボス名
const wchar_t BossName[Stage][128]{
{ L"シーソークス" },
{ L"パイロドラゴ" },
{ L"SS-001" },

};

//ステージ名
const wchar_t StageName[Stage][128]{
{ L"「イフェマラル・ディープシー」" },
{ L"「ヘイヴン・ヘヴン」" },
{ L"「ガラクシア」" },

};

//ちっこいステージのファイル名
const wchar_t StageMiniName[Stage][255]{
	{ L"modelData/StageMini1.cmo" },
	{ L"modelData/StageMini2.cmo" },
	{ L"modelData/StageMini3.cmo" },

};

//BGMのファイル名
const wchar_t BGMName[Stage][255]{
{ L"sound/sea.wav" },
{ L"sound/iseki.wav" },
{ L"sound/ikukan.wav" },
};

//ボスBGMのファイル名
const wchar_t BossBGMName[Stage][255]{
{ L"sound/seaSokus.wav" },
{ L"sound/pairodorago.wav" },
{ L"sound/SS_001.wav" },
};