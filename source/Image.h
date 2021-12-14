#pragma once
#include <vector>
#include <string>
#include "DxLib.h"
#include "Global.h"

using std::vector;
using std::string_view;

namespace Game {
	/// <summary>
	/// Image�N���X�̃��[�V�����̎��
	/// </summary>
	enum class ImageMotionType {
		NOMOTION,		// �Ȃ�
		MOVE_NORM,		// �ړ��i�ʏ�j
		MOVE_ACCEL,		// �ړ��i�����E�������ʕt���j
		JUMP_HOL,		// �W�����v�i���j
		JUMP_VER,		// �W�����v�i�c�j
		ROTATION,		// ��]
	};

	/// <summary>
	/// Image�N���X�̃G�t�F�N�g�̎��
	/// </summary>
	enum class ImageEffctType {
		NOEFFECT,
		FADEOUT,
		FADEIN,
	};

	/// <summary>
	/// Image�N���X�̃��[�V�����̍\����
	/// </summary>
	struct ImageMotion {
								// ���[�V�����̎��
		ImageMotionType imType = ImageMotionType::NOMOTION;
		int x = 0;				// X���W
		int y = 0;				// Y���W
		int frame = 0;			// ���v�t���[��
		double arg = 0.0;		// ����

		int fcounter = 0;		// �t���[���J�E���^

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
	/// �C���[�W�N���X�̃G�t�F�N�g�̍\����
	/// </summary>
	struct ImageEffect {
								// �G�t�F�N�g�̎��
		ImageEffctType ieType = ImageEffctType::NOEFFECT;
		int frame = 0;			// ���v�t���[��

		int fcounter = 0;		// �t���[���J�E���^

		ImageEffect() {

		}

		ImageEffect(ImageEffctType ieType, int frame) {
			this->ieType = ieType;
			this->frame = frame;
		}
	};

	class Image {
	private:
		int gh = 0;		// �O���t�B�b�N�n���h��
		int x = 0;		// �`�捶��X
		int y = 0;		// �`�捶��Y
		int alpha = 0;	// �`��A���t�@�l
						// �`��G�t�F�N�g�Ǘ�vector
		vector<ImageMotion> vImgMotion = vector<ImageMotion>(0);
						// ���[�V�����Ǘ�vector
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
