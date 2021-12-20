#pragma once
#include <string>
#include <string_view>
#include "Global.h"
#include "Utilities.h"

using string = std::string;
using string_view = std::string_view;

namespace Game {
	/* ダイアログボックスに合わせて設定 */
	constexpr int DLGBOX_WIDTH = 1014;		// メッセージボックスの幅
	constexpr int DLGBOX_HEIGHT = 212;		// メッセージボックスの高さ
	constexpr int DLGBOX_TOP = 488;			// メッセージボックス上端のy座標
	constexpr int DLGBOX_LEFT = 133;		// メッセージボックス左端のx座標

	// 文字色リスト(処理の都合上、10個まで登録可能)
	constexpr color_t colorList[10] =
	{ 0xFFFFFF, 0xff0000, 0xFFCCFF, 0xffff00, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000 };

	/// <summary>
	/// セリフクラス
	/// </summary>
	class Dialog
	{
	private:
		string strSpeaker = "";				// 話者文字列
		string strContent = "";				// 内容文字列
		size_t nLenSpeaker = (size_t)0;		// 話者文字列サイズ
		size_t nLenContent = (size_t)0;		// 内容文字列サイズ
		bool onDisplay = true;				// ダイアログボックス表示中か

		int status = 0;			// 描画モード
		string strContDisp = "";			// 実際に表示する用の文字列
		size_t index_strCont = 0;			// 表示文字語数インデックス
		size_t nWordContnet = (size_t)0;	// 内容文字列の語数

		int fcounter = 0;	// フレームカウンタ
		int mode = 0;		// 表示モード
		static int gh_box;		// メッセージボックスの画像

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Dialog() {

		}

		/// <summary>
		/// コンストラクタ（メッセージウィンドウ画像を指定）
		/// </summary>
		/// <param name="gh">メッセージウィンドウのグラフィックハンドル</param>
		Dialog(int gh) {
			gh_box = gh;
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
