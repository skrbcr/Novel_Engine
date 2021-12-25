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
		//MOVE_NORM,		// 移動（通常）
		MOVE_NORM_X,	// 移動（通常・X方向）
		MOVE_NORM_Y,	// 移動（通常・Y方向）
		//MOVE_ACCEL,		// 移動（加速・減速効果付き）
		MOVE_ACCEL_X,	// 移動（加速・減速効果付き・X方向）
		MOVE_ACCEL_Y,	// 移動（加速・減速効果付き・Y方向）
		JUMP_X,			// ジャンプ（X方向）
		JUMP_Y,			// ジャンプ（Y方向）
		ROTATION,		// 回転
	};

	/// <summary>
	/// Imageクラスのエフェクトの種類
	/// </summary>
	enum class ImageEffctType {
		NOEFFECT,		// なし
		FADEOUT,		// フェードアウト
		FADEIN,			// フェードイン
	};

	/// <summary>
	/// Imageクラスのモーションの構造体
	/// </summary>
	struct ImageMotion {
								// モーションの種類
		ImageMotionType imType = ImageMotionType::NOMOTION;
		double x = 0;			// X座標
		double y = 0;			// Y座標
		int frame = 0;			// 所要フレーム
		double arg = 0.0;		// 引数

		int _fcounter = 1;		// フレームカウンタ
		double _arg1 = 0;		// 内部処理用引数１	
		double _arg2 = 0;		// 内部処理用引数２
		bool _enternal = false;	// 永続フラグ

		ImageMotion() {
			x = 0.0;
			y = 0.0;
			frame = 0;
			arg = 0.0;
			_fcounter = 1;
			_arg1 = 0.0;
			_arg2 = 0.0;
			_enternal = false;
		}

		ImageMotion(ImageMotionType imType, double x, double y, int frame, double arg) {
			this->imType = imType;
			this->x = x;
			this->y = y;
			this->frame = frame;
			this->arg = arg;
			_fcounter = 1;
			_arg1 = 0.0;
			_arg2 = 0.0;

			if (this->frame == -1) {
				_enternal = true;
			}
			else {
				_enternal = false;
			}
		}
	};

	/// <summary>
	/// イメージクラスのエフェクトの構造体
	/// </summary>
	struct ImageEffect {
								// エフェクトの種類
		ImageEffctType ieType = ImageEffctType::NOEFFECT;
		int frame = 0;			// 所要フレーム

		int _fcounter = 0;		// フレームカウンタ

		ImageEffect() {

		}

		ImageEffect(ImageEffctType ieType, int frame) {
			this->ieType = ieType;
			this->frame = frame;
		}
	};

	class Image {
	private:
		int gh = 0;				// グラフィックハンドル
		double x = 0.0;			// 描画左上X
		double y = 0.0;			// 描画左上Y
		double alpha = 0;		// 描画アルファ値
		double x_org = 0.0;		// X座標（元）
		double y_org = 0.0;		// Y座標（元）
		double alpha_org = 0.0;	// アルファ値（元）
		double rad = 0;			// 回転角度
		bool onShow = false;	// 表示フラグ

						// 描画エフェクト管理vector
		vector<ImageMotion> vImgMotion = vector<ImageMotion>(0);
						// モーション管理vector
		vector<ImageEffect> vImgEffect = vector<ImageEffect>(0);

	public:
		Image() {

		}

		~Image() {
			DeleteGraph(gh);
		}

		void SetImage(string_view strImgFile, int x, int y, double alpha);

		void SetMotion(ImageMotionType imType, int x, int y, int frame, int arg);

		void SetEffect(ImageEffctType ieType, int frame);

		/// <summary>
		/// 画像のメイン処理
		/// </summary>
		/// <returns>true:効果継続中 false:効果なし</returns>
		bool Main();

		void ChangeVisible(bool flag) {
			onShow = flag;
		}

		void Reset();
	};
}
