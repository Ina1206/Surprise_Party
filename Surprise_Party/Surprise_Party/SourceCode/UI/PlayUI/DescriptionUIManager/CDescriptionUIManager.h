#ifndef CDESCRIPTION_UI_MANAGER_H
#define CDESCRIPTION_UI_MANAGER_H

#include "..\Arrow\CArrow.h"
#include "..\TutorialBlackScreen\CTutorialBlackScreen.h"
#include "..\..\SpeakUI\SpeakTutorial\CSpeakTutorial.h"

/*****************************************
*		説明UI管理クラス.
**************/
class CDescriptionUIManager
{
public:
	CDescriptionUIManager();
	~CDescriptionUIManager();

	//======================定数=========================//.
	const D3DXVECTOR3	GAGE_ARROW_POS	= D3DXVECTOR3(500.0f, -30.0f, 0.0f);//ゲージの矢印座標.
	const D3DXVECTOR3	CLOSE_ARROW_POS = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);	//閉じる矢印座標.

	//======================関数=========================//.
	void Update();															//更新処理関数.
	void Render();															//描画処理関数.

	//================情報置換処理関数===================//.
	//中央座標.
	void SetCenterPos(const D3DXVECTOR3& vGagePos, const D3DXVECTOR3& vTimePos);
	//コメントを進める処理.
	void SetAdvanceComment() { m_pCSpeakTutorial->AdvanceOnceComment(); }
	//選択移動カウント追加処理.
	void SetAddSelectMoveCount() { m_pCSpeakTutorial->AddSelectMoveCount(); }
	//コメント追加フラグ.
	void SetAdvanceCommentFlag(const bool& flag) { m_pCSpeakTutorial->SetAdvanceCommentFlag(flag); }

	//================情報取得処理関数===================//.
	//コメント追加フラグ.
	bool GetAdvanceCommentFlag() const { return m_pCSpeakTutorial->GetAdvanceCommentFlag(); }
	//チュートリアルフラグ.
	unsigned int GetTutorialFlag() const { return m_pCSpeakTutorial->GetTutorialFlag(); }
	//開始直前フラグ.
	unsigned int GetStartLatestFlag() const { return m_pCSpeakTutorial->GetStartLatestFlag(); }
	//説明終了フラグ.
	bool GetDescriptionEndFlag() const { return m_pCSpeakTutorial->GetDescriptionEndFlag(); }
	//全てのフォント表示フラグ.
	bool GetAppearancedAllFont() const { return m_pCSpeakTutorial->GetAppearancedAllFont(); }

private:
	//======================関数=========================//.
	void Init();															//初期化処理関数.
	void Release();															//解放処理関数.
	D3DXVECTOR3 SettingArrowPos();											//矢印座標設定処理関数.
	unsigned int SettingArrowFlag();										//矢印フラグ設定処理関数.
	void JudgeDescription();												//説明判定処理関数.

	//======================変数=========================//.
	std::unique_ptr<CArrow>						m_pCArrow;					//矢印クラス.
	std::unique_ptr<CTutorialBlackScreen>		m_pCTutorialBlackScreen;	//チュートリアル黒画面.
	std::unique_ptr<CSpeakTutorial>				m_pCSpeakTutorial;			//チュートリアル会話.
	D3DXVECTOR3									m_vCenterPos;				//中心座標.
	bool										m_bRenderArrowFlag;			//両方の矢印の描画フラグ.
};

#endif	//#ifndef CDESCRIPTION_UI_MANAGER_H.