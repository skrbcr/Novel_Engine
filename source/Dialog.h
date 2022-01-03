#pragma once
#include <string>
#include <string_view>
#include "Global.h"
#include "Utilities.h"

using string = std::string;
using string_view = std::string_view;

namespace Game {
	// 文字色リスト(処理の都合上、10個まで登録可能)
	constexpr color_t colorList[10] =
	{ 0xFFFFFF, 0xff0000, 0xFFCCFF, 0xffff00, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000 };

	/// <summary>
	/// セリフクラス
	/// </summary>
	class Dialog
	{
	public:
		static int gh_box;			// メッセージボックスの画像
		static int msgwnd_left;		// メッセージボックスの左端
		static int msgwnd_top;		// メッセージボックスの上端
		static int msgwnd_width;	// メッセージボックスの幅
		static int msgwnd_height;	// メッセージボックスの高さ
		static int msgspk_left;		// 話者の左端（相対座標）
		static int msgspk_top;		// 話者の上端（相対座標）
		static int msgtxt_left;		// 表示テキストの左端（相対座標）
		static int msgtxt_top;		// 表示テキストの上端（相対座標）

	private:
		string strSpeaker;		// 話者文字列
		string strContent;		// 内容文字列
		size_t nLenSpeaker;		// 話者文字列サイズ
		size_t nLenContent;		// 内容文字列サイズ
		bool onDisplay;			// ダイアログボックス表示中か

		int status;				// 描画モード
		string strContDisp;		// 実際に表示する用の文字列
		size_t index_strCont;	// 表示文字語数インデックス
		size_t nWordContnet;	// 内容文字列の語数

		int fcounter;		// フレームカウンタ
		int mode;			// 表示モード

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Dialog() {
			strSpeaker = "";
			strContent = "";
			nLenSpeaker = (size_t)0;
			nLenContent = (size_t)0;
			onDisplay = true;
			status = 0;
			strContDisp = "";
			index_strCont = 0;
			nWordContnet = (size_t)0;
		}

		static void ApplyMsgWndCongig(int gh, int left, int top, int width, int height) {
			gh_box = gh;
			msgwnd_left = left;
			msgwnd_top = top;
			msgwnd_width = width;
			msgwnd_height = height;
		}

		static void ApplyMsgSpkConfig(int left, int top) {
			msgspk_left = left;
			msgspk_top = top;
		}

		static void ApplyMsgTxtConfig(int left, int top) {
			msgtxt_left = left;
			msgtxt_top = top;
		}

		/// <summary>
		/// Dialogを登録
		/// </summary>
		/// <param name="speaker">話者文字列</param>
		/// <param name="content">内容文字列</param>
		void Set(string_view speaker, string_view content);

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		/// <summary>
		/// Dialogの処理・描画
		/// </summary>
		/// <param name="mode">0:通常(既定) 1:選択肢</param>
		/// <returns>0:終了 1:文字表示演出中 2:通常</returns>
		int Main(int mode = 0);
	};
}
