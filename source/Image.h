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
		int gh;				// �O���t�B�b�N�n���h��
		double x;			// �`�捶��X
		double y;			// �`�捶��Y
		double alpha;		// �`��A���t�@�l
		double x_org;		// X���W�i���j
		double y_org;		// Y���W�i���j
		double alpha_org;	// �A���t�@�l�i���j
		double rad;			// ��]�p�x
		bool onShow;		// �\���t���O						
		vector<ImageMotion> vImgMotion;		// �`��G�t�F�N�g�Ǘ�vector
		vector<ImageEffect> vImgEffect;		// ���[�V�����Ǘ�vector

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
		/// �摜��ݒ�
		/// </summary>
		/// <param name="strImgFile"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="alpha"></param>
		void SetImage(string_view strImgFile, int x, int y, double alpha);

		/// <summary>
		/// �摜�݂̂�ύX
		/// </summary>
		/// <param name="strImgFile"></param>
		void ChangeImage(string_view strImgFile);

		/// <summary>
		/// �f�t�H���g�̈ʒu��ݒ�
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="alpha"></param>
		void SetDefPos(int x, int y, double alpha);

		/// <summary>
		/// ���[�V������ݒ�
		/// </summary>
		/// <param name="imType"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="frame"></param>
		/// <param name="arg"></param>
		void SetMotion(ImageMotionType imType, int x, int y, int frame, int arg);

		/// <summary>
		/// �G�t�F�N�g��ݒ�
		/// </summary>
		/// <param name="ieType"></param>
		/// <param name="frame"></param>
		void SetEffect(ImageEffctType ieType, int frame);

		/// <summary>
		/// �摜�̃��C������
		/// </summary>
		/// <returns>true:���ʌp���� false:���ʂȂ�</returns>
		bool Main();

		/// <summary>
		/// �\����Ԃ�ύX
		/// </summary>
		/// <param name="flag">�\���t���O</param>
		void ChangeVisible(bool flag) {
			onShow = flag;
		}

		/// <summary>
		/// �摜���f�t�H���g�̏�Ԃɖ߂�
		/// </summary>
		void Reset();

		/// <summary>
		/// �摜���폜
		/// </summary>
		void Clear() {
			DeleteGraph(gh);
			gh = 0;
			onShow = false;
		}
	};
}
