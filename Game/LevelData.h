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
{ L"level/level_00.tkl" },
{ L"level/level_01.tkl" },
{ L"level/level_02.tkl" },
{ L"level/level_03.tkl" }, //Boss
{ L"level/level_Test.tkl" },//ここからステージ２
{ L"level/level_Test.tkl" },//ここからステージ２
{ L"level/level_Test.tkl" },//ここからステージ２
{ L"level/level_03.tkl" },//ここからステージ２
{ L"level/level_Test.tkl" },//ここからステージ２
{ L"level/level_Test.tkl" },//ここからステージ２
{ L"level/level_Test.tkl" },//ここからステージ２
{ L"level/level_03.tkl" },//ここからステージ２

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
{ L"sound/iseki.wav" },
};

//ボスBGMのファイル名
const wchar_t BossBGMName[Stage][255]{
	{ L"sound/seaSokus.wav" },
{ L"sound/seaSokus.wav" },
{ L"sound/seaSokus.wav" },
};