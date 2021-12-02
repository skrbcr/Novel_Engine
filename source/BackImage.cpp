#include "BackImage.h"

namespace Game {
	void BackImage::Set(int gh, double x, double y) {
		this->gh = gh;
		drawX = x;
		drawY = y;

		arg_m1 = 0.0;
		arg_m2 = 0.0;
	}

	void BackImage::SetMotion(backMotion mType, double arg1, double arg2) {
		bmotion = mType;
		fcount = 0;

		switch (mType)
		{
		case Game::backMotion::MOVE_VER:
		case Game::backMotion::MOVE_HOL:
			arg_m1 = arg1 / arg2;
			duration = static_cast<int>(arg2);
			break;
		}
	}

	void BackImage::Main() {
		DrawGraph(static_cast<int>(drawX), static_cast<int>(drawY), gh, FALSE);

		if (bmotion != backMotion::NO_MOTION && fcount <= duration) {
			switch (bmotion)
			{
			case Game::backMotion::MOVE_VER:
				drawY += arg_m1;
				break;
			case Game::backMotion::MOVE_HOL:
				drawX += arg_m1;
				break;
			case Game::backMotion::SHAKE:
				break;
			default:
				break;
			}
			fcount++;
		}
	}
}