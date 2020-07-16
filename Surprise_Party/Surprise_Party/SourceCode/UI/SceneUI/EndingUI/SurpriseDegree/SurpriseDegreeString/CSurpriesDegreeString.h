#ifndef CSURPRISE_RAGREE_STRING_H
#define CSURPRISE_RAGREE_STRING_H

#include "..\SurpriseDegreeBase\CSurpriseDegreeBase.h"

/**********************************************
*		驚かし度文章クラス.
*******************/
class CSurpriseDegreeString
	: public CSurpriseDegreeBase
{
public:
	
	CSurpriseDegreeString();
	~CSurpriseDegreeString();

	//========================定数================================//.
	const D3DXVECTOR3	INIT_POS	= D3DXVECTOR3(0.0f, 430.0f, 0.0f);	//初期座標.
	const D3DXVECTOR3	FINISH_POS	= D3DXVECTOR3(0.0f, 560.0f, 0.0f);	//最終座標.
	const float			MOVE_SPEED	= 1.5f;								//移動速度.

	//========================関数================================//.
	void Update();			//更新処理関数.

private:
	//========================関数================================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.
	void Move();			//移動処理関数.
	void Transparent();		//透過処理関数.
	
	//========================変数================================//.
	bool m_bPlaySoundFlag;	//音再生フラグ.

};

#endif	//#ifndef CSURPRISE_RAGREE_STRING_H.