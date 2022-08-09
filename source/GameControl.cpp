#include "GameControl.h"

namespace Game {
    GameControl::GameControl() {
        title = Title();
        menu = Menu();
        place = Place();
		//LoadConfig();
		try {
			SetConfig();
		}
		catch (const std::exception& e) {
			string str = "Error: Failed to apply config. ";
			throw runtime_error(str + e.what());
		}
    }
	void GameControl::GameMain() {
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
				index_place = gw.saveData[i].index_place;
				for (int k = 0; k < FLAG_MAX; ++k) {
					flag[k] = gw.saveData[i].flag[k];
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
	int GameControl::GamePlay() {
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
	void GameControl::GameInit() {
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
	void GameControl::SetConfig() {
		// システムSEの読み込み
		if (gw.js_cfg["se"].is_object()) {
			se.ApplayConfig(gw.js_cfg["se"]);
		}
		// ダイアログ
		if (gw.js_cfg["dialog"].is_object()) {
			Dialog::ApplyConfig(gw.js_cfg["dialog"]);
		}
		// 選択肢
		if (gw.js_cfg["choice"].is_object()) {
			Choice::ApplyConfig(gw.js_cfg["choice"]);
		}
		// キャラクター画像
		if (gw.js_cfg["chara"].is_object()) {
			if (gw.js_cfg["chara"]["img"].is_array()) {
				size_t n = gw.js_cfg["chara"]["img"].size();
				place.InitChara(n);
				for (size_t i = 0; i < n; ++i) {
					if (gw.js_cfg["chara"]["img"][i].is_array() && gw.js_cfg["chara"]["img"][i][0].is_string()
						&& gw.js_cfg["chara"]["img"][i][1].is_number() && gw.js_cfg["chara"]["img"][i][2].is_number()) {
						place.SetChara(i, gw.js_cfg["chara"]["img"][i][0],
							gw.js_cfg["chara"]["img"][i][1], gw.js_cfg["chara"]["img"][i][2]);
					}
				}
			}
		}
		// タイトル画面の設定
		if (gw.js_cfg["title"].is_object()) {
			title.ApplyConfig(gw.js_cfg["title"]);
		}
		// フォントの読み込み
		if (gw.js_cfg["font"]["data"].is_array()) {
			string strFontFile = "";
			char lpszFontFile[64] = { '\000' };
			for (const auto& str : gw.js_cfg["font"]["data"]) {
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
		if (gw.js_cfg["font"]["font"].is_array()) {
			for (auto& jsf : gw.js_cfg["font"]["font"]) {
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
					gw.vfont.push_back(f);
				}
				else {
					ErrorLog(ER_JSON_RULE, "Config.json", (const char*)u8"作成するフォントの指定に誤りがあります。");
				}
			}
		}
		if (gw.vfont.size() == 0) {
			ErrorLog(ER_JSON_RULE, "Config.json", (const char*)u8"少なくとも 1つは正常なフォントを作成してください。");
			throw runtime_error("Error: No normal fonts were made. Plese make more than 1 fonts.");
		}
		if (gw.vfont.size() > 10) {
			ErrorLog(ER_JSON_RULE, "Config.json", (const char*)u8"10個を超えるフォントが作成されましたが、11個目以降は利用できません。");
		}
	}
}