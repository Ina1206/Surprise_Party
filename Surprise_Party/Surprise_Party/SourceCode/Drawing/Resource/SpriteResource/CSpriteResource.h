#ifndef CSPRITE_RESOURCE_H
#define CSPRITE_RESOURCE_H

#include "..\..\Sprite\Sprite\CSprite.h"
#include "..\..\Sprite\SpriteUI\CSpriteUI.h"
#include "..\..\..\Global.h"
#include "..\CResourceBase.h"

/***********************************************
*		スプライト系クラス.
**/
template <class Sprite, class SpriteType>
class CSprite_Resource
	: public CResourceBase
{
public:
	CSprite_Resource();
	~CSprite_Resource();

	//===============関数==================//.
	HRESULT Init(int max);								//初期化処理関数.
	HRESULT Load(std::vector<std::string> vecFileName);	//読み込み処理関数.
	HRESULT ReleaseCalling();							//解放呼び出し処理関数.

	//==========情報獲得処理関数============//.
	Sprite* GetSprite(SpriteType enSprite);		//スプライト系クラスのアドレス.

	//==========情報置換処理関数============//.
	void	SetSpriteState(SPRITE_STATE* stSpriteState) { m_pSpriteState = stSpriteState; }
	
private:
	//===============関数=================//.
	HRESULT Create(SpriteType enSprite, const char* pfileName);	//作成処理関数.
	HRESULT Release(SpriteType enSprite);						//解放処理関数.
	HRESULT Check_SpriteRange(SpriteType enSprite);				//スプライトの範囲を確認処理関数.

	//===============変数=================//.
	Sprite**		m_ppSprite;			//スプライト系クラス.
	SPRITE_STATE*	m_pSpriteState;		//スプライト系のステータス構造体.

};

#endif	//#ifndef CSPRITE_RESOURCE_H.