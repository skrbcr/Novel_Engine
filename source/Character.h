#pragma once
#include <vector>
#include <string>
#include "Global.h"
#include "Image.h"

using std::vector;
using std::string_view;

namespace Game {
	struct CharaImg {
		//int gh_body = 0;		// body �O���t�B�b�N�n���h��
		//int gh_face = 0;		// face �O���t�B�b�N�n���h��
		Image img_body;			// �y��摜
		Image img_face;			// ��悹�摜
		string strPos = "";		// �z�u�R�}���h
		int x = 0;				// �摜x���W
		int y = 0;				// �摜y���W
	};

	class Character
	{
	private:
		vector<CharaImg> vchara = vector<CharaImg>(0);		// �L�����N�^�[�摜�f�[�^�z��

	public:
		Character() {

		}

		Character(size_t nSizeVchara) {
			vchara = vector<CharaImg>(nSizeVchara);
		}

		~Character() {

		}

		/// <summary>
		/// �摜���z��ɒǉ�
		/// </summary>
		/// <param name="index">�v�f�ԍ�</param>
		/// <param name="strPos">�ʒu�R�}���h</param>
		/// <param name="x">�摜���� x���W</param>
		/// <param name="y">�摜���� ���W</param>
		void SetCharaPos(size_t index, string_view strPos, int x, int y);

		/// <summary>
		/// body �摜��ݒ�
		/// </summary>
		/// <param name="strFile"></param>
		/// <param name="strPos"></param>
		void SetBody(string_view strFile, string_view strPos);

		/// <summary>
		/// face �摜��ݒ�
		/// </summary>
		/// <param name="strFile"></param>
		/// <param name="strPos"></param>
		void SetFace(string_view strFile, string_view strPos);

		/// <summary>
		/// body �摜���폜
		/// </summary>
		/// <param name="strPos">�z�u�R�}���h</param>
		void DeleteBody(string_view strPos);

		/// <summary>
		/// face �摜���폜
		/// </summary>
		/// <param name="strPos">�z�u�R�}���h</param>
		void DeleteFace(string_view strPos);

		/// <summary>
		/// ���C���֐�
		/// </summary>
		void Main();
	};
}

