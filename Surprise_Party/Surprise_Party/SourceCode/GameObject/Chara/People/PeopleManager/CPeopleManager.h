#ifndef CPEOPLE_MANAGER_H
#define CPEOPLE_MANAGER_H

#include "..\..\FileLoad\FileResource\CFileResource.h"
#include "..\Boy\CBoy.h"
#include "..\Girl\CGirl.h"
#include "..\..\UI\MapUI\CharaUI\Icon\PeopleIcon\GirlIcon\CGirlIcon.h"
#include "..\..\\UI\MapUI\CharaUI\Icon\PeopleIcon\BoyIcon\CBoyIcon.h"

/***************************************
*		人々の管理クラス.
********/
class CPeopleManager
{
public:
	CPeopleManager();
	~CPeopleManager();

	//=================定数==================//.
	const D3DXVECTOR3	INIT_POS			= D3DXVECTOR3(-1.0f, 0.0f, -2.5f);		//最初の位置.
	const unsigned int	DISP_TIME			= 60;									//表示させる時間.
	const int			HUMAN_TYPE_MAX		= 2;									//人間種類最大数.

	//=================関数==================//.
	void Init(int FileNum, int max, float StageMax);	//初期化処理関数.
	void Update();										//更新処理関数.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos, const LIGHT& stLight);	//描画処理関数.
	
	//===========情報置換処理関数============//.
	//ステージ距離最大値.
	void SetStageDistanceMax(const float& fStageDistanceMax) { m_fStageDistanceMax = fStageDistanceMax; }
	//驚いたフラグ.
	void SetSurpriseFlag(const int& SurpriseHumanNum, const bool& bFlag) { m_bSurpriseFlag[SurpriseHumanNum] = bFlag; }
	//驚いている人番号.
	void SetNowHumanSurprise(const std::vector<int>& HumanNum);
	//チュートリアルフラグ.
	void SetTutorialFlag(const bool& bFlag) { m_pCPeopleBase[0]->SetTutorialFlag(bFlag); }
	//ポーズフラグ.
	void SetPauseFlag(const bool& bFlag) { m_bPauseFlag = bFlag; }
	//アイコン描画しないフラグ.
	void SetNotRenderIcon(const bool& bFlag) { m_bNotRenderIcon = bFlag; }

	//===========情報獲得処理関数============//.
	//人の座標取得.
	std::vector<D3DXVECTOR3> GetHumanPos() const { return m_vHumanPos; }
	//追加ポイント量.
	int GetAddSurprisePoint() const { return m_AddSurprisePoint; }

private:
	//=================関数==================//.
	void Release();		//解放処理関数.
	void HumanApp();	//人の表示処理関数.
	void HumanMove();	//人の移動処理関数.

	//=================変数==================//.
	CFileResource*								m_pCFileResource;	//ファイル読み込みクラス.

	std::vector<int>							m_HumanAppOrder;	//人を出す順番.
	std::vector<CPeopleBase*>					m_pCPeopleBase;		//人のクラス.
	std::vector<bool>							m_bDispFlag;		//表示フラグ.
	std::vector<D3DXVECTOR3>					m_vHumanPos;		//人の座標.
	float										m_fStageDistanceMax;//ステージ最大数.
	unsigned int								m_CreateHumanMax;	//作成最大数.
	std::vector<bool>							m_bSurpriseFlag;	//驚いたフラグ.

	unsigned int								m_DispCnt;			//表示カウント.
	unsigned int								m_AppHumanNum;		//現れる人間の番号.

	std::vector<int>							m_SurpriseHumanNum;	//驚いている人番号.
	int											m_AddSurprisePoint;	//追加驚きポイント.

	std::vector<std::unique_ptr<CPeopleIcon>>	m_pCPeopleIcon;		//人のアイコン.

	bool										m_bPauseFlag;		//ポーズフラグ.
	bool										m_bNotRenderIcon;	//アイコン描画しないフラグ.
};


#endif	//#ifndef CPEOPLE_MANAGER_H.