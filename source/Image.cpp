#include "Image.h"

namespace Game {
	void Image::SetImage(string_view strImgFile, int x, int y, double alpha) {
		gh = LoadGraph(strImgFile.data());
		if (gh <= 0) {
			ErrorLog(ER_IMG_LOAD, strImgFile);
		}
		this->x = x_org = static_cast<double>(x);
		this->y = y_org = static_cast<double>(y);
		this->alpha = alpha_org = alpha;
	}

	void Image::ChangeImage(string_view strImgFile) {
		DeleteGraph(gh);
		gh = LoadGraph(strImgFile.data());
		if (gh <= 0) {
			ErrorLog(ER_IMG_LOAD, strImgFile);
		}
	}

	void Image::SetDefPos(int x, int y, double alpha) {
		this->x = x_org = static_cast<double>(x);
		this->y = y_org = static_cast<double>(y);
		this->alpha = alpha_org = alpha;
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
						x = im._arg1 + im._arg2 * std::pow(im._fcounter, 2.) * (2. * im._fcounter - 3. * im.frame);
						break;
					case ImageMotionType::MOVE_ACCEL_Y:
						y = im._arg1 + im._arg2 * std::pow(im._fcounter, 2.) * (2. * im._fcounter - 3. * im.frame);
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

			for (auto& ie : vImgEffect) {
				if (ie._fcounter <= ie.frame) {
					switch (ie.ieType) {
					case ImageEffctType::FADEIN:
						alpha = alpha_org * ie._fcounter / ie.frame;
						break;
					case ImageEffctType::FADEOUT:
						alpha = alpha_org * (1.0 - static_cast<double>(ie._fcounter) / ie.frame);
						break;
					default:
						break;
					}

					if (ie._fcounter < ie.frame) {
						res = false;
					}

					ie._fcounter++;
				}
			}

			//DrawRotaGraph(static_cast<int>(x), static_cast<int>(y), 1.0, rad, gh, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha * 255));
			DrawGraphF(static_cast<float>(x), static_cast<float>(y), gh, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		return res;
	}

	void Image::Reset() {
		x = x_org;
		y = y_org;
		alpha = alpha_org;
		vImgEffect.clear();
		vImgEffect.clear();
	}
}