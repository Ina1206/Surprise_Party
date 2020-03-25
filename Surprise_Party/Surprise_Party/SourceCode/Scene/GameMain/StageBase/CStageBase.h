#ifndef CSTAGE_BASE_H
#define CSTAGE_BASE_H

#include "..\..\..\Global.h"
#include "..\..\..\Drawing\Resource\CResourceManager.h"

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

	//=====================定数=========================//.
	const unsigned int	FINISH_NEXT_ENDING	= (1 << 0);		//次がタイトルでの終了.
	const unsigned int	FINISH_NEXT_GAME	= (1 << 1);		//次がゲームでの終了.


	//=====================関数=========================//.
	void RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos);	//描画初期設定処理関数.
	void DebugStageChange();																												//デバッグ用ステージ変更処理関数.

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
	bool GetTutorialFlag() const { return m_bTutorialFlag; }
protected:
	//=====================関数=========================//.
	virtual void Init() = 0;		//初期化処理関数.
	virtual void Release() = 0;		//解放処理関数.
	virtual void Control() = 0;		//操作処理関数.

	//=====================変数=========================//.
	D3DXMATRIX					m_mView;					//ビュー行列.
	D3DXMATRIX					m_mProj;					//プロジェクション行列.
	LIGHT						m_stLight;					//ライト情報.
	//D3DXVECTOR3					m_vCameraPos;				//カメラ座標.
	CAMERA						m_Camera;					//カメラ構造体.

	bool						m_bChangeStageFlag;			//ステージ変更フラグ.
	int							m_StageNum;					//ステージ番号.

	enBeforeStageEndigneType	m_enBeforeStageEndingType;	//前回のステージのエンディングタイプ.
	unsigned int				m_FinishFlag;				//終了フラグ.
	bool						m_bTutorialFlag;			//チュートリアルフラグ.
};

#endif	//#ifndef CSTAGE_BASE_H.