#ifndef CENDING_STAGE_BASE_H
#define CENDING_STAGE_BASE_H

#include "..\..\GameObject\Chara\Ghost\BigGhost\CBigGhost.h"
#include "..\..\GameObject\Chara\Ghost\WorkGhost\EndingWorkGhost\EndingDispGhost\CEndingDispGhost.h"
#include "..\..\GameObject\Chara\Ghost\WorkGhost\EndingWorkGhost\EndingSwitchGhost\CEndingSwitchGhost.h"
#include "..\..\GameObject\Object\StaticObject\Floor\CFloor.h"
#include "..\..\GameObject\Object\StaticObject\Light\BackstageLight\CBackstageLight.h"
#include "..\..\Camera\CameraEnding\CCameraEnding.h"
#include "..\..\UI\Fade\WhiteScreenFade\CWhiteScreenFade.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/*******************************************
*		エンディングステージ基底クラス.
*****************/
class CEndingStageBase
{
public:
	CEndingStageBase();
	CEndingStageBase(const int& EvaluationNum);
	virtual ~CEndingStageBase();

	//===================定数======================//.
	const int			INIT_EVALUATION_NUM		= -1;								//初期評価番号.
	const unsigned int	SURPRISE_DEGREE_FLAG	= (1 << 0);							//驚かし度フラグ.
	const unsigned int	EVALUATION_STRING_FLAG	= (1 << 1);							//評価文字.
	const unsigned int	GHOST_FLAG				= (1 << 2);							//お化けフラグ.
	const unsigned int	PUSH_ENTER_FLAG			= (1 << 3);							//PushEnterフラグ.
	const D3DXVECTOR3	FLOOR_POS				= D3DXVECTOR3(0.0f, -6.0f, 0.0f);	//床の座標.
	const float			SCALE					= 0.5f;								//大きさ.
	const D3DXVECTOR3	LOOK_POS				= D3DXVECTOR3(5.0f, 1.5f, 8.0f);	//見る場所.
	const int			GHOST_MAX				= 5;								//お化けの最大数.
	const float			START_RADIAN			= -7.0f;							//開始ラジアン.
	const float			RADIAN_WIDTH			= 55.0f;							//ラジアン幅.
	const float			POS_WIDTH				= 2.5f;								//位置の幅.
	const D3DXVECTOR3	ADD_POS					= D3DXVECTOR3(5.0f, 1.5f, 8.0f);	//加算座標.
	const float			ADD_HIGHT				= 0.5f;								//高さ加算.
	const int			BIG_GHOST_NUM			= 2;								//ビッグゴースト番号.
	const int			WORK_GHOST_TYPE_MAX		= 2;								//働くお化け種類最大数.

	//========================関数=============================//.
	virtual void Update() = 0;														//更新処理関数.
	virtual void Render() = 0;														//描画処理関数.

	void RenderInitSetting(const D3DXMATRIX& mProj);								//描画初期設定処理関数.

	//==================情報置換処理関数=======================//.
	//評価.
	void SetEvaluation(const int& Evaluation) { m_Evaluation = Evaluation; }

	//==================情報取得処理関数=======================//.
	//ステージ変更フラグ.
	bool GetChangeStage() const { return m_bChangeStage; }

protected:
	//========================関数=============================//.
	virtual void Init() = 0;														//初期化処理関数.
	virtual void Release() = 0;														//解放処理関数.

	void RenderFloor();																//床の描画処理関数.
	void RenderGhost();																//お化け描画処理関数.
	void SettingBGMVolume();														//BGMの音量を設定処理関数.

	//========================変数=============================//.
	D3DXMATRIX									m_mView;							//ビュー行列.
	D3DXMATRIX									m_mProj;							//プロジェクション行列.
	std::unique_ptr<CBackstageLight>			m_pCBackstageLight;					//舞台裏ライトクラス.
	std::vector<std::unique_ptr<CGhostBase>>	m_pCGhost;							//お化けクラス.
	std::unique_ptr<CCameraEnding>				m_pCCameraEnding;					//エンディングカメラ.
	std::unique_ptr<CWhiteScreenFade>			m_pCWhiteScreenFade;				//白画面のフェード.
	int											m_Evaluation;						//評価.
	int											m_OldEvaluation;					//差分用評価.
	bool										m_bChangeStage;						//ステージ変更フラグ.
	D3DXVECTOR3									m_vObjLookPos;						//オブジェクトが見る場所.
	unsigned int								m_UpdateFlag;						//更新フラグ.
	bool										m_bDisplayAllAtOnce;				//一気に表示フラグ.

private:

	//========================関数=============================//.
	void InitCommonValue();															//共通値の初期化処理関数.
	void CreateInstanceFronClass(const int& num);									//クラスからインスタンスを作成する処理関数.

	//========================変数=============================//.
	std::unique_ptr<CFloor>					m_pCFloor;								//床クラス.
	CPlaySoundManager*						m_pCPlaySoundManager;					//曲再生管理クラス.
	int										m_BGMVolume;							//BGMの音量.
};

#endif	//#ifndef CENDING_STAGE_BASE_H.