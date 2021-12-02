#include "DxLib.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	/* �E�B���h�E�ݒ� */
	SetWindowText("");				// �E�B���h�E��
	SetAlwaysRunFlag(TRUE);						// ��A�N�e�B�u�������s
	//SetWindowIconID();							// �A�C�R���i.ico�t�@�C����icon.rc���K�v�B������icon.rc�Őݒ肵���C�ӂ̃A�C�R��ID�j
	//SetOutApplicationLogValidFlag(FALSE);		// ���O���o�͂��Ȃ�
	ChangeWindowMode(TRUE);						// �t���X�N���[���ɂ��Ȃ�
	SetGraphMode(1280, 720, 32);				// �E�B���h�E�T�C�Y�ƐF�r�b�g���̎w��
	SetWindowSizeExtendRate(1.0);				// ���ۂɕ\������E�B���h�E�T�C�Y�ɕύX

	/* ������ */
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);				// �_�u���o�b�t�@�̎g�p

	char key[256];								// �L�[���͔z��

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {
		
	}

	/* �I������ */
	DxLib_End();

	return 0;
}
