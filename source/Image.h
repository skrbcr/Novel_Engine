#pragma once
#include <vector>
#include <string>
#include "DxLib.h"
#include "Global.h"

using std::vector;
using std::string_view;

namespace Game {
	/// <summary>
	/// Imageクラスのモーションの種類
	/// </summary>
	enum class ImageMotionType {
		NOMOTION,		// なし
		MOVE_NORM,		// 移動（通常）
		MOVE_ACCEL,		// 移動（加速・減速効果付き）
		JUMP_HOL,		// ジャンプ（横）
		JUMP_VER,		// ジャンプ（縦）
		ROTATION,		// 回転
	};

	/// <summary>
	/// Imageクラスのエフェクトの種類
	/// </summary>
	enum class ImageEffctType {
		NOEFFECT,
		FADEOUT,
		FADEIN,
	};

	/// <summary>
	/// Imageクラスのモーションの構造体
	/// </summary>
	struct ImageMotion {
								// モーションの種類
		ImageMotionType imType = ImageMotionType::NOMOTION;
		int x = 0;				// X座標
		int y = 0;				// Y座標
		int frame = 0;			// 所要フレーム
		double arg = 0.0;		// 引数

		int fcounter = 0;		// フレームカウンタ

		ImageMotion() {
			x = 0;
			y = 0;
			frame = 0;
			arg = 0.0;
			fcounter = 0;
		}

		ImageMotion(ImageMotionType imType, int x, int y, int frame, double arg) {
			this->imType = imType;
			this->x = x;
			this->y = y;
			this->frame = frame;
			this->arg = arg;
			fcounter = 0;
		}
	};

	/// <summary>
	/// イメージクラスのエフェクトの構造体
	/// </summary>
	struct ImageEffect {
								// エフェクトの種類
		ImageEffctType ieType = ImageEffctType::NOEFFECT;
		int frame = 0;			// 所要フレーム

		int fcounter = 0;		// フレームカウンタ

		ImageEffect() {

		}

		ImageEffect(ImageEffctType ieType, int frame) {
			this->ieType = ieType;
			this->frame = frame;
		}
	};

	class Image {
	private:
		int gh = 0;		// グラフィックハンドル
		int x = 0;		// 描画左上X
		int y = 0;		// 描画左上Y
		int alpha = 0;	// 描画アルファ値
						// 描画エフェクト管理vector
		vector<ImageMotion> vImgMotion = vector<ImageMotion>(0);
						// モーション管理vector
		vector<ImageEffect> vImgEffct = vector<ImageEffect>(0);

	public:
		Image() {

		}

		~Image() {
			DeleteGraph(gh);
		}

		void SetImage(string_view strImgFile, int x, int y, int alpha);

		void SetMotion(ImageMotionType imType, int x, int y, int frame, int arg);

		void SetEffect(ImageEffctType ieType, int frame);
	};
}
