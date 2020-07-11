#ifndef CSURPRISE_RAGREE_STRING_H
#define CSURPRISE_RAGREE_STRING_H

#include "..\SurpriseRegreeBase\CSurpriseRegreeBase.h"

/**********************************************
*		驚かし度文章クラス.
*******************/
class CSurpriseRegreeString
	: public CSurpriseRegreeBase
{
public:
	
	CSurpriseRegreeString();
	~CSurpriseRegreeString();

	//========================関数================================//.
	void Update();		//更新処理関数.

private:
	//========================関数================================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	
	//========================変数================================//.


};

#endif	//#ifndef CSURPRISE_RAGREE_STRING_H.