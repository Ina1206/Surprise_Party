#ifndef CWORK_GHOST_BASE_H
#define CWORK_GHOST_BASE_H

#include "..\CGhostBase.h"
#include "..\..\..\..\UI\GameWorldUI\Act_Selection\CAct_Selection.h"
#include "..\..\..\..\UI\MapUI\CharaUI\Icon\GhostIcon\CGhostIcon.h"
#include "..\..\..\..\UI\GameWorldUI\GhostStrengthIcon\CGhostStrengthIcon.h"
#include "..\..\SpriteEffect\SurpriseEffect\CSurpriseEffect.h"

/*************************************
*		働くお化け基底クラス.
******/
class CWorkGhostBase
	: public CGhostBase
{
public:
	CWorkGhostBase();
	virtual ~CWorkGhostBase();


	//=============列挙体================//.
	//お化けの種類.
	enum class enGhostType {
		DispGhost,			//現れるお化け.
		SwitchGhost,		//スイッチ押すお化け.

		Max,				//最大値.
		Start = DispGhost,	//開始値.
	};


protected:

private:
};

#endif	//#ifndef CWORK_GHOST_BASE_H.