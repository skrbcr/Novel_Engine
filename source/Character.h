#pragma once
#include <vector>
#include <string>
#include "Global.h"

using std::vector;
using std::string_view;

struct CharaImg
{
	int gh_body = 0;		// body �O���t�B�b�N�n���h��
	int gh_face = 0;		// face �O���t�B�b�N�n���h��
	string strPos = "";		// �z�u�R�}���h
	int x = 0;				// �摜x���W
	int y = 0;				// �摜y���W
};

namespace Game {
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
		/// <param name="gh"></param>
		/// <param name="strPos"></param>
		void SetBody(int gh, string_view strPos);

		/// <summary>
		/// face �摜��ݒ�
		/// </summary>
		/// <param name="gh"></param>
		/// <param name="strPos"></param>
		void SetFace(int gh, string_view strPos);

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

