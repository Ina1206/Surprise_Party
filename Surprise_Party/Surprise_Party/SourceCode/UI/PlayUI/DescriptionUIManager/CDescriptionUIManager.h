#ifndef CDESCRIPTION_UI_MANAGER_H
#define CDESCRIPTION_UI_MANAGER_H

#include "..\Arrow\CArrow.h"
#include "..\TutorialBlackScreen\CTutorialBlackScreen.h"

/*****************************************
*		説明UI管理クラス.
**************/
class CDescriptionUIManager
{
public:
	CDescriptionUIManager();
	~CDescriptionUIManager();

	//======================関数=========================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

	//================情報置換処理関数===================//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }

private:
	//======================関数=========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//======================変数=========================//.
	std::unique_ptr<CArrow>						m_pCArrow;					//矢印クラス.
	std::unique_ptr<CTutorialBlackScreen>		m_pCTutorialBlackScreen;	//チュートリアル黒画面.
	D3DXVECTOR3									m_vCenterPos;				//中心座標.
};

#endif	//#ifndef CDESCRIPTION_UI_MANAGER_H.