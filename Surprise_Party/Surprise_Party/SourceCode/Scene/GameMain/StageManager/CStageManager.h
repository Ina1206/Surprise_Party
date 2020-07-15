#ifndef CSTAGE_MANAGER_H
#define CSTAGE_MANAGER_H

#include "..\MainStage\CMainStage.h"
#include "..\GhostSpeakStage\CGhostSpeakStage.h"	
#include "..\..\..\UI\Fade\StageFade\CStageFade.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/**************************************************
*		ステージ管理クラス.
********/
class CStageManager
{
public:
	CStageManager();
	~CStageManager();

	//=====================定数=========================//.
	const unsigned int	FINISH_NEXT_ENDING	= (1 << 0);		//終了しエンディングへ移動.
	const unsigned int	FINISH_NEXT_TITLE	= (1 << 1);		//終了しタイトルへ移動.
	const int			NORMAL_STAGE_NUM	= 0;			//通常ステージ番号.

	//====================関数=========================//.
	void Init();													//初期化処理関数.
	void UpDate();													//更新処理関数.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj);	//描画処理関数.
	void Release();													//解放処理関数.

	//==============情報獲得処理関数===================//.
	unsigned int GetFinishFlag() const { return m_FinishFlag; }
	int	GetAverageEvaluation() const { return m_AllEndingType / 3; }

	//==============情報置換処理関数===================//.
	void SetPauseFlag(const bool& bFlag) { m_bPauseFlag = bFlag; }

private:
	//====================関数=========================//.
	void ChangeStage();								//ステージ変更処理関数.

	//====================変数=========================//.
	std::vector<std::unique_ptr<CStageBase>>	m_pCStageBase;			//ステージクラス.
	int											m_StageType;			//ステージ種類.
	int											m_StageNum;				//ステージ番号.
	CMainStage::enBeforeStageEndigneType		m_enBeforeEndingType;	//前回のステージエンディングタイプ.
	std::unique_ptr<CStageFade>					m_pCStageFade;			//ステージフェード.
	unsigned int								m_FinishFlag;			//終了フラグ.
	unsigned int								m_bOldTutorialFlag;		//チュートリアルフラグ.
	int											m_AllEndingType;		//全てのエンディングタイプの合計.
	bool										m_bPauseFlag;			//ポーズフラグ.
	CPlaySoundManager*							m_pCPlaySoundManager;	//曲再生管理クラス.
};

#endif	//#ifndef CSTAGE_MANAGER_H.