#include "GameWindow.h"

namespace Game {
	GameWindow::GameWindow() {
		/* ウィンドウ設定 */
		SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);	// DxLib関数の文字列引数に使用する文字コードの設定
		LoadConfig();
		SetMainWindowText(Game::strGameName.c_str());	// タイトルテキストの設定
		SetMainWindowClassName(Game::SOFT_NAME);		// ウィンドウクラス名を登録
		SetAlwaysRunFlag(TRUE);							// 非アクティブ時も実行
		//SetWindowIconID(1);							// アイコン（.icoファイルとicon.rcが必要。引数はicon.rcで設定した任意のアイコンID）
		//SetOutApplicationLogValidFlag(FALSE);			// ログを出力しない
		ChangeWindowMode(TRUE);							// フルスクリーンにしない
		SetGraphMode(1280, 720, 32);					// ウィンドウサイズと色ビット数の指定
		SetWindowSizeExtendRate(1.0);					// 実際に表示するウィンドウサイズに変更

		if (DxLib_Init() == -1) {
			throw runtime_error("Error: Failed to initialize DxLib. ");
		}
		SetDrawScreen(DX_SCREEN_BACK);				// ダブルバッファの使用

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
		font1 = CreateFontToHandle((const char*)u8"游明朝", 24, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font2 = CreateFontToHandle((const char*)u8"游明朝", 18, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font3 = CreateFontToHandle((const char*)u8"游明朝", 20, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font4 = CreateFontToHandle((const char*)u8"游明朝", 48, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font5 = CreateFontToHandle((const char*)u8"游明朝", 12, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font6 = CreateFontToHandle((const char*)u8"游明朝", 30, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
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

		// ゲームタイトルの設定
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
		// システムSEの読み込み
		if (js_cfg["se"].is_object()) {
			se.ApplayConfig(js_cfg["se"]);
		}
		// ダイアログ
		if (js_cfg["dialog"].is_object()) {
			Dialog::ApplyConfig(js_cfg["dialog"]);
		}
		// 選択肢
		if (js_cfg["choice"].is_object()) {
			Choice::ApplyConfig(js_cfg["choice"]);
		}
		// キャラクター画像
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
		// タイトル画面の設定
		if (js_cfg["title"].is_object()) {
			title.ApplyConfig(js_cfg["title"]);
		}
		// フォントの読み込み
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
					ErrorLog(ER_JSON_RULE, "Config.json", (const char*)u8"フォントデータファイルの指定に誤りがあります。");
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
					ErrorLog(ER_JSON_RULE, "Config.json", (const char*)u8"作成するフォントの指定に誤りがあります。");
				}
			}
		}
		if (vfont.size() == 0) {
			ErrorLog(ER_JSON_RULE, "Config.json", (const char*)u8"少なくとも 1つは正常なフォントを作成してください。");
			throw runtime_error("Error: No normal fonts were made. Plese make more than 1 fonts.");
		}
		if (vfont.size() > 10) {
			ErrorLog(ER_JSON_RULE, "Config.json", (const char*)u8"10個を超えるフォントが作成されましたが、11個目以降は利用できません。");
		}
	}
	void GameWindow::GameMain() {
		switch (status) {
		case 0:					// タイトル画面
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
		case 10:				// ゲーム本編
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
		// メインの処理
		place.Main(resEvent, resEvDet);

		// ゲーム終了
		if (flag[1]) {
			snum = 0;
			playFinFlag = true;
		}

		// メニュー
		switch (menu.Main()) {
		case 1:
			playFinFlag = true;
			bgm.SetEffect(BGM_effct::FADE_OUT, 20);
		}

		// 終了フラグが立っているとき、お片付け！
		if (playFinFlag) {
			playFinFlag = false;
			return 1;
		}

		return 0;
	}
}
