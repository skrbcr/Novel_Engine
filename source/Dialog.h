#pragma once
#include <string>
#include <string_view>
#include "Global.h"
#include "Utilities.h"

using string = std::string;
using string_view = std::string_view;

namespace Game {
	// �����F���X�g(�����̓s����A10�܂œo�^�\)
	constexpr color_t colorList[10] =
	{ 0xFFFFFF, 0xff0000, 0xFFCCFF, 0xffff00, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000 };

	/// <summary>
	/// �Z���t�N���X
	/// </summary>
	class Dialog
	{
	public:
		static int gh_box;			// ���b�Z�[�W�{�b�N�X�̉摜
		static int msgwnd_left;		// ���b�Z�[�W�{�b�N�X�̍��[
		static int msgwnd_top;		// ���b�Z�[�W�{�b�N�X�̏�[
		static int msgwnd_width;	// ���b�Z�[�W�{�b�N�X�̕�
		static int msgwnd_height;	// ���b�Z�[�W�{�b�N�X�̍���
		static int msgspk_left;		// �b�҂̍��[�i���΍��W�j
		static int msgspk_top;		// �b�҂̏�[�i���΍��W�j
		static int msgtxt_left;		// �\���e�L�X�g�̍��[�i���΍��W�j
		static int msgtxt_top;		// �\���e�L�X�g�̏�[�i���΍��W�j

	private:
		string strSpeaker;		// �b�ҕ�����
		string strContent;		// ���e������
		size_t nLenSpeaker;		// �b�ҕ�����T�C�Y
		size_t nLenContent;		// ���e������T�C�Y
		bool onDisplay;			// �_�C�A���O�{�b�N�X�\������

		int status;				// �`�惂�[�h
		string strContDisp;		// ���ۂɕ\������p�̕�����
		size_t index_strCont;	// �\�������ꐔ�C���f�b�N�X
		size_t nWordContnet;	// ���e������̌ꐔ

		int fcounter;		// �t���[���J�E���^
		int mode;			// �\�����[�h

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Dialog() {
			strSpeaker = "";
			strContent = "";
			nLenSpeaker = (size_t)0;
			nLenContent = (size_t)0;
			onDisplay = true;
			status = 0;
			strContDisp = "";
			index_strCont = 0;
			nWordContnet = (size_t)0;
		}

		static void ApplyMsgWndCongig(int gh, int left, int top, int width, int height) {
			gh_box = gh;
			msgwnd_left = left;
			msgwnd_top = top;
			msgwnd_width = width;
			msgwnd_height = height;
		}

		static void ApplyMsgSpkConfig(int left, int top) {
			msgspk_left = left;
			msgspk_top = top;
		}

		static void ApplyMsgTxtConfig(int left, int top) {
			msgtxt_left = left;
			msgtxt_top = top;
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
