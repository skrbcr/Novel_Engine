#pragma once
#include <string>
//#include <string_view>
#include <vector>
#include "Global.h"
#include "Dialog.h"
#include "Button.h"

using std::string;
using std::vector;

namespace Game {
	class Choice
	{
	private:
		vector<string> strOptList;			// �I����������z��
		Button button = Button();
		int num = 0;				// �I������
		int count = 0;				// ���ݑI��ԍ�
		int width = 0;				// �I���{�b�N�X��

	public:

		Choice() {

		}

		~Choice() {

		}

		/// <summary>
		/// ���C���֐�
		/// </summary>
		/// <returns>-1:�ʏ� 0~:�{�^������</returns>
		int Main();

		/// <summary>
		/// �ݒ�
		/// </summary>
		/// <param name="strList">�I����������</param>
		void Set(vector<string>& strList);
	};
}

