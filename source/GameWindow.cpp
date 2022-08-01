#include "GameWindow.h"

namespace Game {
	GameWindow::GameWindow() {
		/* �E�B���h�E�ݒ� */
		SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);	// DxLib�֐��̕���������Ɏg�p���镶���R�[�h�̐ݒ�
		LoadConfig();
		SetMainWindowText(Game::strGameName.c_str());	// �^�C�g���e�L�X�g�̐ݒ�
		SetMainWindowClassName(Game::SOFT_NAME);		// �E�B���h�E�N���X����o�^
		SetAlwaysRunFlag(TRUE);							// ��A�N�e�B�u�������s
		//SetWindowIconID(1);							// �A�C�R���i.ico�t�@�C����icon.rc���K�v�B������icon.rc�Őݒ肵���C�ӂ̃A�C�R��ID�j
		//SetOutApplicationLogValidFlag(FALSE);			// ���O���o�͂��Ȃ�
		ChangeWindowMode(TRUE);							// �t���X�N���[���ɂ��Ȃ�
		SetGraphMode(1280, 720, 32);					// �E�B���h�E�T�C�Y�ƐF�r�b�g���̎w��
		SetWindowSizeExtendRate(1.0);					// ���ۂɕ\������E�B���h�E�T�C�Y�ɕύX

		if (DxLib_Init() == -1) {
			throw runtime_error("Error: Failed to initialize DxLib. ");
		}
		SetDrawScreen(DX_SCREEN_BACK);				// �_�u���o�b�t�@�̎g�p

		MakeHandles();
		try {
			SetConfig();
		}
		catch (const std::exception& e) {
			DeleteHandles();
			DxLib_End();
			string str = "Error: Failed to apply config. ";
			throw runtime_error(str + e.what());
		}
	}
	GameWindow::~GameWindow() {
		DeleteHandles();
		DxLib_End();
	}
	void GameWindow::Main() {
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {
			SetKey(key);
			GameMain();
		}
	}
	void GameWindow::GameInit() {
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
	void GameWindow::MakeHandles() {
		SetFontCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
		font1 = CreateFontToHandle((const char*)u8"������", 24, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font2 = CreateFontToHandle((const char*)u8"������", 18, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font3 = CreateFontToHandle((const char*)u8"������", 20, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font4 = CreateFontToHandle((const char*)u8"������", 48, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font5 = CreateFontToHandle((const char*)u8"������", 12, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font6 = CreateFontToHandle((const char*)u8"������", 30, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
	}
	void GameWindow::DeleteHandles() {
		DeleteFontToHandle(font1);
		DeleteFontToHandle(font2);
		DeleteFontToHandle(font3);
		DeleteFontToHandle(font4);
		DeleteFontToHandle(font5);

		for (auto& f : vfont) {
			DeleteFontToHandle(f.fh);
		}
	}
	void GameWindow::LoadConfig() {
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
	void GameWindow::SetConfig() {
		// �V�X�e��SE�̓ǂݍ���
		if (js_cfg["se"].is_object()) {
			se.ApplayConfig(js_cfg["se"]);
		}
		// �_�C�A���O
		if (js_cfg["dialog"].is_object()) {
			Dialog::ApplyConfig(js_cfg["dialog"]);
		}
		// �I����
		if (js_cfg["choice"].is_object()) {
			Choice::ApplyConfig(js_cfg["choice"]);
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
		// �t�H���g�̓ǂݍ���
		if (js_cfg["font"]["data"].is_array()) {
			string strFontFile = "";
			char lpszFontFile[64] = { '\000' };
			for (const auto& str : js_cfg["font"]["data"]) {
				if (str.is_string()) {
					strFontFile = str;
					ConvertStringCharCodeFormat(DX_CHARCODEFORMAT_UTF8, strFontFile.c_str(), DX_CHARCODEFORMAT_SHIFTJIS, lpszFontFile);
					AddFontResourceEx(lpszFontFile, FR_PRIVATE, NULL);
				}
				else {
					ErrorLog(ER_JSON_RULE, "Config.json", (const char*)u8"�t�H���g�f�[�^�t�@�C���̎w��Ɍ�肪����܂��B");
				}
			}
		}
		if (js_cfg["font"]["font"].is_array()) {
			for (auto& jsf : js_cfg["font"]["font"]) {
				Font f = Font();
				string str = string();
				if (jsf["name"].is_string() && jsf["size"].is_number_integer()) {
					str = jsf["name"];
					f.fh = CreateFontToHandle(str.c_str(), jsf["size"], -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
					f.height = jsf["size"];
					if (jsf["lspace"].is_number_integer()) {
						f.lspace = jsf["lspace"];
					}
					else {
						f.lspace = f.height * 2;
					}
					vfont.push_back(f);
				}
				else {
					ErrorLog(ER_JSON_RULE, "Config.json", (const char*)u8"�쐬����t�H���g�̎w��Ɍ�肪����܂��B");
				}
			}
		}
		if (vfont.size() == 0) {
			ErrorLog(ER_JSON_RULE, "Config.json", (const char*)u8"���Ȃ��Ƃ� 1�͐���ȃt�H���g���쐬���Ă��������B");
			throw runtime_error("Error: No normal fonts were made. Plese make more than 1 fonts.");
		}
		if (vfont.size() > 10) {
			ErrorLog(ER_JSON_RULE, "Config.json", (const char*)u8"10�𒴂���t�H���g���쐬����܂������A11�ڈȍ~�͗��p�ł��܂���B");
		}
	}
	void GameWindow::GameMain() {
		switch (status) {
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
	int GameWindow::GamePlay() {
		// ���C���̏���
		place.Main(resEvent, resEvDet);

		// �Q�[���I��
		if (flag[1]) {
			snum = 0;
			playFinFlag = true;
		}

		// ���j���[
		switch (menu.Main()) {
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
