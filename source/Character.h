#pragma once
#include <vector>
#include <string>
#include "Global.h"
#include "Image.h"

using std::vector;
using std::string_view;

namespace Game {
	struct CharaImg {
		Image img_body;		// 土台画像
		Image img_face;		// 上乗せ画像
		string strPos;		// 配置コマンド
		int x;				// 画像x座標
		int y;				// 画像y座標

		CharaImg() {
			img_body = Image();
			img_face = Image();
			strPos = "";
			x = 0;
			y = 0;
		}
	};

	class Character
	{
	private:
		vector<CharaImg> vchara;		// キャラクター画像データ配列

	public:
		Character() {
			vchara = vector<CharaImg>(0);
		}

		Character(size_t nSizeVchara) {
			vchara = vector<CharaImg>(nSizeVchara);
		}

		~Character() {

		}

		/// <summary>
		/// 画像情報配列に追加
		/// </summary>
		/// <param name="index">要素番号</param>
		/// <param name="strPos">位置コマンド</param>
		/// <param name="x">画像左上 x座標</param>
		/// <param name="y">画像左上 座標</param>
		void SetCharaPos(size_t index, string_view strPos, int x, int y);

		/// <summary>
		/// body 画像を設定
		/// </summary>
		/// <param name="strFile">画像ファイル</param>
		/// <param name="strPos">位置コマンド</param>
		void SetBody(string_view strFile, string_view strPos);

		/// <summary>
		/// body 画像のみを変更
		/// </summary>
		/// <param name="strFile">画像ファイル</param>
		/// <param name="strPos">位置コマンド</param>
		void ChangeBody(string_view strFile, string_view strPos);

		/// <summary>
		/// face 画像のみを変更
		/// </summary>
		/// <param name="strFile"></param>
		/// <param name="strPos"></param>
		void ChangeFace(string_view strFile, string_view strPos);

		/// <summary>
		/// body 画像を削除
		/// </summary>
		/// <param name="strPos">配置コマンド</param>
		void DeleteBody(string_view strPos);

		/// <summary>
		/// face 画像を削除
		/// </summary>
		/// <param name="strPos">配置コマンド</param>
		void DeleteFace(string_view strPos);

		/// <summary>
		/// メイン関数
		/// </summary>
		void Main();

		/// <summary>
		/// 全消去(キャラ画像・エフェクト・モーション)
		/// </summary>
		void Clear();
	};
}

