#include "Image.h"

namespace Game {
	void Image::SetImage(string_view strImgFile, int x, int y, int alpha) {
		gh = LoadGraph(strImgFile.data());
		if (gh <= 0) {
			ErrorLog(ER_IMG_LOAD, strImgFile);
		}
		this->x = x;
		this->y = y;
		this->alpha = alpha;
	}

	void Image::SetMotion(ImageMotionType imType, int x, int y, int frame, int arg) {
		vImgMotion.push_back(ImageMotion(imType, x, y, frame, arg));
	}

	void Image::SetEffect(ImageEffctType ieType, int frame) {
		vImgEffct.push_back(ImageEffect(ieType, frame));
	}
}