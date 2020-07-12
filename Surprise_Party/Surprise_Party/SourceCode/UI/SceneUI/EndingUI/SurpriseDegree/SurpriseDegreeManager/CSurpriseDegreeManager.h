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

	//====================情報取得処理関数======================//.
	bool GetAllDispFlag() const { return m_bAllDispFlag; }

private:
	//==========================関数============================//.
	void Init();		//初期化処理関数.

	//==========================変数============================//.
	std::vector<std::unique_ptr<CSurpriseDegreeBase>>	m_pCSurpriseDegreeBase;	//驚かし度UIクラス.
	bool												m_bAllDispFlag;			//全てを表示したフラグ.
	int													m_UpdateUINum;			//更新しているUI番号.
};

#endif	//#ifndef CSURPRISE_DEGREE_MANAGER_H.