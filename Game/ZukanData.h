#pragma once

//図鑑のデータベース

const int Monster = 5; //項目数

//モデル
const wchar_t MonsterModel[Monster][128]{
{ L"modelData/bunbo-gu0.cmo" },
{ L"modelData/neoriku_0.cmo" },
{ L"modelData/soukabuto_0.cmo" },
{ L"modelData/Neruk.cmo" },
{ L"modelData/shisokus.cmo" },

};

//アニメーション
const wchar_t MonsterAnime[Monster][128]{
{ L"animData/walk.tka" },
{ L"animData/Neowalk.tka" },
{ L"animData/souwalk.tka" },
{ L"animData/Neruwalk.tka" },
{ L"animData/sisowalk.tka" },

};

//モンスター名
const wchar_t MonsterName[Monster][128]{
{ L"ブンローグ" },
{ L"ネオリク" },
{ L"ソウカブト" },
{ L"ネルク" },
{ L"シーソークス" },

};

//説明文 1行14文字までがちょうどいい
const wchar_t Setumei[Monster][255]{
{ L"ブンローグのせつめい" },
{ L"ネオリクのせつめい" },
{ L"ソウカブトのせつめ" },
{ L"ネルクのアレ" },
{ L"シーソークスの〜" },

};

//図鑑用スケール
const CVector3 M_Scale[Monster]{
	{ 2.0f,2.0f,2.0f },
	{ 2.0f,2.0f,2.0f },
	{ 2.0f,2.0f,2.0f },
	{ 2.0f,2.0f,2.0f },
	{ 0.5f,0.5f,0.5f },

};

//図鑑用Y補正
const float Y_Hosei[Monster]{
	{ 0.0f },
	{ 0.0f },
	{ -60.0f },
	{ 0.0f },
	{ 0.0f },

};