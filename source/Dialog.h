#pragma once
#include <string>
#include <string_view>
#include "Global.h"

using string = std::string;
using string_view = std::string_view;

namespace Game {
	/* �_�C�A���O�{�b�N�X�ɍ��킹�Đݒ� */
	constexpr int DLGBOX_WIDTH = 1014;		// ���b�Z�[�W�{�b�N�X�̕�
	constexpr int DLGBOX_HEIGHT = 212;		// ���b�Z�[�W�{�b�N�X�̍���
	constexpr int DLGBOX_TOP = 488;			// ���b�Z�[�W�{�b�N�X��[��y���W
	constexpr int DLGBOX_LEFT = 133;		// ���b�Z�[�W�{�b�N�X���[��x���W

	/* �萔 */
	//constexpr int DLGM_NORMAL = 0;			// �ʏ�
	//constexpr int DLGM_FINISH = 1;			// ��b�I��
	//constexpr int DLGM_EFFSET = 2;			// �G�t�F�N�g�Z�b�g

	// �����F���X�g(�����̓s����A10�܂œo�^�\)
	constexpr color_t colorList[10] =
	{ 0xFFFFFF, 0xff0000, 0xFFCCFF, 0xffff00, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000 };

	/// <summary>
	/// �Z���t�N���X
	/// </summary>
	class Dialog
	{
	private:
		string strSpeaker = "";				// �b�ҕ�����
		string strContent = "";				// ���e������
		size_t nLenSpeaker = (size_t)0;		// �b�ҕ�����T�C�Y
		size_t nLenContent = (size_t)0;		// ���e������T�C�Y
		bool onDisplay = true;				// �_�C�A���O�{�b�N�X�\������

		int status = 0;			// �`�惂�[�h
		string strContDisp = "";			// ���ۂɕ\������p�̕�����
		size_t index_strCont = 0;			// �\�������ꐔ�C���f�b�N�X
		size_t nWordContnet = (size_t)0;	// ���e������̌ꐔ

		int fcounter = 0;
		int mode = 0;

	public:
		static int gh_box;			// ���b�Z�[�W�{�b�N�X�̉摜

		/// <summary>
		/// Dialog�N���X�̃R���X�g���N�^
		/// </summary>
		Dialog() {

		}

		/// <summary>
		/// Dialog��o�^
		/// </summary>
		/// <param name="speaker">�b�ҕ�����</param>
		/// <param name="content">���e������</param>
		void Set(string_view speaker, string_view content);

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

		/// <summary>
		/// Dialog�̏����E�`��
		/// </summary>
		/// <param name="mode">0:�ʏ�(����) 1:�I����</param>
		/// <returns>0:�I�� 1:�����\�����o�� 2:�ʏ�</returns>
		int Main(int mode = 0);
	};
}
