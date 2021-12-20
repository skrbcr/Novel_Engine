#pragma once
#include <string>
#include "DxLib.h"
#include "Global.h"

using std::string;

namespace Game {
	enum class BGM_effct
	{
		NO_EFFECT,		// �G�t�F�N�g�Ȃ�
		FADE_OUT,		// �t�F�[�h�A�E�g
		FADE_IN,		// �t�F�[�h�C��
		CHANGE_VOL,		// ���ʕύX
	};

	class BGM
	{
	private:
		int sh = 0;							// BGM�T�E���h�n���h��
		string filepath = "";				// �t�@�C���p�X
		int playType = DX_PLAYTYPE_LOOP;	// �Đ����@
		int volume = 255;					// ����(0~255)
		double volume_gen = 1;				// ����(�S�̐ݒ� 0~1.0)
		int duration = 0;					// �t���[����
		int frame = 0;						// �t���[���J�E���^
		bool onPlay = false;				// �Đ����t���O
		bool onChange = false;				// �ύ����t���O
		BGM_effct effectMode = BGM_effct::NO_EFFECT;	// ���݂̃G�t�F�N�g

	private:

	public:
		BGM() {

		}

		void Main();

		/// <summary>
		/// �Đ��J�n
		/// </summary>
		/// <param name="from_zero">�擪����Đ����邩</param>
		void Play(int from_zero);

		/// <summary>
		/// �Đ��J�n
		/// </summary>
		/// <param name="filepath">�T�E���h�n���h��</param>
		/// <param name="playType">�Đ����@(DX_PLAYTYPE_XXX)</param>
		/// <param name="volume">����(0~1.0)</param>
		/// <param name="from_zero">�擪����Đ����邩</param>
		void Play(int sh, int playType, double volume, int from_zero);
		//void Play(string_view filepath, int playType, double volume);

		/// <summary>
		/// �Đ���~
		/// </summary>
		void Pause();

		/// <summary>
		/// ���ʂ�ݒ�
		/// </summary>
		/// <param name="effectType">���ʂ̎��(BGM_effect enum class)</param>
		/// <param name="arg">����</param>
		void SetEffect(BGM_effct effectType, double arg);

		/// <summary>
		/// BGM�S�̂̉��ʐݒ�̕ύX��K�p
		/// </summary>
		/// <param name="volume">����(0~1.0)</param>
		void SetGeneralVolume(double volume);
	};
}
