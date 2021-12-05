#pragma once
#include <vector>
#include <string>
#include "Global.h"

using std::vector;
using std::string_view;

namespace Game {
	class Character
	{
	private:
		int gh_body = 0;		// body �O���t�B�b�N�n���h��
		int gh_face = 0;		// face �O���t�B�b�N�n���h��

	public:
		static vector<vector<int>> vpos;		// �摜�z�u���W

	public:
		Character() {

		}

		~Character() {

		}

		/// <summary>
		/// body �摜��ݒ�
		/// </summary>
		/// <param name="gh"></param>
		/// <param name="strPos"></param>
		void SetBody(int gh, string_view strPos);

	};
}

