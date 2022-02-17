#include "Title.h"
#include "Image.h"

namespace Game {
	void Title::ApplyConfig(json& js) {
		string strtmp = "";
		if (js["back"].is_array()) {
			if (js["back"][0].is_string()) {
				strtmp = js["back"][0];
				gh_back = LoadGraph(strtmp.data());
				if (gh_back == -1) {
					ErrorLog(ER_IMG_LOAD, strtmp);
				}
			}
		}
		if (js["bgm"].is_array()) {
			if (js["bgm"][0].is_string()) {
				strtmp = js["bgm"][0];
				sh_bgm = LoadSoundMem(strtmp.data());
				if (sh_bgm == -1) {
					ErrorLog(ER_SND_LOAD, strtmp);
				}
			}
			if (js["bgm"][1].is_number()) {
				this->bgmVol = js["bgm"][1];
			}
		}
		if (js["version"].is_boolean()) {
			showVerFlag = js["version"];
		}

		width_hajime = GetDrawStringWidthToHandle((const char*)u8"はじめから", static_cast<int>(strlen((const char*)u8"はじめから")), font6);
		width_tuduki = GetDrawStringWidthToHandle((const char*)u8"つづきから", static_cast<int>(strlen((const char*)u8"つづきから")), font6);

		button_title = Button(2);
		button_title.SetGroup(1, 0);
		button_title.SetButton(0, (WIDTH - width_hajime) / 2, 518, width_hajime, 50);
		button_title.SetButton(1, (WIDTH - width_tuduki) / 2, 595, width_tuduki, 50);

		button_load = Button(4);
		button_load.SetGroup(1, 0, 0xCCCCFF);
		button_load.SetButton(0, 160, 230, 960, 85);
		button_load.SetButton(1, 160, 330, 960, 85);
		button_load.SetButton(2, 160, 430, 960, 85);
		button_load.SetButton(3, 905, 570, GetDrawStringWidthToHandle((const char*)u8"タイトルに戻る", static_cast<int>(strlen((const char*)u8"タイトルに戻る")), font3) + 10, 40);
	}

	int Title::Main() {
		int res = 0;

		switch (nPage)
		{
		case 0:		// 起動時など
			// 背景
			DrawGraph(0, 0, gh_back, FALSE);
			if (fcounter == 0) {

				// セーブデータ読み込み
				std::ifstream ifs;
				for (int i = 0; i < MAX_SAVE; ++i) {
					ifs = std::ifstream("save/save" + std::to_string(i + 1) + ".json");
					if (ifs) {
						try {
							ifs >> js_saveFile[i];
						}
						catch (...) {
							// エラー時の処理
							
						}
						ifs.close();

						// セーブデータの読み込み処理
						saveData[i] = SaveData();
						if (js_saveFile[i]["header"]["soft"]["name"].is_string()) {
							if (js_saveFile[i]["header"]["soft"]["name"] == SOFT_NAME) {
								if (js_saveFile[i]["save"].is_object()) {
									if (js_saveFile[i]["save"]["time"].is_number_integer()) {
										saveData[i].saveTime = static_cast<time_t>(js_saveFile[i]["save"]["time"]);
									}
									if (js_saveFile[i]["save"]["count"].is_number_integer()) {
										saveData[i].saveCount = js_saveFile[i]["save"]["count"];
									}
									if (js_saveFile[i]["save"]["data"]["index_place"].is_number_integer()) {
										saveData[i].index_place = js_saveFile[i]["save"]["data"]["index_place"];
									}
									if (js_saveFile[i]["save"]["data"]["flag"].is_array()) {
										if (js_saveFile[i]["save"]["data"]["flag"].size() == FLAG_MAX) {
											for (int j = 0; j < FLAG_MAX; ++j) {
												if (js_saveFile[i]["save"]["data"]["flag"][j].is_boolean()) {
													saveData[i].flag[j] = js_saveFile[i]["save"]["data"]["flag"][j];
												}
											}
										}
									}
								}
								opt_title = 1;
								button_title.SetSelection(1);
							}
						}
					}
				}
			}
			if (fcounter <= 30) {
				// 画面演出
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 - 255 * fcounter / 30.0));
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				// 演出終了・BGM再生開始
				if (fcounter == 30) {
					// BGM開始
					bgm.Play(sh_bgm, DX_PLAYTYPE_LOOP, bgmVol, TRUE);
					nPage = 1;
					fcounter = -1;
				}
			}
			break;
		case 1:		// タイトル画面
			// 描画
			DrawGraph(0, 0, gh_back, FALSE);

