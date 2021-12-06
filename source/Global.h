#pragma once
#include <string>
#include <string_view>
#include <fstream>
#include "nlohmann/json.hpp"
#include "DxLib.h"
#include "Effect.h"
#include "BGM.h"

using std::string;
using std::string_view;
using std::ofstream;
using std::endl;
using nlohmann::json;
//using color_t = unsigned int;		// 色

namespace Game {
	constexpr char GAME_CLASS[] = "skrb_novel";

	extern string strGameName;
	extern string strGameVersion;

	constexpr int WIDTH = 1280;		// ウィンドウ幅
	constexpr int HEIGHT = 720;		// ウィンドウ高さ
	constexpr int MAX_SAVE = 3;		// セーブファイル最大
	constexpr int FLAG_MAX = 64;	// フラグの最大値・いずれ使用停止

	constexpr char STR_BGM_DIRECTORY[] = "data/bgm/";
	constexpr char STR_BGS_DIRECTORY[] = "data/bgs/";
	constexpr char STR_ME_DIRECTORY[] = "data/me/";
	constexpr char STR_SE_DIRECTORY[] = "data/se/";
	constexpr char STR_JSON_DIRECTORY[] = "data/data/";	

	constexpr int ER_JSON_OPEN = 10;
	constexpr int ER_JSON_SYNTAX = 11;
	constexpr int ER_JSON_RULE = 12;
	constexpr int ER_PLC_SET = 13;
	constexpr int ER_IMG_LOAD = 21;
	constexpr int ER_SND_LOAD = 31;

	extern int sh_cursor;			// カーソルSE(矢印キー・目立たせないOKキー)
	extern int sh_decide;			// 決定SE
	extern int sh_cancel;			// キャンセルSE
	extern int sh_success;			// 成功SE(セーブ時)
	extern int sh_fail;				// 失敗SE(セーブ時)

	extern class Effect effect;
	extern class BGM bgm;

	struct SaveData
	{
		//const char* strheader = GAME_CLASS;		// ヘッダー文字列
		//const char* strgm = strGameName.c_str();			// ゲーム名
		//const char* strver = strGameVersion.c_str();		// ヴァージョン
		time_t saveTime = 0;				// セーブ日時
		int saveCount = 0;					// セーブ回数
		int index_place = 0;				// Placeのindex
		bool flag[FLAG_MAX] = { false };	// フラグ配列
	};

	__declspec(selectany) struct SaveData saveData[3] = {};
	__declspec(selectany) json js_saveFile[3] = {};

	extern int font1;		// 24pxフォント
	extern int font2;		// 18pxフォント
	extern int font3;		// 20pxフォント
	extern int font4;		// 48pxフォント
	extern int font5;		// 12pxフォント
	extern int font6;		// 30pxフォント

	extern bool onMenu;		// メニューオープン中フラグ
	extern bool onMenuAllow;// メニューオープン許可フラグ
	extern bool onEvent;	// イベント中フラグ

	__declspec(selectany) bool flag[FLAG_MAX] = { false };		// フラグ配列(ゲーム本編用)
	extern int index_place;	// Placeのindex

	/// <summary>
	/// 描画効果列挙型
	/// </summary>
	enum class drawEffect
	{
		NO_EFFECT,		// 効果なし（通常）
		FADE_OUT,		// フェードアウト
		FADE_IN,		// フェードイン
		FLASH,			// 点滅
		MOVE_UP,		// 背景画像の上へ移動
		MOVE_DOWN,		// 背景画像の下へ移動
		MOVE_RIGHT,		// 背景画像の右へ移動
		MOVE_LEFT,		// 背景画像の左へ移動
		WAIT,			// 待ち時間
	};

	// システムSE読み込み
	//void SetSound();

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

	// エラーログの出力
	void ErrorLog(int ER_TYPE, string_view state1 = "", string_view state2 = "");
}