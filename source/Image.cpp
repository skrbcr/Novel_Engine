#include "Image.h"

namespace Game {
	void Image::SetImage(string_view strImgFile, int x, int y, double alpha) {
		gh = LoadGraph(strImgFile.data());
		if (gh <= 0) {
			ErrorLog(ER_IMG_LOAD, strImgFile);
		}
		this->x = static_cast<double>(x);
		this->y = static_cast<double>(y);
		this->alpha = alpha;
	}

	void Image::SetMotion(ImageMotionType imType, int x, int y, int frame, int arg) {
		if (frame == 0) {
			frame = 1;
		}

		vImgMotion.push_back(ImageMotion(imType, x, y, frame, arg));
		ImageMotion& im = vImgMotion[vImgMotion.size() - 1];
		switch (im.imType) {
		//case ImageMotionType::MOVE_NORM:
		//	im._arg1 = (im.x - this->x) / im.frame;	// 毎フレームのX方向への移動量
		//	im._arg2 = (im.y - this->y) / im.frame;	// 毎フレームのY方向への移動量
		//	break;
		case ImageMotionType::MOVE_NORM_X:
			im.x -= this->x;		// 合計のX方向への移動量
			im._arg1 = this->x;		// 現在の画像X座標
			break;
		case ImageMotionType::MOVE_NORM_Y:
			im.y -= this->y;		// 合計のY方向への移動量
			im._arg1 = this->y;		// 現在の画像Y座標
			break;
		//case ImageMotionType::MOVE_ACCEL:
		//	im._arg1 = im.x - this->x;		// 合計のX方向への移動量
		//	im._arg2 = im.y - this->y;		// 合計のY方向への移動量
		//	break;
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
		//case ImageMotionType::JUMP_X:
		//	im._arg1 = im.x - this->x;
		//	break;
		//case ImageMotionType::JUMP_Y:
		//	im._arg2 = im.y - this->y;
		//	break;
		case ImageMotionType::ROTATION:
			break;
		default:
			break;
		}
	}

	void Image::SetEffect(ImageEffctType ieType, int frame) {
		vImgEffct.push_back(ImageEffect(ieType, frame));
	}

	void Image::Main() {
		size_t n = vImgMotion.size();
		for (int i = 0; i < n; ++i) {
			ImageMotion& im = vImgMotion[i];
			if (im._fcounter <= im.frame) {
				switch (vImgMotion[i].imType) {
					//case ImageMotionType::MOVE_NORM:
					//	x += im._arg1;
					//	y += im._arg2;
					//	break;
				case ImageMotionType::MOVE_NORM_X:
					x = im._arg1 + static_cast<double>(im.x) * im._fcounter / im.frame;
					break;
				case ImageMotionType::MOVE_NORM_Y:
					y = im._arg1 + static_cast<double>(im.y) * im._fcounter / im.frame;
					break;
					//case ImageMotionType::MOVE_ACCEL:
					//	x += 12 * im._arg1 * (std::pow(im._fcounter, 2.0) - (im.frame + 1) * im._fcounter + (std::pow(im.frame, 2.0) / 4 + im.frame / 2.0 + 1.0 / 3)) / std::pow(im.frame, 3.0);
					//	y += 12 * im._arg2 * (std::pow(im._fcounter, 2.0) - (im.frame + 1) * im._fcounter + (std::pow(im.frame, 2.0) / 4 + im.frame / 2.0 + 1.0 / 3)) / std::pow(im.frame, 3.0);
					//	break;
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

				vImgMotion[i]._fcounter++;
			}
		}

		//DrawRotaGraph(static_cast<int>(x), static_cast<int>(y), 1.0, rad, gh, TRUE);
		DrawGraphF(static_cast<float>(x), static_cast<float>(y), gh, TRUE);
	}
}