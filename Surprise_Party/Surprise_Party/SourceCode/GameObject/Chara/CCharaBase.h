#ifndef CCHARA_BASE_H
#define CCHARA_BASE_H

#include "..\CGameObject.h"
#include "..\..\Drawing\Resource\CResourceManager.h"
#include "..\..\FileLoad\FileResource\CFileResource.h"

/*************************************************
*		キャラクタ基底クラス.
******/
class CCharaBase
	: public CGameObject
{
public:
	CCharaBase();
	virtual ~CCharaBase();

	//====================列挙体=======================//.
	//キャラクタ種類.
	enum class enCharacterType {
		Ghost = 0,		//お化け.
		Human,			//人.

		Max,			//最大値.
		Start = Human,	//開始値.
	};

protected:
	//=====================変数========================//.
	CFileResource*		m_pCFileResource;	//ファイル読み込みクラス.

private:

};

#endif	//#ifndef CCHARA_BASE_H.