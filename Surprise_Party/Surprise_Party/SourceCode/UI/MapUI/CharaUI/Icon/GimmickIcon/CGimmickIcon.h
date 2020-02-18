#ifndef CGIMMICK_ICON_H
#define CGIMMICK_ICON_H

#include "..\CIcon.h"

/******************************************
*		�M�~�b�N�A�C�R���N���X.
*********/
class CGimmickIcon
	: public CIcon
{
public:
	CGimmickIcon();
	CGimmickIcon(int GimmickNum);
	~CGimmickIcon();

	//=========================�񋓑�=============================//.
	//�M�~�b�N�̎��.
	enum class enGimmickType {
		DispGhost = 0,	//�������������.
		SwitchObject,	//�X�C�b�`.
	};

	//==========================�֐�==============================//.
	void UpDate();		//�X�V�����֐�.

private:
	//==========================�֐�==============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//==========================�ϐ�==============================//.
	int	m_GimmickType;	//�M�~�b�N�^�C�v.

};

#endif	//#ifndef CGIMMICK_ICON_H.