#ifndef CGIRL_ICON_H
#define CGIRL_ICON_H

#include "..\CPeopleIcon.h"

/***************************************
*	���̎q�̃A�C�R���N���X.
*******/
class CGirlIcon
	: public CPeopleIcon
{
public:
	CGirlIcon();
	~CGirlIcon();

private:
	//===================�֐�=====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
};

#endif //#ifndef CGIRL_ICON_H.