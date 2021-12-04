// skrbcr/Novel_Engine ver.0.1.0�ihttps://github.com/skrbcr/Novel_Engine�j
// DX���C�u�����g�p�̃m�x���Q�[���G���W���H�̃A���t�@��
// 
// �z�z�\�[�X�R�[�h�̈ꕔ�ɁA�ȉ��̃��C�u�������܂݂܂�
// ���쌠�\�����̏ڍׂ́AREADME.md��������������
// �Enlohmann/json�i https://github.com/nlohmann/json �jversion 3.9.1
// �Ejavacommons/strconv�i https://github.com/javacommons/strconv �jv1.8.10
// 
// �܂��A�{�\�t�g�� DX���C�u�����iVer3.23 https://dxlib.xsrv.jp/ �j���g�p���Ă��܂���
// �z�z�\�[�X�R�[�h�ɂ͊܂�ł���܂���̂ŁA�r���h�������́A�e�ʂł̃_�E�����[�h��ݒ蓙�����肢�������܂�
// 

#include "DxLib.h"
#include "nlohmann/json.hpp"
#include "javacommons/strconv.h"
#include "Global.h"
#include "Menu.h"
#include "Place.h"
#include "Choice.h"
#include "Button.h"
#include "BGM.h"
#include "Title.h"

namespace Game {
	static Title title;		// �^�C�g��

	// �e��n���h���̍쐬
	static void MakeHandles();

	// �e��n���h���̍폜
	static void DeleteHandles();

	// Config.json �̓ǂݍ��݁E�^�C�g����ʂ��ݒ�
	static void LoadConfig();

	// �Q�[���̃��C�����[�v����
	static void GameMain();

	// �Q�[���̏������B�{�҈ڍs�O�ɍs��
	static void GameInit();

	// �Q�[���{��
	static int GamePlay();
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	/* �E�B���h�E�ݒ� */
	SetWindowText("Novel Game");				// �E�B���h�E��
	SetMainWindowClassName(Game::GAME_CLASS);	// �E�B���h�E�N���X����o�^
	SetAlwaysRunFlag(TRUE);						// ��A�N�e�B�u�������s
	//SetWindowIconID(1);							// �A�C�R���i.ico�t�@�C����icon.rc���K�v�B������icon.rc�Őݒ肵���C�ӂ̃A�C�R��ID�j
	//SetOutApplicationLogValidFlag(FALSE);		// ���O���o�͂��Ȃ�
	ChangeWindowMode(TRUE);						// �t���X�N���[���ɂ��Ȃ�
	SetGraphMode(1280, 720, 32);				// �E�B���h�E�T�C�Y�ƐF�r�b�g���̎w��
	SetWindowSizeExtendRate(1.0);				// ���ۂɕ\������E�B���h�E�T�C�Y�ɕύX

	/* ������ */
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);				// �_�u���o�b�t�@�̎g�p

	char key[256];								// �L�[���͔z��

	Game::MakeHandles();

	Game::effect = Game::Effect();
	Game::bgm = Game::BGM();

	Game::LoadConfig();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {
		Game::SetKey(key);
		Game::GameMain();
	}

	Game::DeleteHandles();

	/* �I������ */
	DxLib_End();

	return 0;
}

namespace Game {
	static int status = 0;				// �X�e�[�^�X�ԍ�
	static int counter = 0;				// �t���[���J�E���^
	static int snum = 0;				// �V�[���Ǘ��ԍ�
	static int resEvent = 0;			// �C�x���g�Ԃ�l
	static int resEvDet = 0;			// �C�x���g�Ԃ�l�ڍ�
	static bool playFinFlag = false;	// �Q�[���{�ҏI���t���O

	static Menu menu;			// ���j���[
	static Place place;			// �ꏊ�C���X�^���X
	static Choice choice;		// �I���C���X�^���X

	void MakeHandles() {
		// �t�H���g�쐬
		font1 = CreateFontToHandle("������", 24, -1, DX_FONTTYPE_ANTIALIASING_16X16);
		font2 = CreateFontToHandle("������", 18, -1, DX_FONTTYPE_ANTIALIASING_16X16);
		font3 = CreateFontToHandle("������", 20, -1, DX_FONTTYPE_ANTIALIASING_16X16);
		font4 = CreateFontToHandle("������", 48, -1, DX_FONTTYPE_ANTIALIASING_16X16);
		font5 = CreateFontToHandle("������", 12, -1, DX_FONTTYPE_ANTIALIASING_16X16);
		font6 = CreateFontToHandle("������", 30, -1, DX_FONTTYPE_ANTIALIASING_16X16);

		// �_�C�A���O�{�b�N�X�摜�ǂݍ���
		Dialog::gh_box = LoadGraph("data/picture/[����]dialog.png");
	}

