#ifndef CTITLE_STRING_UI_H
#define CTITLE_STRING_UI_H

#include "..\..\..\CUI.h"

/*********************************************
*		�^�C�g������UI�N���X.
*******************/
class CTitleStringUI
	: public CUI
{
public:
	CTitleStringUI();
	~CTitleStringUI();

	//====================�֐�==========================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//====================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//====================�ϐ�==========================//.

};

#endif	//#ifndef CTITLE_STRING_UI_H.