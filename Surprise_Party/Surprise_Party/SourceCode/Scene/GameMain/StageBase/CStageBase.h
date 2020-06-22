#ifndef CSTAGE_BASE_H
#define CSTAGE_BASE_H

#include "..\..\..\Global.h"
#include "..\..\..\Drawing\Resource\CResourceManager.h"
#include "..\..\Camera\CCameraBase.h"

/*****************************************
*		ステージ基底クラス.
********/
class CStageBase
{
public:
	CStageBase();
	virtual ~CStageBase();

	//===================列挙体========================//.
	//前回のステージのエンディングタイプ.
	enum class enBeforeStageEndigneType {
		Great = 0,	//素晴らしい.
		Good,		//良い.
		Bad,		//悪い.
		Nothing,	//なし.
	};
	//ステージ種類.
	enum class enStageType {
		GhostSpeakStage = 0,		//お化けと会話するステージ.
		MainStage,					//メインステージ.

		Tutorial,					//チュートリアル.
		NormalStageMax = Tutorial,	//最大数.

		Start = GhostSpeakStage,	//初め.
	};

	//=====================定数=========================//.
	const unsigned int	FINISH_NEXT_ENDING	= (1 << 0);		//次がタイトルでの終了.
	const unsigned int	FINISH_NEXT_TITLE	= (1 << 1);		//次がゲームでの終了.

	const unsigned int TUTORIAL_START		= (1 << 0);		//チュートリアル開始.
	const unsigned int TUTORIAL_FINISH		= (1 << 1);		//チュートリアル終了


	//=====================関数=========================//.
	void RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj);	//描画初期設定処理関数.
	void DebugStageChange();													//デバッグ用ステージ変更処理関数.

	virtual void UpDate(const bool& ControlFlag)	= 0;	//更新処理関数.
	virtual void Render()							= 0;	//描画処理関数.

	//===============情報取得処理関数===================//.
	//ステージ変更フラグ.
	bool GetChangeStageFlag() const { return m_bChangeStageFlag; }
	//前回のステージエンディングタイプ.
	enBeforeStageEndigneType GetBeforeStageEndingType() const { return m_enBeforeStageEndingType; }
	//終了フラグ.
	unsigned int GetFinishFlag() const { return m_FinishFlag; }
	//チュートリアルフラグ.
	unsigned int GetTutorialFlag() const { return m_TutorialFlag; }

	//===============情報置換処理関数====================//.
	//チュートリアルフラグ.
	void SetTutorialFlag(const unsigned int& flag) { m_TutorialFlag = flag; }
	//ポーズフラグ.
	void SetPauseFlag(const bool& bflag) { m_bPauseFlag = bflag; }

protected:
	//=====================関数=========================//.
	virtual void Init() = 0;		//初期化処理関数.
	virtual void Release() = 0;		//解放処理関数.
	virtual void Control() = 0;		//操作処理関数.

	//=====================変数=========================//.
	D3DXMATRIX						m_mView;					//ビュー行列.
	D3DXMATRIX						m_mProj;					//プロジェクション行列.

	bool							m_bChangeStageFlag;			//ステージ変更フラグ.
	int								m_StageNum;					//ステージ番号.

	enBeforeStageEndigneType		m_enBeforeStageEndingType;	//前回のステージのエンディングタイプ.
	unsigned int					m_FinishFlag;				//終了フラグ.
	unsigned int					m_TutorialFlag;				//チュートリアルフラグ.

	std::unique_ptr<CCameraBase>	m_pCCamera;					//カメラクラス.

	bool							m_bPauseFlag;				//ポーズフラグ.
};

#endif	//#ifndef CSTAGE_BASE_H.