#pragma once
#include "DxLib.h"
#include "Global.h"

namespace Game {
	/// <summary>
	/// 背景モーション列挙型
	/// </summary>
	enum class backMotion
	{
		NO_MOTION,		// なし
		MOVE_VER,		// 背景画像の上下移動 引数1:移動px(下が正) 引数2:所要フレーム
		MOVE_HOL,		// 背景画像の左右移動 引数1:移動px(右が正) 引数2:所要フレーム
		SHAKE,			// 画像揺らし 引数1: 引数2:
	};

	class BackImage
	{
	private:
		int gh = 0;				// 背景画像グラフィックハンドル
		double drawX = 0.0;		// 描画x座標
		double drawY = 0.0;		// 描画y座標
		int fcount = 0;			// フレームカウンタ

		backMotion bmotion = backMotion::NO_MOTION;
		int duration = 0;		// モーション時間
		double arg_m1 = 0.0;	// モーション引数1
		double arg_m2 = 0.0;	// モーション引数2

	public:
		BackImage() {

		}

		~BackImage() {

		}

		void Set(int gh, double x, double y);

		void SetMotion(backMotion mType, double arg1, double arg2);

		void Main();
	};
}
