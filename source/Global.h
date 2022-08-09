#pragma once
#include <stdexcept>
#include <vector>
#include <string>
#include <string_view>
#include <fstream>
#include "nlohmann/json.hpp"
#include "DxLib.h"
#include "GameWindow.h"
#include "Effect.h"
#include "BGM.h"
#include "SE.h"

using std::vector;
using std::string;
using std::string_view;
using std::ofstream;
using std::ifstream;
using std::endl;
using nlohmann::json;
using color_t = unsigned int;		// 色

namespace Game {
	constexpr int ER_JSON_OPEN = 10;
	constexpr int ER_JSON_SYNTAX = 11;
	constexpr int ER_JSON_RULE = 12;
	constexpr int ER_PLC_SET = 13;
	constexpr int ER_IMG_LOAD = 21;
	constexpr int ER_SND_LOAD = 31;

	extern class GameWindow gw;

	extern class Effect effect;
	extern class BGM bgm;
	extern class SE se;

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

	// エラーログの出力
	void ErrorLog(int ER_TYPE, string_view state1 = "", string_view state2 = "");
}