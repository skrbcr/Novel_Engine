#pragma once
#include "DxLib.h"
#include "Global.h"

/* Effect�N���X�̎g����
 * FADE_OUT��͉������Ȃ��ƃG�t�F�N�g���|���葱����
 */

using color_t = unsigned int;

namespace Game {
	/// <summary>
	/// �`����ʗ񋓌^
	/// </summary>
	enum class effectType
	{
		NO_EFFECT,		// ���ʂȂ��i�ʏ�j
		FADE_OUT,		// �t�F�[�h�A�E�g
		FADE_IN,		// �t�F�[�h�C��
		FLASH,			// �_��
		WAIT,			// �ҋ@
	};

	class Effect
	{
	private:
		effectType eType = effectType::NO_EFFECT;		// �G�t�F�N�g���
		int frame = 0;									// ���v�t���[��
		int frame_after = 0;							// �G�t�F�N�g��ҋ@�t���[��
		color_t color = 0x000000;						// �G�t�F�N�g�F

		int fcount = 0;			// �t���[���J�E���^

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Effect() {

		}

		/// <summary>
		/// �G�t�F�N�g�̐ݒ�
		/// </summary>
		/// <param name="eType">���</param>
		/// <param name="frame">���v�t���[��</param>
		/// <param name="frame_after">�G�t�F�N�g��t���[��</param>
		/// <param name="color">�F</param>
		void Set(effectType eType, int frame, int frame_after, color_t color);

		/// <summary>
		/// �G�t�F�N�g�̎��s
		/// </summary>
		/// <returns>true:���s�� false:�Ȃ�</returns>
		bool Main();
	};
}
