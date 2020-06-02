#ifndef CENDING_STAGE_BASE_H
#define CENDING_STAGE_BASE_H

#include "..\..\GameObject\Chara\Ghost\BigGhost\CBigGhost.h"
#include "..\..\GameObject\Object\StaticObject\Floor\CFloor.h"
#include "..\..\GameObject\Object\StaticObject\Light\BackstageLight\CBackstageLight.h"

/*******************************************
*		エンディングステージ基底クラス.
*****************/
class CEndingStageBase
{
public:
	CEndingStageBase();
	virtual ~CEndingStageBase();

	//========================関数=============================//.
	virtual void Update() = 0;	//更新処理関数.
	virtual void Render() = 0;	//描画処理関数.

protected:
	//========================関数=============================//.
	virtual void Init() = 0;	//初期化処理関数.
	virtual void Release() = 0;	//解放処理関数.

	//========================変数=============================//.
	std::unique_ptr<CBigGhost>			m_pCBigGhost;		//ビッグゴーストクラス.
	std::unique_ptr<CFloor>				m_pCFloor;			//床クラス.
	std::unique_ptr<CBackstageLight>	m_pCBackstageLight;	//舞台裏ライトクラス.

private:
	//========================関数=============================//.
	void InitCommonValue();		//共通値の初期化処理関数.


};

#endif	//#ifndef CENDING_STAGE_BASE_H.