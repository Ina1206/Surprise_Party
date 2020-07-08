#ifndef CMAINSTAGE_WORKGHOST_MANAGER_H
#define CMAINSTAGE_WORKGHOST_MANAGER_H

#include "..\MainStageDispGhost\CMainStageDispGhost.h"
#include "..\MainStageSwitchGhost\CMainStageSwitchGhost.h"
#include <tuple>

/*************************************************
*		メインステージの働くお化け管理クラス.
*******************/
class CMainStageWorkGhostManager
{
public:
	CMainStageWorkGhostManager();
	~CMainStageWorkGhostManager();

	//====================定数=========================//.
	const unsigned int OBJ_DOWN_FLAG		= (1 << 0);	//オブジェクトを下げるフラグ.
	const unsigned int OBJ_UP_FLAG			= (1 << 1);	//オブジェクトを上げるフラグ.

	const unsigned int TUTORIAL_STAGE_FLAG	= (1 << 0);	//チュートリアルステージフラグ.
	const unsigned int EXPLAINING_FLAG		= (1 << 1);	//説明しているフラグ.
	const unsigned int GHOST_DECIDE_FLAG	= (1 << 2);	//お化けを決めるフラグ.
	const unsigned int SELECT_WAIT_FLAG		= (1 << 3);	//選択を待機するフラグ.

	//=======================関数======================//.
	void Init(const int& StageType, const int& StageNum, const float& PosWidth);																										//初期化処理関数.
	void Update();																										//更新処理関数.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& Light, const D3DXVECTOR3& vCameraPos);	//描画処理関数.
	void RenderIcon();																									//アイコン描画処理関数.
	void RenderSelectUI();																								//選択UI描画処理関数.
	bool DecisionSelectRest();																							//選択お化けの休憩判定処理関数.
	bool DecisionSelectSurprise();																						//選択お化けの驚かす判定処理関数.
	bool SelectGhost();																									//お化け選択処理関数.

	//=================情報置換処理関数================//.
	//ギミックの座標.
	void SetGimmickPos(const std::vector<D3DXVECTOR3>& vPos) { m_vGimmickPos = vPos; }
	//ステージの距離最大値.
	void SetStageDisntaceMax(const float& fDistance) { m_fStageDistanceMax = fDistance; }
	//人の座標.
	void SetPeoplePos(const std::vector<D3DXVECTOR3>& vPos) { m_vPeoplePos = vPos; }
	//お化け選択フラグ.
	void SetSelectFlag(const bool& bFlag) { m_pCWorkGhost[m_SelectNum]->SetSelectFlag(bFlag); }
	//お化け選択中止フラグ.
	void SetSelectStop() { m_pCWorkGhost[m_SelectNum]->SetSelectStop(); }
	//ギミック変更フラグ.
	void SetChangeGimmickSelect(const bool& bFlag) { m_pCWorkGhost[m_SelectNum]->SetChangeGimmickSelect(bFlag); }
	//目的ギミック座標.
	void SetObjectiveGimmickPos(const D3DXVECTOR3& vPos) { m_pCWorkGhost[m_SelectNum]->SetObjectiveGimmickPos(vPos); }
	//チュートリアルフラグ立てる.
	void SetTutorialFlag(const unsigned int& flag) { m_TutorialFlag |= flag; }
	//チュートリアルフラグを降ろす.
	void UnloadTutorialFlag(const unsigned int& flag) { m_TutorialFlag &= ~flag; }
	//使用しているギミック番号.
	void SetUseGimmickNum(const int& ghostNum, const int& gimmickNum) { m_pCWorkGhost[ghostNum]->SetUseGimmickNum(gimmickNum); }
	//選択しているお化けの使用しているギミック番号.
	void SetUseGimmickNumToSelectGhost(const int& gimmickNum) { m_pCWorkGhost[m_SelectNum]->SetUseGimmickNum(gimmickNum); }
	//ポーズフラグ.
	void SetPauseFlag(const bool& bFlag) { m_bPauseFlag = bFlag; }

	//=================情報取得処理関数================//.
	//近くにいる人の番号.
	std::vector<int> GetNearPeopleNum(const int& ghostNum) const { return m_pCWorkGhost[ghostNum]->GetNearHumanNum(); }
	//働くお化けの総合数.
	unsigned int GetAllGhostNum() const { return m_pCWorkGhost.size(); }
	//働くお化け全員の座標.
	std::vector<D3DXVECTOR3> GetAllGhostPos() const { return m_vWorkGhostPos; }
	//選択しているお化けの座標.
	D3DXVECTOR3 GetSelectGhostPos() const { return m_vWorkGhostPos[m_SelectNum]; }
	//オブジェクトの上げ下げフラグ.
	unsigned int GetUpDownFlag(const int& ghostNum) { return m_UpDownFlag[ghostNum]; }
	//チュートリアル時にコメントを増やすフラグ.
	bool GetTutorialAddCommentFlag(const int& ghostNum) const { return m_pCWorkGhost[ghostNum]->GetTutorialAddCommentFlag(); }
	//選択しているお化けの選択フラグ.
	bool GetSelectGhostFlag() const { return m_pCWorkGhost[m_SelectNum]->GetSelectFlag(); }
	//選択しているギミックを変更フラグ.
	bool GetChangeGimmickSelectFlag() const { return m_pCWorkGhost[m_SelectNum]->GetChangeGimmickSelect(); }
	//驚かすオブジェクトタイプ.
	CGameObject::enSurpriseObjectType GetSurpriseObjectType() const { return m_pCWorkGhost[m_SelectNum]->GetSurpriseObjectType(); }
	//使用ギミック番号.
	int GetUseGimmickNum(const int& ghostNum) const { return m_pCWorkGhost[ghostNum]->GetUseGimmickNum(); };
	//選択しているおばけの使用ギミック番号.
	int GetUseGimmickNumToSelectGhost() const { return m_pCWorkGhost[m_SelectNum]->GetUseGimmickNum(); }
	//選択しているお化けの休憩フラグ.
	bool GetRestSelectGhostFlag() const;

private:
	//=======================関数======================//.
	bool Tutorial(const int& GhostNum);			//チュートリアル処理関数.
	void ChangeElementNum(const int& GhostNum);	//要素数変更処理関数.
	void UpDownObuject(const int& GhostNum);	//オブジェクト上下処理.
	void Release();								//解放処理関数.

	//====================変数=========================//.
	std::vector<std::unique_ptr<CMainStageWorkGhostBase>>	m_pCWorkGhost;			//働くお化け.
	std::vector<D3DXVECTOR3>								m_vGimmickPos;			//ギミックの座標.
	std::vector<D3DXVECTOR3>								m_vPeoplePos;			//人の座標.
	std::vector<D3DXVECTOR3>								m_vWorkGhostPos;		//働くお化けの座標.
	
	std::vector<unsigned int>								m_UpDownFlag;			//上げ下げフラグ.
	unsigned int											m_TutorialFlag;			//チュートリアルフラグ.
	
	float													m_fStageDistanceMax;	//ステージの距離最大値.

	int														m_SelectNum;			//お化けの選択番号.

	bool													m_bPauseFlag;			//ポーズフラグ.
};

#endif	//#ifndef CMAINSTAGE_WORKGHOST_MANAGER_H.