			// はじめから・つづきから
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawBox((WIDTH - 250) / 2, 500, (WIDTH + 250) / 2, 660, 0x999999, TRUE);
			DrawBoxAA((WIDTH - 250) / 2, 500, (WIDTH + 250) / 2, 660, 0xAAAAAA, FALSE, 2.f);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			button_title.Main(false);
			DrawStringToHandle((WIDTH - width_hajime) / 2, 528, (const char*)u8"はじめから", 0x000000, font6);
			DrawStringToHandle((WIDTH - width_tuduki) / 2, 605, (const char*)u8"つづきから", 0x000000, font6);

			// バージョン情報
			if (showVerFlag) {
				DrawStringToHandle(WIDTH - 20 - GetDrawStringWidthToHandle(strGameVersion.c_str(), static_cast<int>(strGameVersion.size()), font2),
					HEIGHT - 30, strGameVersion.c_str(), 0x000000, font2);
			}

			// キー操作
			if (GetSingleUp() || GetSingleDown()) {
				PlaySoundMem(sh_cursor, DX_PLAYTYPE_BACK);
				if (opt_title == 0) {
					opt_title = 1;
				}
				else {
					opt_title = 0;
				}
			}
			if (GetSingleOk()) {
				PlaySoundMem(sh_decide, DX_PLAYTYPE_BACK);
				if (opt_title == 0) {		// 開始処理開始
					nPage = 3;
					fcounter = -1;
					bgm.SetEffect(BGM_effct::FADE_OUT, 120);
				}
				else {
					nPage = 2;
					fcounter = -1;
				}
			}
			break;
		case 2:		// ロード選択
			// 背景
			DrawGraph(0, 0, gh_back, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(0, 0, WIDTH, HEIGHT, 0xFFFFFF, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// ボタン処理
			opt_load = button_load.Main(false);
			switch (opt_load)
			{
			case 0:
			case 1:
			case 2:
				if (saveData[opt_load].saveCount != 0) {
					PlaySoundMem(sh_decide, DX_PLAYTYPE_BACK);
					nPage = 4;
					fcounter = -1;
					bgm.SetEffect(BGM_effct::FADE_OUT, 120);
				}
				else {
					PlaySoundMem(sh_fail, DX_PLAYTYPE_BACK);
				}
				break;
			case 3:
			case -2:
				PlaySoundMem(sh_cancel, DX_PLAYTYPE_BACK);
				nPage = 1;
				fcounter = -1;
				break;
			}

			// 文字描画
			DrawStringToHandle(430, 160, (const char*)u8"～ロードするファイルを選択～", 0x000000, font3);
			DrawStringToHandle(160, 240, (const char*)u8"・セーブ１", 0x000000, font3);
			DrawStringToHandle(160, 340, (const char*)u8"・セーブ２", 0x000000, font3);
			DrawStringToHandle(160, 440, (const char*)u8"・セーブ３", 0x000000, font3);
			DrawLine(160, 550, 1120, 550, 0x000000);
			DrawStringToHandle(910, 580, (const char*)u8"タイトルに戻る", 0x000000, font3);

			for (int i = 0; i < 3; ++i) {
				if (saveData[i].saveCount != 0) {
					struct tm local;
					localtime_s(&local, &saveData[i].saveTime);
					int year = static_cast<long long>(local.tm_year) + 1900;
					int month = local.tm_mon + 1;
					int day = local.tm_mday;
					int hour = local.tm_hour;
					int min = local.tm_min;
					string strMin = "";
					if (min < 10) {
						strMin = "0";
						strMin += std::to_string(min);
					}
					else {
						strMin = std::to_string(min);
					}
					DrawFormatStringToHandle(160, 280 + 100 * i, 0x000000, font3, (const char*)u8"　最終セーブ：%d年%d月%d日　%d時%s分　セーブ回数：%d回", year, month, day, hour, strMin.c_str(), saveData[i].saveCount);
				}
			}
			break;
		case 3:		// タイトル→ゲーム
			// 描画
			DrawGraph(0, 0, gh_back, FALSE);

			// はじめから・つづきから
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawBox((WIDTH - 250) / 2, 500, (WIDTH + 250) / 2, 660, 0x999999, TRUE);
			DrawBoxAA((WIDTH - 250) / 2, 500, (WIDTH + 250) / 2, 660, 0xAAAAAA, FALSE, 2.f);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			button_title.Main(true);
			DrawStringToHandle((WIDTH - width_hajime) / 2, 528, (const char*)u8"はじめから", 0x000000, font6);
			DrawStringToHandle((WIDTH - width_tuduki) / 2, 605, (const char*)u8"つづきから", 0x000000, font6);

			// バージョン情報
			if (showVerFlag) {
				DrawStringToHandle(WIDTH - 20 - GetDrawStringWidthToHandle(strGameVersion.c_str(), static_cast<int>(strGameVersion.size()), font2),
					HEIGHT - 30, strGameVersion.c_str(), 0x000000, font2);
			}

			// 演出
			if (fcounter < 90) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * fcounter / 90.0));
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				fcounter++;
			}
			else if (fcounter < 150) {
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
			}
			else {
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
				res = 1;
			}
			break;
		case 4:		// ロード→ゲーム
			// 背景
			DrawGraph(0, 0, gh_back, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(0, 0, WIDTH, HEIGHT, 0xFFFFFF, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// ボタン
			button_load.Main(true);

			// 文字描画
			DrawStringToHandle(430, 160, (const char*)u8"～ロードするファイルを選択～", 0x000000, font3);
			DrawStringToHandle(160, 240, (const char*)u8"・セーブ１", 0x000000, font3);
			DrawStringToHandle(160, 340, (const char*)u8"・セーブ２", 0x000000, font3);
			DrawStringToHandle(160, 440, (const char*)u8"・セーブ３", 0x000000, font3);
			DrawLine(160, 550, 1120, 550, 0x000000);
			DrawStringToHandle(910, 580, (const char*)u8"タイトルに戻る", 0x000000, font3);
			for (int i = 0; i < 3; ++i) {
				if (saveData[i].saveCount != 0) {
					struct tm local;
					localtime_s(&local, &saveData[i].saveTime);
					int year = static_cast<long long>(local.tm_year) + 1900;
					int month = local.tm_mon + 1;
					int day = local.tm_mday;
					int hour = local.tm_hour;
					int min = local.tm_min;
					string strMin = "";
					if (min < 10) {
						strMin = "0";
						strMin += std::to_string(min);
					}
					else {
						strMin = std::to_string(min);
					}
					DrawFormatStringToHandle(160, 280 + 100 * i, 0x000000, font3, (const char*)u8"　最終セーブ：%d年%d月%d日　%d時%s分　セーブ回数：%d回", year, month, day, hour, strMin.c_str(), saveData[i].saveCount);
				}
			}

			// 演出
			if (fcounter < 90) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * fcounter / 90.0));
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else if (fcounter < 150) {
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
			}
			else {
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
				res = 10 + opt_load;
			}
			break;
		default:
			break;
		}

		fcounter++;

		return res;
	}
}