	void DeleteHandles() {
		DeleteFontToHandle(font1);
		DeleteFontToHandle(font2);
		DeleteFontToHandle(font3);
		DeleteFontToHandle(font4);
		DeleteFontToHandle(font5);
	}

	void LoadConfig() {
		ifstream ifs = ifstream("data/data/config.json");
		json js = json();
		if (ifs) {
			try {
				ifs >> js;
			}
			catch (...) {
				ErrorLog(ER_JSON_SYNTAX, "data/data/config.json");
				return;
			}
			ifs.close();
		}
		else {
			ErrorLog(ER_JSON_OPEN, "data/data/config.json");
			return;
		}
		// �Q�[���^�C�g���̐ݒ�
		if (js["game"].is_object()) {
			if (js["game"]["name"].is_string()) {
				strGameName = utf8_to_ansi(js["game"]["name"]);
				SetWindowTextA(strGameName.c_str());
			}
			if (js["game"]["version"].is_string()) {
				strGameVersion = utf8_to_ansi(js["game"]["version"]);
			}
		}
		// �V�X�e��SE�̓ǂݍ���
		if (js["se"].is_object()) {
			if (js["se"]["cursor"].is_string()) {
				sh_cursor = LoadSoundMem(utf8_to_ansi(js["se"]["cursor"]).c_str());
			}
			if (js["se"]["decide"].is_string()) {
				sh_decide = LoadSoundMem(utf8_to_ansi(js["se"]["decide"]).c_str());
			}
			if (js["se"]["cancel"].is_string()) {
				sh_cancel = LoadSoundMem(utf8_to_ansi(js["se"]["cancel"]).c_str());
			}
			if (js["se"]["success"].is_string()) {
				sh_success = LoadSoundMem(utf8_to_ansi(js["se"]["success"]).c_str());
			}
			if (js["se"]["fail"].is_string()) {
				sh_fail = LoadSoundMem(utf8_to_ansi(js["se"]["fail"]).c_str());
			}
		}

		// �^�C�g����ʂ̐ݒ�
		string strBack = "";
		string strBgm = "";
		double bgmVol = 1.0;
		bool showVer = false;
		if (js["title"].is_object()) {
			if (js["title"]["back"].is_array()) {
				if (js["title"]["back"][0].is_string()) {
					strBack = js["title"]["back"][0];
					strBack = utf8_to_ansi(strBack);
				}
			}
			if (js["title"]["bgm"].is_array()) {
				if (js["title"]["bgm"][0].is_string()) {
					strBgm = js["title"]["bgm"][0];
					strBgm = utf8_to_ansi(strBgm);
				}
				if (js["title"]["bgm"][1].is_number()) {
					bgmVol = js["title"]["bgm"][1];
				}
			}
			if (js["title"]["version"].is_boolean()) {
				showVer = js["title"]["version"];
			}
		}
		title = Title(strBack, strBgm, bgmVol, showVer);
	}

	void GameMain() {
		switch (status)
		{
		case 0:					// �^�C�g�����
		{
			int i = title.Main();
			if (i == 1) {
				GameInit();
				place.SetGeneral();
				status = 10;
			}
			else if (i >= 10 && i <= 12) {
				i -= 10;
				GameInit();
				index_place = saveData[i].index_place;
				for (int k = 0; k < FLAG_MAX; ++k) {
					flag[k] = saveData[i].flag[k];
				}
				place.SetGeneral();
				status = 10;
			}
		}
		break;
		case 10:				// �Q�[���{��
			if (GamePlay() == 1) {
				counter = -1;
				status = 0;
				title.Init();
			}
			break;
		}

		bgm.Main();

		counter++;
	}

	void GameInit() {
		snum = 0;
		for (int i = 0; i < FLAG_MAX; ++i) {
			flag[i] = false;
		}
		place = Place();
		choice = Choice();
		menu = Menu();
		index_place = 0;

		onMenu = false;
		onEvent = false;
	}

	int GamePlay() {
		// ���C���̏���
		place.Main(resEvent, resEvDet);

		// �Q�[���I��
		if (flag[1]) {
			snum = 0;
			playFinFlag = true;
		}

		// ���j���[
		switch (menu.Main())
		{
		case 1:
			playFinFlag = true;
			bgm.SetEffect(BGM_effct::FADE_OUT, 20);
		}

		// �I���t���O�������Ă���Ƃ��A���Еt���I
		if (playFinFlag) {
			playFinFlag = false;
			return 1;
		}

		return 0;
	}
}