#ifndef CSTAGE_MANAGER_H
#define CSTAGE_MANAGER_H

#include "..\MainStage\CMainStage.h"
#include "..\GhostSpeakStage\CGhostSpeakStage.h"	
#include "..\..\..\UI\Fade\StageFade\CStageFade.h"
#include "..\..\Scene\Tutorial\CTutorial.h"

/**************************************************
*		ステージ管理クラス.
********/
class CStageManager
{
public:
	CStageManager();
	~CStageManager();
	//===================列挙体========================//.
	//ステージ種類.
	enum class enStageType {
		GhostSpeakStage,			//お化けと会話するステージ.
		MainStage,					//メインステージ.

		Tutorial,					//チュートリアル.
		NormalStageMax = Tutorial,	//最大数.

		Start = GhostSpeakStage,	//初め.
	};

	//=====================定数=========================//.
	const unsigned int	FINISH_NEXT_ENDING	= (1 << 0);		//次がタイトルでの終了.
	const unsigned int	FINISH_NEXT_GAME	= (1 << 1);		//次がゲームでの終了.
	const int			NORMAL_STAGE_NUM	= 0;			//通常ステージ番号.

	//====================関数=========================//.
	void Init();																													//初期化処理関数.
	void UpDate();																													//更新処理関数.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos);		//描画処理関数.
	void Release();																													//解放処理関数.

	//==============情報獲得処理関数===================//.
	unsigned int GetFinishFlag() const { return m_FinishFlag; }

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
	bool										m_bOldTutorialFlag;		//チュートリアルフラグ.
};

#endif	//#ifndef CSTAGE_MANAGER_H.