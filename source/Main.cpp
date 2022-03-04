// skrbcr/Novel_Engine�ihttps://github.com/skrbcr/Novel_Engine�j
// DX���C�u�����g�p�̃m�x���Q�[���G���W���H�̃A���t�@�� ver.0.2.0�i�\��j
// 
// �z�z�\�[�X�R�[�h�̈ꕔ�ɁA�ȉ��̃��C�u�������܂݂܂�
// ���쌠�\���̏ڍׂ́A"./nlohmann/json.hpp" �� "../README.md" ��������������
// �Enlohmann/json�i https://github.com/nlohmann/json �jversion 3.9.1
// 
// �܂��A�{�\�t�g�� DX���C�u�����iVer3.23 https://dxlib.xsrv.jp/ �j���g�p���Ă��܂���
// �z�z�\�[�X�R�[�h�ɂ͊܂�ł���܂���
// �ł�����A�r���h�������́A�����g�ł̃_�E�����[�h��ݒ蓙�����肢�������܂�
// 

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "DxLib.h"
#include "nlohmann/json.hpp"
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

	// Config.json�̓ǂݍ��݁E�E�B���h�E�̐ݒ�
	static void LoadConfig();

	// Config.json �̓K�p
	static void SetConfig();

	// �Q�[���̃��C�����[�v����
	static void GameMain();

	// �Q�[���̏������B�{�҈ڍs�O�ɍs��
	static void GameInit();

	// �Q�[���{��
	static int GamePlay();
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	/* �f�o�b�O�p�i���������[�N���m�j */
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//int* a = new int();		// ���������[�N�̃T���v���idelete���Ă΂Ȃ��j

	/* �E�B���h�E�ݒ� */
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);	// DxLib�֐��̕���������Ɏg�p���镶���R�[�h�̐ݒ�
	Game::LoadConfig();
	SetMainWindowText(Game::strGameName.c_str());	// �^�C�g���e�L�X�g�̐ݒ�
	SetMainWindowClassName(Game::SOFT_NAME);		// �E�B���h�E�N���X����o�^
	SetAlwaysRunFlag(TRUE);							// ��A�N�e�B�u�������s
	//SetWindowIconID(1);							// �A�C�R���i.ico�t�@�C����icon.rc���K�v�B������icon.rc�Őݒ肵���C�ӂ̃A�C�R��ID�j
	//SetOutApplicationLogValidFlag(FALSE);			// ���O���o�͂��Ȃ�
	ChangeWindowMode(TRUE);							// �t���X�N���[���ɂ��Ȃ�
	SetGraphMode(1280, 720, 32);					// �E�B���h�E�T�C�Y�ƐF�r�b�g���̎w��
	SetWindowSizeExtendRate(1.0);					// ���ۂɕ\������E�B���h�E�T�C�Y�ɕύX

	/* ������ */
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);				// �_�u���o�b�t�@�̎g�p

	char key[256];								// �L�[���͔z��

	Game::MakeHandles();
	Game::SetConfig();

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

	static json js_cfg = json();		// Config.json

	void MakeHandles() {
		// �t�H���g�쐬
		SetFontCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
		font1 = CreateFontToHandle((const char*)u8"������", 24, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font2 = CreateFontToHandle((const char*)u8"������", 18, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font3 = CreateFontToHandle((const char*)u8"������", 20, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font4 = CreateFontToHandle((const char*)u8"������", 48, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font5 = CreateFontToHandle((const char*)u8"������", 12, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font6 = CreateFontToHandle((const char*)u8"������", 30, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
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
		if (ifs) {
			try {
				ifs >> js_cfg;
			}
			catch (...) {
				ErrorLog(ER_JSON_SYNTAX, "data/data/config.json");
				return;
			}
		}
		else {
			ErrorLog(ER_JSON_OPEN, "data/data/config.json");
			return;
		}

		// �Q�[���^�C�g���̐ݒ�
		if (js_cfg["game"].is_object()) {
			if (js_cfg["game"]["title"].is_string()) {
				strGameName = js_cfg["game"]["title"];
			}
			if (js_cfg["game"]["version"].is_string()) {
				strGameVersion = js_cfg["game"]["version"];
			}
		}
	}

	void SetConfig() {
		// �V�X�e��SE�̓ǂݍ���
		if (js_cfg["se"].is_object()) {
			se.ApplayConfig(js_cfg["se"]);
		}
		// �_�C�A���O
		if (js_cfg["dialog"].is_object()) {
			Dialog::ApplyConfig(js_cfg["dialog"]);
		}
		// �L�����N�^�[�摜
		if (js_cfg["chara"].is_object()) {
			if (js_cfg["chara"]["img"].is_array()) {
				size_t n = js_cfg["chara"]["img"].size();
				place.InitChara(n);
				for (size_t i = 0; i < n; ++i) {
					if (js_cfg["chara"]["img"][i].is_array() && js_cfg["chara"]["img"][i][0].is_string()
						&& js_cfg["chara"]["img"][i][1].is_number() && js_cfg["chara"]["img"][i][2].is_number()) {
						place.SetChara(i, js_cfg["chara"]["img"][i][0],
							js_cfg["chara"]["img"][i][1], js_cfg["chara"]["img"][i][2]);
					}
				}
			}
		}
		// �^�C�g����ʂ̐ݒ�
		if (js_cfg["title"].is_object()) {
			title.ApplyConfig(js_cfg["title"]);
		}
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
		place.Init();
		//choice = Choice();
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