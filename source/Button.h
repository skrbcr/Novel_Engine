#pragma once
#include <vector>
#include "DxLib.h"
#include "Global.h"

using std::vector;
using color_t = unsigned int;

namespace Game {
	class Button
	{
	private:
		int index = 0;				// �I�𒆂̃{�^���ԍ�
		int num = 0;				// �{�^����
		int span_ver = 0;			// ���������̈ړ���
		int span_hol = 0;			// ���������̈ړ���
		int fcounter = 0;			// �t���[���J�E���^
		int alpha = 0;				// �A���t�@�l

		//bool onFreeze = false;

		vector<vector<int>> vvpos;

		color_t color = 0;			// �{�^���F


	public:
		Button(int num = 0) {
			vvpos = vector<vector<int>>(num, vector<int>(4));
			index = 0;
			this->num = num;
			span_ver = 0;
			span_hol = 0;
			fcounter = 0;
			alpha = 0;
		}

		/// <summary>
		/// �{�^���O���[�v��ݒ�
		/// </summary>
		/// <param name="span_ver">�㉺�L�[�ł̐��������ړ���</param>
		/// <param name="span_hol">���E�L�[�ł̐��������ړ���</param>
		/// <param name="color">�{�^���̐F</param>
		void SetGroup(int span_ver, int span_hol, color_t color = 0xDDDDDD);

		/// <summary>
		/// �{�^����ݒ�
		/// </summary>
		/// <param name="index">�{�^���ԍ�</param>
		/// <param name="x">����x���W</param>
		/// <param name="y">����y���W</param>
		/// <param name="width">�{�^����</param>
		/// <param name="height">�{�^������</param>
		void SetButton(int index, int x, int y, int width, int height);

		/// <summary>
		/// �{�^����ǉ��i�Ō���ɒǉ��j
		/// </summary>
		/// <param name="x">����x���W</param>
		/// <param name="y">����y���W</param>
		/// <param name="width">�{�^����</param>
		/// <param name="height">�{�^������</param>
		void AddButton(int x, int y, int width, int height);

		/// <summary>
		/// ���C�������E�`��
		/// <param name="freeze">�t���[�Y�t���O</param>
		/// </summary>
		int Main(bool freeze);

		void SetSelection(int index);

		int GetSelection() {
			return index;
		}

	private:
		void Draw();
	};
}
