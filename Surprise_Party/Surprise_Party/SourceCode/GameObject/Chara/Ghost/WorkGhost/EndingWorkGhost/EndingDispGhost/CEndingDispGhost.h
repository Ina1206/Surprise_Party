#ifndef CENDING_DISP_GHOST_H
#define CENDING_DISP_GHOST_H

#include "..\CEndingWorkGhostBase.h"

/******************************************
*		エンディングの現れるお化けクラス.
**************/
class CEndingDispGhost
	: public CEndingWorkGhostBase
{
public:
	CEndingDispGhost();
	~CEndingDispGhost();

	//======================関数=======================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//======================関数=======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.



};

#endif	//#ifndef CENDING_DISP_GHOST_H.