#pragma once

//各ステージのWave数
int Stage_Wave[5]{
	2,
	0,
	0,
	0,
	0,
};

//レベルファイル名
//テストプレイ用レベル名→level/level_Test.tkl
wchar_t LevelName[5][255]{
{ L"level/level_Test.tkl" },
{ L"level/level_03.tkl" }, //Boss
{ L"level/level_01.tkl" },
{ L"level/level_02.tkl" },

};

//レベルファイル名
wchar_t BossName[5][255]{
{ L"シーソークス" },

};
