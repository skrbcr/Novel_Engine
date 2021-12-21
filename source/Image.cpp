#include "Image.h"

namespace Game {
	void Image::SetImage(string_view strImgFile, int x, int y, double alpha) {
		gh = LoadGraph(strImgFile.data());
		if (gh <= 0) {
			ErrorLog(ER_IMG_LOAD, strImgFile);
		}
		this->x = x_org = static_cast<double>(x);
		this->y = y_org = static_cast<double>(y);
		this->alpha = alpha;
	}

	void Image::SetMotion(ImageMotionType imType, int x, int y, int frame, int arg) {
		if (frame == 0) {
			frame = 1;
		}

		vImgMotion.push_back(ImageMotion(imType, x, y, frame, arg));

		ImageMotion& im = *vImgMotion.rbegin();
		switch (im.imType) {
		case ImageMotionType::MOVE_NORM_X:
			im.x -= this->x;		// 合計のX方向への移動量
			im._arg1 = this->x;		// 現在の画像X座標
			break;
		case ImageMotionType::MOVE_NORM_Y:
			im.y -= this->y;		// 合計のY方向への移動量
			im._arg1 = this->y;		// 現在の画像Y座標
			break;
		case ImageMotionType::MOVE_ACCEL_X:
			im.x -= this->x;		// 合計のX方向への移動量
			im._arg1 = this->x;		// 現在の画像X座標
			im._arg2 = - im.x / std::pow(im.frame, 3);		// 計算用
			break;
		case ImageMotionType::MOVE_ACCEL_Y:
			im.y -= this->y;		// 合計のY方向への移動量
			im._arg1 = this->y;		// 現在の画像Y座標
			im._arg2 = - im.y / std::pow(im.frame, 3);		// 計算用
			break;
		case ImageMotionType::ROTATION:
			break;
		default:
			break;
		}
	}

	void Image::SetEffect(ImageEffctType ieType, int frame) {
		vImgEffect.push_back(ImageEffect(ieType, frame));
	}

	bool Image::Main() {
		bool res = true;

		if (onShow) {
			for (auto& im : vImgMotion) {
				if (im._fcounter <= im.frame || im._enternal) {
					switch (im.imType) {
					case ImageMotionType::MOVE_NORM_X:
						x = im._arg1 + static_cast<double>(im.x) * im._fcounter / im.frame;
						break;
					case ImageMotionType::MOVE_NORM_Y:
						y = im._arg1 + static_cast<double>(im.y) * im._fcounter / im.frame;
						break;
					case ImageMotionType::MOVE_ACCEL_X:
						x = im._arg1 + im._arg2 * std::pow(im._fcounter, 2.0) * (2 * im._fcounter - 3 * im.frame);
						break;
					case ImageMotionType::MOVE_ACCEL_Y:
						y = im._arg1 + im._arg2 * std::pow(im._fcounter, 2.0) * (2 * im._fcounter - 3 * im.frame);
						break;
					case ImageMotionType::JUMP_X:
						break;
					case ImageMotionType::JUMP_Y:
						break;
					case ImageMotionType::ROTATION:
						break;
					default:
						break;
					}

					if (im._fcounter < im.frame && !im._enternal) {
						res = false;
					}

					im._fcounter++;
				}
			}

			//DrawRotaGraph(static_cast<int>(x), static_cast<int>(y), 1.0, rad, gh, TRUE);
			DrawGraphF(static_cast<float>(x), static_cast<float>(y), gh, TRUE);
		}

		return res;
	}
	void Image::Reset() {
		x = x_org;
		y = y_org;
		for (auto& im : vImgEffect) {
			im.fcounter = 1;
		}
		for (auto& im : vImgMotion) {
			im._fcounter = 1;
		}
	}
}