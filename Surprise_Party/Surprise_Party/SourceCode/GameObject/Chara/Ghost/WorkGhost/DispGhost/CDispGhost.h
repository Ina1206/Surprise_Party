#ifndef CDISP_GHOST_H
#define CDISP_GHOST_H

#include "..\CWorkGhostBase.h"

class CDispGhost
	: public CWorkGhostBase
{
public:
	CDispGhost();
	~CDispGhost();

	//===============定数===================//.
	const unsigned int	APPEAR_FLAG					= (1 << 0);	//現れるフラグ.
	const unsigned int  APPEAR_SURPRISE_FLAG		= (1 << 1);	//現れて驚かすフラグ.
	const unsigned int	RETURN_FLAG					= (1 << 2);	//戻るフラグ.
	const float			WAIT_SURPRISE_ANIM_SPEED	= 0.0f;		//驚かし待ちのアニメーション速度.
	const float			SURPRISE_ANIM_SPEED			= 0.008f;	//驚かすときのアニメーション速度.
	const float			WAIT_ANIM_START_POS			= 0.95f;	//待機時のアニメーション座標.
	const double		RETURN_ANIM_TIME			= 1.1;		//戻るアニメーション時間.
	const double		WAIT_ANIM_TIME				= 1.5;		//待機アニメーション時間.
	const float			APPEAR_SPEED				= 0.15f;	//現れる速度.
	const float			APPEAR_POS_MAX				= -0.3f;	//現れる場所の最大値.
	const float			RETURN_SPEED				= 0.2f;		//戻る速度.
	const float			RETURN_POS_MAX				= 3.5f;		//戻る場所の最大値.
	const float			GHOST_POS_Z					= 3.5f;		//お化けのｚ軸座標.
	const float			OBJECT_DOWN_POS				= 3.4f;		//オブジェクト落とすお化けの座標.
	const float			HIGHT_MIN					= 0.0f;		//高さの最小値.


	//===============関数===================//.
	void UpDate();									//更新処理関数.
	void Render();									//描画処理関数.

private:
	//===============関数===================//.
	void Init();									//初期化処理関数.
	void Release();									//解放処理関数.
	void SurpriseAct();								//驚かす行動処理関数.
	void ChangeObjectUpDown();						//上下移動変更処理関数.
	void ReturnMove();								//戻る移動処理関数.

	//===============変数===================//.
	CDX9SkinMesh*				m_pCSkinMesh;		//スキンメッシュクラス.
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;		//アニメーションコントローラ.
	float						m_fAnimSpeed;		//アニメーション速度.
	unsigned int				m_SurpriseActFlag;	//驚かす行動フラグ.
	double						m_dAnimTime;		//アニメーション時間.
};

#endif	//#ifndef CDISP_GHOST_H.