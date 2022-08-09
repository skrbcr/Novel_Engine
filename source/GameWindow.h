#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include "DxLib.h"
#include "nlohmann/json.hpp"

using std::string;
using std::vector;
using std::runtime_error;
using std::ifstream;
using nlohmann::json;

namespace Game {
	constexpr char SOFT_NAME[] = "skrb_novel";
	constexpr char SOFT_VER[] = "version 0.2.0";

	constexpr int WIDTH = 1280;		// ウィンドウ幅
	constexpr int HEIGHT = 720;		// ウィンドウ高さ
	constexpr int MAX_SAVE = 3;		// セーブファイル最大
	constexpr int FLAG_MAX = 64;	// フラグの最大値・いずれ使用停止

	constexpr char STR_BGM_DIRECTORY[] = "data/bgm/";
	constexpr char STR_BGS_DIRECTORY[] = "data/bgs/";
	constexpr char STR_ME_DIRECTORY[] = "data/me/";
	constexpr char STR_SE_DIRECTORY[] = "data/se/";
	constexpr char STR_JSON_DIRECTORY[] = "data/data/";

	struct Font {
		int fh = 0;
		int height = 0;
		int lspace = 0;
	};

	struct SaveData {
		time_t saveTime = 0;				// セーブ日時
		int saveCount = 0;					// セーブ回数
		int index_place = 0;				// Placeのindex
		bool flag[FLAG_MAX] = { false };	// フラグ配列
	};

	class GameWindow {
	private:
		bool singleOk = false;			// OKキー単押し
		bool singleCancel = false;		// キャンセルキー単押し
		bool singleUp = false;			// 上キー単押し
		bool singleDown = false;		// 下キー単押し
		bool singleRight = false;		// 右キー単押し
		bool singleLeft = false;		// 左キー単押し
		bool autoSkip = false;			// スキップキー自動
		bool okPress = false;			// キー入力（OK）
		bool cancelPress = false;		// キー入力（キャンセル)
		bool singleOkFlag = false;		// 決定単押しフラグ
		bool singleCancelFlag = false;	// キャンセル単押しフラグ）
		bool upPress = false;			// 上キー入力
		bool downPress = false;			// 下キー入力
		bool rightPress;				// 右クリック
		bool leftPress;					// 左クリック
		bool singleUpFlag = false;		// 上キー単押しフラグ
		bool singleDownFlag = false;	// 下キー単押しフラグ
		bool singleRightFlag;			// 右キー単押しフラグ
		bool singleLeftFlag;			// 左キー単押しフラグ
		bool skipPress = false;			// キー入力(スキップ)
		int autoSkipCount = 0;			// スキップオートカウンタ

	public:
		string strGameName = "";
		string strGameVersion = "";

		json js_cfg = json();		// Config.json
		json js_saveFile[3] = {};	// セーブデータファイルたち
		SaveData saveData[3] = {};	// セーブデータ中身たち

		vector<Font> vfont = vector<Font>();

		// ここのフォントは後で消したい（最初からフォントを個別に取っておくのは良くないので）
		int font1;		// 24pxフォント
		int font2;		// 18pxフォント
		int font3;		// 20pxフォント
		int font4;		// 48pxフォント
		int font5;		// 12pxフォント
		int font6;		// 30pxフォント

	public:
		GameWindow();
		~GameWindow();
		/// <summary>
		/// 単押しキー取得
		/// </summary>
		/// <param name="key">キー配列</param>
		void SetKey(const char* key);

		// OKキー単押し取得
		bool GetSingleOk();

		// Cancelキー単押し取得
		bool GetSingleCancel();

		// 上キー単押し取得
		bool GetSingleUp();

		// 下キー単押し取得
		bool GetSingleDown();

		// 右キー単押し取得
		bool GetSingleRight();

		// 左キー単押し取得
		bool GetSingleLeft();

		// スキップキー取得
		bool GetAutoSkip();

	private:
		void LoadConfig();
		void MakeHandles();			// 各種ハンドルの作成
		void DeleteHandles();		// 各種ハンドルの削除
	};
}
