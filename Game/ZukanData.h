#pragma once

//�}�ӂ̃f�[�^�x�[�X

const int Monster = 33; //���ڐ�

//���f��
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

//�A�j���[�V����
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

//�U���A�j���̗L��
const bool MonsterATK_Flag[Monster]{
	true,
	false,
	false,
	false,
	true,
	false,
	false,
	true,
	true,//�x�j�e�[
	true,
	false,
	true,//�������`��
	false,
	false,
	false,//�`�Y�`���E
	true,
	false,
	true,//�e�B���I�X�J
	false,
	false,
	true,
	true,
	false,
	true,
	true,//�C�[�_���h
	false,
	false,
	true,
	false,
	false,
	false,
	false,//�X���[�N
	false,

};

//�U���A�j���[�V����
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

//�����X�^�[��
const wchar_t MonsterName[Monster][128]{
{ L"�u�����[�O" },
{ L"�l�I���N" },
{ L"�\�E�J�u�g" },
{ L"�l���N" },
{ L"�V�[�\�[�N�X" },
{ L"�L�R�E�`���E" },
{ L"�E�~�m�E�V" },
{ L"�A�R���h�J��" },
{ L"�x�j�e�[" },
{ L"�j�[�{�[" },
{ L"�Z�N�e�B��" },
{ L"�������`��" },
{ L"�L���r��" },
{ L"�X�e�B��" },
{ L"�`�Y�`���E" },
{ L"�N�[�{" },
{ L"�g���s�s" },
{ L"�e�B���I�X�J" },
{ L"�A�c�J��" },
{ L"���g�|���X" },
{ L"�G�b�N" },
{ L"�s�[���r" },
{ L"�t�@�C��" },
{ L"�p�C���h���S" },
{ L"�C�[�_���h" },
{ L"�R�_��" },
{ L"�^�C�h��" },
{ L"�����R��" },
{ L"�����b�g" },
{ L"�A���J�V��" },
{ L"SS-001" },
{ L"�X���[�N" },
{ L"�~�~�b�g" },

};

//������ 1�s14�����܂ł����傤�ǂ���
const wchar_t Setumei[Monster][255]{
{ L"���ł� ���񂩂����傤�� ��\n��������͂�������\n���Ă��邼�I" },
{ L"������Ƃ������Ƃ���\n�܂ق����� �������Ă���\n���݂̂����ꂢ�B" },
{ L"�����������������āA\n�Ƃ��ǂ� ����������������\n�Ƃ����񂵂Ă��邼�I" },
{ L"�V�[�\�[�N�X�̂��ǂ��B\n���܂��܂ł�\n�W�˂񂩂���炵���B" },
{ L"�l�R�~�~ �̂͂����T���B\n���킢���Ƃ����ăO�����B\n�V�b�|�̓`�F�[���\�[�����B" },
{ L"�V�R�E�`���E�̂��񂹂��B\n�������� �{�[�i�X�X�R�A��\n����� �������c���B" },
{ L"���݂ɂ��ރE�V�B\n���ڂ�� ��������\n���イ�ɂイ�� �łĂ���B" },
{ L"�J�j�̂悤�ȃ��h�J���B\n���݂̂Ȃ��̓q�}�Ȃ̂�\n�������� �{�N�V���O ���͂��߂��B" },
{ L"�����݂��� ��������\n�����傤�� �G���[�g�B\n������ւ�̃^�P�Ƃ͂������̂��B" },
{ L"���ꂽ�T�{�e���� ���܂�����\n��ǂ����������B\n�����܂� ������ ��邢�B" },
{ L"�Ƃ����񂵂Ă��� ���񂽂��A���B\n���� �����҂��I�I�J�~ ��\n��������Ă���B" },
{ L"�������� ����̂��傶��B\n���炾�� ������������\n��� �� �܂�������B" },
{ L"���킢�炵�� �Ȃ܂������A\n���イ�˂�Ԃ��� ���������B\n���� �� �������� ���B" },
{ L"�������� �����Ă�����\n�������� 2�����˂� �˂��������B\n���肠���� ���Ȃ��� �������Ă���B" },
{ L"�����ꂽ ������\n����� �Ƃт͂��߂��B\n�݂��� �ɂ��āB" },
{ L"���Ă�ꂽ �ڂ�����\n���܂����� ��ǂ����B\n�����Ȃ��̂� �����肵�傤���B" },
{ L"���ǂ��̂��� ���ӂ��\n�Ƃ��� �������\n�Ȃ��� �������́B" },
{ L"���񂵂�A�Ђ������A�ɂ񂰂�\n3�̂������� ����\n�������� ���{�b�g�B" },
{ L"UG���g���� �����������{�B\n�\�E�J�u�g �̂��Ƃ�\n���C�o���� ���Ă���B" },
{ L"UG���g���� �����у��{�B\n�����Ă��邪\n���イ�肷�� �ЂƂ����Ȃ��B" },
{ L"���₵���݂��߂���\n��傤�肪����݁B\n�Ƃ�����傤��� �߂��܂₫�B" },
{ L"���͂ɂ����傭�����ŁA\n�Ă����肵������\n�������邼�I" },
{ L"��������ׂ�h���S���B\n�_�C�G�b�g�̂��߂�\n�Ƃ����񂷂�I" },
{ L"����ǂ��납 ��������\n���ׂĂ��܂���\n�t�@�C�� �� ���₾�܁B" },
{ L"�T�C�R���� �悤�����B\n���������� �R�_����\n3���� ���傤���񂷂�B" },
{ L"�C�[�_���h�� ���ǂ��B\n���܂܂� ���ǂ�����\n���܂���� ���������B" },
{ L"�����ނ����� �����イ��\n�C���[�W���� ����ꂽ\n������������Ђ�B" },
{ L"�悭�݂�Ƃ��킢�� ��\n�t�@���O�b�Y �� ��������\n����Ă���Ƃ��B" },
{ L"�ɂ���邢�� �܂ق����� ��\n�����Ƃ��ł���A\nAI�X�s�[�J�[�B" },
{ L"���̂킷�� ���͂������̂�\n�͂��������Ƃ�\n�o�b�N�ł��ǂ��Ă��邼�I" },
{ L"���݂ɂ����� ���񂩂� ��\n�V�[�\�[�N�X�̂��ł񂵂�\n���킳�����������B" },
{ L"���{�Ȃ̂� �|�G����\n�����̂� ����݁B\n�x�X�g�Z���[�������B" },
{ L"�݂炢�̃��{�b�g�B\n�����b�g�� �܂񂴂�\n�R���r������ł���B" },

};

