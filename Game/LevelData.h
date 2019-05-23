#pragma once

const int Stage = 2; //ステージ数

//各ステージのWave数
const int Stage_Wave[Stage]{
	2,
	4,
};

//レベルファイル名
//テストプレイ用レベル名→level/level_Test.tkl
const wchar_t LevelName[10][255]{
{ L"level/level_Test.tkl" },
{ L"level/level_03.tkl" },
{ L"level/level_02.tkl" },
{ L"level/level_03.tkl" }, //Boss
{ L"level/level_Test.tkl" },//ここからステージ２

};

//ステージ別ボス名
const wchar_t BossName[Stage][128]{
{ L"シーソークス" },

};

//ステージ名
const wchar_t StageName[Stage][128]{
	{ L"イフェマラル・ディープシー" },
	{ L"ヘイヴン・ヘヴン" },

};

//ちっこいステージのファイル名
const wchar_t StageMiniName[Stage][255]{
	{ L"modelData/StageMini1.cmo" },
	{ L"modelData/StageMini2.cmo" },
};