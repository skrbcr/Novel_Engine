#pragma once
#include "DxLib.h"
#include "Global.h"

namespace Game {
	/// <summary>
	/// �w�i���[�V�����񋓌^
	/// </summary>
	enum class backMotion
	{
		NO_MOTION,		// �Ȃ�
		MOVE_VER,		// �w�i�摜�̏㉺�ړ� ����1:�ړ�px(������) ����2:���v�t���[��
		MOVE_HOL,		// �w�i�摜�̍��E�ړ� ����1:�ړ�px(�E����) ����2:���v�t���[��
		SHAKE,			// �摜�h�炵 ����1: ����2:
	};

	class BackImage
	{
	private:
		int gh = 0;				// �w�i�摜�O���t�B�b�N�n���h��
		double drawX = 0.0;		// �`��x���W
		double drawY = 0.0;		// �`��y���W
		int fcount = 0;			// �t���[���J�E���^

		backMotion bmotion = backMotion::NO_MOTION;
		int duration = 0;		// ���[�V��������
		double arg_m1 = 0.0;	// ���[�V��������1
		double arg_m2 = 0.0;	// ���[�V��������2

	public:
		BackImage() {

		}

		~BackImage() {

		}

		void Set(int gh, double x, double y);

		void SetMotion(backMotion mType, double arg1, double arg2);

		void Main();
	};
}
