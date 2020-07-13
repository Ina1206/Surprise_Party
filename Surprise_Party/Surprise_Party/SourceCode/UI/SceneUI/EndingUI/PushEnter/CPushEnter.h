#ifndef CPUSH_ENTER_H
#define CPUSH_ENTER_H

#include "..\..\..\CUI.h"

/********************************************
*		PushEnterクラス.
***********************/
class CPushEnter
	: public CUI
{
public:
	CPushEnter();
	~CPushEnter();

	//=============================定数====================================//.
	const D3DXVECTOR3	POS						= D3DXVECTOR3(800.0f, 600.0f, 0.0f);//位置.
	const int			CHANGE_ALPHA_ADD_DIRECT = -1;								//透過値追加方向の変更数値.
	const float			TRANSPARENT_SPEED		= 0.05f;							//透過速度.
	const float			ALPHA_MIN				= 0.0f;								//透過値最小値.
	const float			SCALE_MAX				= 2.0f;								//大きさ最大値.

	//=============================関数====================================//.
	void Update();	//更新処理関数.
	void Render();	//描画処理関数.
	
private:
	//=============================関数====================================//.
	void Init();	//初期化処理関数.
	void Release();	//解放処理関数.

	//=============================変数====================================//.
	CSpriteUI*		m_pCSpriteUI;		//スプライトUIクラス.
	int				m_AlphaAddDirect;	//透過値追加方向.

};

#endif	//#ifndef CPUSH_ENTER_H.