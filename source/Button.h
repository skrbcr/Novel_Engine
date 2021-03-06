#pragma once
#include <vector>
#include "DxLib.h"
#include "Global.h"

using std::vector;
using color_t = unsigned int;

namespace Game {
	class Button
	{
	private:
		int index = 0;				// 選択中のボタン番号
		int num = 0;				// ボタン数
		int span_ver = 0;			// 垂直方向の移動数
		int span_hol = 0;			// 水平方向の移動数
		int fcounter = 0;			// フレームカウンタ
		int alpha = 0;				// アルファ値

		vector<vector<int>> vvpos;

		color_t color = 0;			// ボタン色


	public:
		Button(int num = 0) {
			vvpos = vector<vector<int>>(num, vector<int>(4));
			index = 0;
			this->num = num;
			span_ver = 0;
			span_hol = 0;
			fcounter = 0;
			alpha = 0;
		}

		/// <summary>
		/// ボタングループを設定
		/// </summary>
		/// <param name="span_ver">上下キーでの垂直方向移動数</param>
		/// <param name="span_hol">左右キーでの水平方向移動数</param>
		/// <param name="color">ボタンの色</param>
		void SetGroup(int span_ver, int span_hol, color_t color = 0xDDDDDD);

		/// <summary>
		/// ボタンを設定
		/// </summary>
		/// <param name="index">ボタン番号</param>
		/// <param name="x">左上x座標</param>
		/// <param name="y">左上y座標</param>
		/// <param name="width">ボタン幅</param>
		/// <param name="height">ボタン高さ</param>
		void SetButton(int index, int x, int y, int width, int height);

		/// <summary>
		/// ボタンを追加（最後尾に追加）
		/// </summary>
		/// <param name="x">左上x座標</param>
		/// <param name="y">左上y座標</param>
		/// <param name="width">ボタン幅</param>
		/// <param name="height">ボタン高さ</param>
		void AddButton(int x, int y, int width, int height);

		/// <summary>
		/// メイン処理・描画
		/// <param name="freeze">フリーズフラグ</param>
		/// </summary>
		int Main(bool freeze);

		void SetSelection(int index);

		int GetSelection() {
			return index;
		}

	private:
		void Draw();
	};
}
