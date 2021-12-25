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
		//MOVE_NORM,		// �ړ��i�ʏ�j
		MOVE_NORM_X,	// �ړ��i�ʏ�EX�����j
		MOVE_NORM_Y,	// �ړ��i�ʏ�EY�����j
		//MOVE_ACCEL,		// �ړ��i�����E�������ʕt���j
		MOVE_ACCEL_X,	// �ړ��i�����E�������ʕt���EX�����j
		MOVE_ACCEL_Y,	// �ړ��i�����E�������ʕt���EY�����j
		JUMP_X,			// �W�����v�iX�����j
		JUMP_Y,			// �W�����v�iY�����j
		ROTATION,		// ��]
	};

	/// <summary>
	/// Image�N���X�̃G�t�F�N�g�̎��
	/// </summary>
	enum class ImageEffctType {
		NOEFFECT,		// �Ȃ�
		FADEOUT,		// �t�F�[�h�A�E�g
		FADEIN,			// �t�F�[�h�C��
	};

	/// <summary>
	/// Image�N���X�̃��[�V�����̍\����
	/// </summary>
	struct ImageMotion {
								// ���[�V�����̎��
		ImageMotionType imType = ImageMotionType::NOMOTION;
		double x = 0;			// X���W
		double y = 0;			// Y���W
		int frame = 0;			// ���v�t���[��
		double arg = 0.0;		// ����

		int _fcounter = 1;		// �t���[���J�E���^
		double _arg1 = 0;		// ���������p�����P	
		double _arg2 = 0;		// ���������p�����Q
		bool _enternal = false;	// �i���t���O

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
	/// �C���[�W�N���X�̃G�t�F�N�g�̍\����
	/// </summary>
	struct ImageEffect {
								// �G�t�F�N�g�̎��
		ImageEffctType ieType = ImageEffctType::NOEFFECT;
		int frame = 0;			// ���v�t���[��

		int _fcounter = 0;		// �t���[���J�E���^

		ImageEffect() {

		}

		ImageEffect(ImageEffctType ieType, int frame) {
			this->ieType = ieType;
			this->frame = frame;
		}
	};

	class Image {
	private:
		int gh = 0;				// �O���t�B�b�N�n���h��
		double x = 0.0;			// �`�捶��X
		double y = 0.0;			// �`�捶��Y
		double alpha = 0;		// �`��A���t�@�l
		double x_org = 0.0;		// X���W�i���j
		double y_org = 0.0;		// Y���W�i���j
		double alpha_org = 0.0;	// �A���t�@�l�i���j
		double rad = 0;			// ��]�p�x
		bool onShow = false;	// �\���t���O

						// �`��G�t�F�N�g�Ǘ�vector
		vector<ImageMotion> vImgMotion = vector<ImageMotion>(0);
						// ���[�V�����Ǘ�vector
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
		/// �摜�̃��C������
		/// </summary>
		/// <returns>true:���ʌp���� false:���ʂȂ�</returns>
		bool Main();

		void ChangeVisible(bool flag) {
			onShow = flag;
		}

		void Reset();
	};
}
