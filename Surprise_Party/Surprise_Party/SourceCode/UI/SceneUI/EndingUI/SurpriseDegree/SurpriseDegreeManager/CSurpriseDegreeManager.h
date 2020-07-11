#ifndef CSURPRISE_DEGREE_MANAGER_H
#define CSURPRISE_DEGREE_MANAGER_H

#include "..\SurpriseDegreeBase\CSurpriseDegreeBase.h"

/*********************************************
*		驚かし度の管理クラス.
********************/
class CSurpriseDegreeManager
{
public:
	CSurpriseDegreeManager();
	~CSurpriseDegreeManager();

	//==========================関数============================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//==========================関数============================//.
	void Init();		//初期化処理関数.

	//==========================変数============================//.
	

};

#endif	//#ifndef CSURPRISE_DEGREE_MANAGER_H.