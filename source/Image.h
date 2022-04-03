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
		int gh;				// グラフィックハンドル
		double x;			// 描画左上X
		double y;			// 描画左上Y
		double alpha;		// 描画アルファ値
		double x_org;		// X座標（元）
		double y_org;		// Y座標（元）
		double alpha_org;	// アルファ値（元）
		double rad;			// 回転角度
		bool onShow;		// 表示フラグ						
		vector<ImageMotion> vImgMotion;		// 描画エフェクト管理vector
		vector<ImageEffect> vImgEffect;		// モーション管理vector

	public:
		Image() {
			gh = 0;
			x = 0.0;
			y = 0.0;
			alpha = 0;
			x_org = 0.0;
			y_org = 0.0;
			alpha_org = 0.0;
			rad = 0;
			onShow = false;
			vImgMotion = vector<ImageMotion>(0);
			vImgEffect = vector<ImageEffect>(0);
		}

		~Image() {
			DeleteGraph(gh);
		}

		/// <summary>
		/// 画像を設定
		/// </summary>
		/// <param name="strImgFile"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="alpha"></param>
		void SetImage(string_view strImgFile, int x, int y, double alpha);

		/// <summary>
		/// 画像のみを変更
		/// </summary>
		/// <param name="strImgFile"></param>
		void ChangeImage(string_view strImgFile);

		/// <summary>
		/// デフォルトの位置を設定
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="alpha"></param>
		void SetDefPos(int x, int y, double alpha);

		/// <summary>
		/// モーションを設定
		/// </summary>
		/// <param name="imType"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="frame"></param>
		/// <param name="arg"></param>
		void SetMotion(ImageMotionType imType, int x, int y, int frame, int arg);

		/// <summary>
		/// エフェクトを設定
		/// </summary>
		/// <param name="ieType"></param>
		/// <param name="frame"></param>
		void SetEffect(ImageEffctType ieType, int frame);

		/// <summary>
		/// 画像のメイン処理
		/// </summary>
		/// <returns>true:効果継続中 false:効果なし</returns>
		bool Main();

		/// <summary>
		/// 表示状態を変更
		/// </summary>
		/// <param name="flag">表示フラグ</param>
		void ChangeVisible(bool flag) {
			onShow = flag;
		}

		/// <summary>
		/// 画像をデフォルトの状態に戻す
		/// </summary>
		void Reset();

		/// <summary>
		/// 画像を削除
		/// </summary>
		void Clear() {
			DeleteGraph(gh);
			gh = 0;
			onShow = false;
		}
	};
}
