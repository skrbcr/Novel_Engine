#pragma once
#include <cmath>
#include <vector>
#include <string>
#include <string_view>
#include "Global.h"
#include "Utilities.h"

using std::vector;
using std::string;
using std::string_view;

namespace Game {
	struct Font {
		int fh = 0;
		int height = 0;
	};

	struct FontName {
		string strFont = "";
		int size = 0;
		int thick = 0;
	};
	

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
		static color_t msgspk_color;// �b�҂̕����F
		static int msgtxt_left;		// �\���e�L�X�g�̍��[�i���΍��W�j
		static int msgtxt_top;		// �\���e�L�X�g�̏�[�i���΍��W�j
		static vector<Font> fontList;		// �t�H���g���X�g
		static vector<color_t> colorList;	// �����F���X�g

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

		static void ApplyConfig(json& js);

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