//�}�ӗp�X�P�[��
const CVector3 M_Scale[Monster]{
{ 2.0f,2.0f,2.0f },
{ 2.0f,2.0f,2.0f },
{ 2.0f,2.0f,2.0f },
{ 2.0f,2.0f,2.0f },
{ 0.5f,0.5f,0.5f },//�V�[�\�[�N�X
{ 2.0f,2.0f,2.0f },
{ 1.0f,1.0f,1.0f },
{ 2.0f,2.0f,2.0f },
{ 0.5f,0.5f,0.5f },//�x�j�e�[
{ 2.0f,2.0f,2.0f },
{ 50.0f,50.0f,50.0f },
{ 4.0f,4.0f,4.0f },//�������`��
{ 1.0f,1.0f,1.0f },
{ 50.0f,50.0f,50.0f },
{ 2.0f,2.0f,2.0f },//�`�Y�`���E
{ 1.5f,1.5f,1.5f },
{ 2.0f,2.0f,2.0f },
{ 10.0f,10.0f,10.0f },//�e�B���I�X�J
{ 3.0f,3.0f,3.0f },
{ 3.0f,3.0f,3.0f },
{ 2.0f,2.0f,2.0f },
{ 30.0f,30.0f,30.0f },
{ 1.0f,1.0f,1.0f },
{ 20.0f, 20.0f, 20.0f },
{ 1.0f,1.0f,1.0f },//�C�[�_���h
{ 1.0f,1.0f,1.0f },
{ 1.5f,1.5f,1.5f },
{ 20.0f, 20.0f, 20.0f },
{ 1.0f,1.0f,1.0f },
{ 2.0f,2.0f,2.0f },
{ 0.5f,0.5f,0.5f },
{ 2.0f,2.0f,2.0f },//�X���[�N
{ 150.0f,150.0f,150.0f },

};

//�}�ӗpX�␳
const float X_Hosei[Monster]{
	{ 0.0f },
{ 0.0f },
{ 50.0f },
{ 0.0f },
{ 0.0f },//�V�[�\�[�N�X
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 20.0f },//�x�j�e�[
{ 20.0f },
{ 0.0f },
{ 40.0f },//�������`��
{ 20.0f },
{ 0.0f },
{ 0.0f },//�`�Y�`���E
{ 0.0f },
{ 0.0f },
{ 0.0f },//�e�B���I�X�J
{ 20.0f },
{ 20.0f },
{ 50.0f },
{ 20.0f },
{ 20.0f },
{ 20.0f },
{ 0.0f },//�C�[�_���h
{ 0.0f },
{ 10.0f },
{ 50.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 20.0f },
{ 20.0f },

};

//�}�ӗpY�␳
const float Y_Hosei[Monster]{
	{ 0.0f },
	{ 0.0f },
	{ -60.0f },
	{ 0.0f },
	{ 0.0f },
	{ -10.0f },
	{ 0.0f },
	{ -30.0f },
{ -40.0f },//�x�j�e�[
{ -50.0f },
{ -30.0f },
{ -100.0f },//�������`��
{ -40.0f },
{ 0.0f },
{ 0.0f },//�`�Y�`���E
{ 0.0f },
{ 0.0f },
{ -50.0f },//�e�B���I�X�J
{ -50.0f },
{ -70.0f },
{ -50.0f },
	{ -50.0f },
	{ -50.0f },
	{ -100.0f },
{ -30.0f },//�C�[�_���h
{ 0.0f },
{ -50.0f },
{ -160.0f },
{ 0.0f },
{ -60.0f },
{ 0.0f },
{ -30.0f },
{ -60.0f },

};

//�}�ӗpZ�␳
const float Z_Hosei[Monster]{
	{ 0.0f },
{ 0.0f },
{ -100.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },//�x�j�e�[
{ 0.0f },
{ 0.0f },
{ 0.0f },//�������`��
{ 0.0f },
{ 0.0f },
{ 0.0f },//�`�Y�`���E
{ 0.0f },
{ 0.0f },
{ 0.0f },//�e�B���I�X�J
{ 0.0f },
{ 0.0f },
{ -100.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },//�C�[�_���h
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },

};