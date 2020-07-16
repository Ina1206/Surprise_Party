#ifndef CBEFORE_RESULT_STAGE_H
#define CBEFORE_RESULT_STAGE_H

#include "..\CEndingStageBase\CEndingStageBase.h"
#include "..\..\UI\SpeakUI\ReputationSNS\CReputationSNS.h"
#include "..\..\GameObject\Object\StaticObject\SmartPhone\CSmartPhone.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/********************************************
*		結果発表前のステージクラス.
******************/
class CBeforeResultStage
	: public CEndingStageBase
{
public:
	CBeforeResultStage();
	~CBeforeResultStage();

	//========================関数=========================//.
	void Update();				//更新処理関数.
	void Render();				//描画処理関数.

private:
	//========================関数=========================//.
	void Init();				//初期化処理関数.
	void Release();				//解放処理関数.
	void DecideString();		//文章決定処理関数.
	void RenderSmartPhone();	//スマートフォン描画処理関数.

	//========================変数=========================//.
	std::unique_ptr<CReputationSNS>	m_pCReputationSNS;		//SNS評判処理関数.
	std::unique_ptr<CSmartPhone>	m_pCSmartPhone;			//スマートフォンクラス.
	CPlaySoundManager*				m_pCPlaySoundManager;	//音再生管理クラス.
	bool							m_bPlaySE;				//SE再生フラグ.
};

#endif	//#ifndef CBEFORE_RESULT_STAGE_H.