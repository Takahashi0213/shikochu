#pragma once

//�}�ӂ̃f�[�^�x�[�X

const int Monster = 13; //���ڐ�

//���f��
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

//�A�j���[�V����
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

//�U���A�j���̗L��
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

//�U���A�j���[�V����
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

//�����X�^�[��
const wchar_t MonsterName[Monster][128]{
{ L"�u�����[�O" },
{ L"�l�I���N" },
{ L"�\�E�J�u�g" },
{ L"�l���N" },
{ L"�V�[�\�[�N�X" },
{ L"�G�b�N" },
{ L"�s�[���r" },
{ L"�t�@�C��" },
{ L"�p�C���h���S" },
{ L"�����R��" },
{ L"�����b�g" },
{ L"�A���J�V��" },
{ L"SS-001" },

};

//������ 1�s14�����܂ł����傤�ǂ���
const wchar_t Setumei[Monster][255]{
{ L"���ł� ���񂩂����傤�� ��\n��������͂�������\n���Ă��邼�I" },
{ L"������Ƃ������Ƃ���\n�܂ق����� �������Ă���\n���݂̂����ꂢ�B" },
{ L"�����������������āA\n�Ƃ��ǂ� ����������������\n�Ƃ����񂵂Ă��邼�I" },
{ L"�V�[�\�[�N�X�̂��ǂ��B\n���܂��܂ł�\n�W�˂񂩂���炵���B" },
{ L"�l�R�~�~ �̂͂����T���B\n���킢���Ƃ����ăO�����B\n�V�b�|�̓`�F�[���\�[�����B" },
{ L"���₵���݂��߂���\n��傤�肪����݁B\n�Ƃ�����傤��� �߂��܂₫�B" },
{ L"���͂ɂ����傭�����ŁA\n�Ă����肵������\n�������邼�I" },
{ L"��������ׂ�h���S���B\n�_�C�G�b�g�̂��߂�\n�Ƃ����񂷂�I" },
{ L"����ǂ��납 ��������\n���ׂĂ��܂���\n�t�@�C�� �� ���₾�܁B" },
{ L"�悭�݂�Ƃ��킢�� ��\n�t�@���O�b�Y �� ��������\n����Ă���Ƃ��B" },
{ L"�ɂ���邢�� �܂ق����� ��\n�����Ƃ��ł���A\nAI�X�s�[�J�[�B" },
{ L"���̂킷�� ���͂������̂�\n�͂��������Ƃ�\n�o�b�N�ł��ǂ��Ă��邼�I" },
{ L"���݂ɂ����� ���񂩂� ��\n�V�[�\�[�N�X�̂��ł񂵂�\n���킳�����������B" },

};

//�}�ӗp�X�P�[��
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

//�}�ӗpX�␳
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

//�}�ӗpY�␳
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

//�}�ӗpZ�␳
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