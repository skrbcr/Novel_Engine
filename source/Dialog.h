#pragma once
#include <cmath>
#include <vector>
#include <string>
#include <string_view>
#include "Global.h"
#include "Utilities.h"

using std::vector;
using std::string;
using std::string_view;

namespace Game {
	struct Font {
		int fh = 0;
		int height = 0;
	};

	struct FontName {
		string strFont = "";
		int size = 0;
		int thick = 0;
	};
	

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
		static color_t msgspk_color;// 話者の文字色
		static int msgtxt_left;		// 表示テキストの左端（相対座標）
		static int msgtxt_top;		// 表示テキストの上端（相対座標）
		static vector<Font> fontList;		// フォントリスト
		static vector<color_t> colorList;	// 文字色リスト

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

		static void ApplyConfig(json& js);

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
