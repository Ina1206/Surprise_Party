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

	//=============================定数======================================//.
	const float			WAIT_ANIM_START_POS = 0.95f;	//待機時のアニメーション座標.

	//=============列挙体================//.
	//お化けの種類.
	enum class enGhostType {
		DispGhost,			//現れるお化け.
		SwitchGhost,		//スイッチ押すお化け.

		Max,				//最大値.
		Start = DispGhost,	//開始値.
	};


protected:
	//==============================関数====================================//.
	void InitAnimation();							//アニメーション初期化処理関数.
	void RenderDispGhost(const D3DXVECTOR3& vPos);	//現れるお化け描画処理関数.
	void InitStaticMeshGhost();						//静的オブジェクトお化け初期化処理関数.
	void RenderSwitchGhost(const D3DXVECTOR3& vPos);//スイッチお化け描画処理関数.

	//==============================変数====================================//.
	CDX9SkinMesh*				m_pCSkinMesh;		//スキンメッシュクラス.
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;		//アニメーションコントローラ.
	CDX9Mesh*					m_pCMesh;			//メッシュ.

private:
};

#endif	//#ifndef CWORK_GHOST_BASE_H.