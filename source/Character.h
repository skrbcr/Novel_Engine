#pragma once
#include <vector>
#include <string>
#include "Global.h"

using std::vector;
using std::string_view;

struct CharaImg
{
	int gh_body = 0;		// body グラフィックハンドル
	int gh_face = 0;		// face グラフィックハンドル
	string strPos = "";		// 配置コマンド
	int x = 0;				// 画像x座標
	int y = 0;				// 画像y座標
};

//struct CharaPos
//{
//	string strPos = "";
//	int x = 0;
//	int y = 0;
//};

namespace Game {
	class Character
	{
	private:
		//vector<CharaPos> vpos = vector<CharaPos>(0);		// 画像配置情報配列
		vector<CharaImg> vchara = vector<CharaImg>(0);		// キャラクター画像データ配列
		size_t nSizeVchara = 0;

	public:
		Character() {

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
		/// CharaImg 配列を生成
		/// </summary>
		//void MakeCharaImg();

		/// <summary>
		/// body 画像を設定
		/// </summary>
		/// <param name="gh"></param>
		/// <param name="strPos"></param>
		void SetBody(int gh, string_view strPos);

		/// <summary>
		/// face 画像を設定
		/// </summary>
		/// <param name="gh"></param>
		/// <param name="strPos"></param>
		void SetFace(int gh, string_view strPos);

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
	};
}

