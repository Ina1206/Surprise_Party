#ifndef CWORK_GHOST_BASE_H
#define CWORK_GHOST_BASE_H

#include "..\CGhostBase.h"
#include "..\..\..\..\UI\GameWorldUI\Act_Selection\CAct_Selection.h"
#include "..\..\..\..\UI\MapUI\CharaUI\Icon\GhostIcon\CGhostIcon.h"
#include "..\..\..\..\UI\GameWorldUI\GhostStrengthIcon\CGhostStrengthIcon.h"
#include "..\..\SpriteEffect\SurpriseEffect\CSurpriseEffect.h"

/*************************************
*		�������������N���X.
******/
class CWorkGhostBase
	: public CGhostBase
{
public:
	CWorkGhostBase();
	virtual ~CWorkGhostBase();


	//=============�񋓑�================//.
	//�������̎��.
	enum class enGhostType {
		DispGhost,			//����邨����.
		SwitchGhost,		//�X�C�b�`����������.

		Max,				//�ő�l.
		Start = DispGhost,	//�J�n�l.
	};


protected:

private:
};

#endif	//#ifndef CWORK_GHOST_BASE_H.