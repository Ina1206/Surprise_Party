#ifndef CGHOST_STRENGTH_ICON_H
#define CGHOST_STRENGTH_ICON_H

#include "..\CGameWorldUI.h"

/************************************************
*		�������̗̑̓A�C�R���N���X.
***************/
class CGhostStrengthIcon
	: public CGameWorldUI
{
public:
	CGhostStrengthIcon();
	~CGhostStrengthIcon();

	//=================�萔=================//.
	const D3DXVECTOR2	GREAT_STRENGTH		= D3DXVECTOR2(1.0f, 0.0f);			//�̗�(�D��)�A�C�R���ԍ�.
	const D3DXVECTOR2	GOOD_STRENGTH		= D3DXVECTOR2(4.0f, 1.0f);			//�̗�(��)�A�C�R���ԍ�.
	const D3DXVECTOR2	NORMAL_STRENGTH		= D3DXVECTOR2(1.0f, 3.0f);			//�̗�(����)�A�C�R���ԍ�.
	const D3DXVECTOR2	BAD_STRENGTH		= D3DXVECTOR2(0.0f, 1.0f);			//�̗�(��)�A�C�R���ԍ�.
	const D3DXVECTOR3	ICON_POS_ADJUST		= D3DXVECTOR3(1.5f, 5.5f, -1.0f);	//�A�C�R�����W������.
	const float			ALPHA_CHANGE_POS	= 0.5f;								//���ߒl�ύX���W.
	const float			WALL_BACK_ALPHA		= 0.3f;								//�ǂ̌��ɂ���Ƃ��̓��ߒl.
	const float			BEFORE_WALL_ALPHA	= 1.0f;								//�ǂ̑O�ɂ���Ƃ��̓��ߒl.

	//================�񋓑�================//.
	//�̗̓^�C�v.
	enum class enStrengthType {
		Bad = 0,	//��.
		Normal,		//����.
		Good,		//�ǂ�.
		Great,		//�D.
	};

	//=================�֐�=================//.
	void UpDate();	//�X�V�����֐�.

	//===========���u�������֐�===========//.
	//�x�e�t���O.
	void SetRestFlag(const bool& bflags) { m_bRestFalg = bflags; }
	//�̗̓A�C�R��.
	void SetStrengthIcon(const int& Strength) { m_StrengthIcon = Strength; }

private:
	//=================�֐�=================//.
	void Init();	//�����������֐�.
	void Release();	//��������֐�.

	//=================�ϐ�=================//.
	bool	m_bRestFalg;	//�x�e�t���O.
	int		m_StrengthIcon;	//�̗̓A�C�R��.
};

#endif	//#ifndef CGHOST_STRENGTH_ICON_H.