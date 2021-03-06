#ifndef CGHOST_SPEAK_STAGE_H
#define CGHOST_SPEAK_STAGE_H

#include "..\StageBase\CStageBase.h"
#include "..\..\..\FileLoad\FileResource\CFileResource.h"
#include "..\..\GameObject\Object\StaticObject\Floor\CFloor.h"
#include "..\..\GameObject\Chara\Ghost\BigGhost\CBigGhost.h"
#include "..\..\UI\SpeakUI\SpeakBigGhost\CSpeakBigGhost.h"
#include "..\..\GameObject\Object\StaticObject\Light\BackstageLight\CBackstageLight.h"

/*****************************************
*	お化けとの会話ステージクラス.
*********/
class CGhostSpeakStage
	: public CStageBase
{
public:
	CGhostSpeakStage();
	CGhostSpeakStage(int stagenum, enBeforeStageEndigneType BeforeStageEndingType);
	~CGhostSpeakStage();

	//========================定数=============================//.
	const D3DXVECTOR3	FLOOR_POS					= D3DXVECTOR3(0.0f, -6.0f, 0.0f);		//床の座標.
	const D3DXVECTOR3	INIT_CAMERA_POS				= D3DXVECTOR3(5.0f, 2.5f, -3.5f);		//カメラ初期位置.
	const D3DXVECTOR3	INIT_CAMERA_LOOK			= D3DXVECTOR3(5.0f, 2.5f, 5.0f);		//カメラ初期注視点.
	const D3DXVECTOR3	SPEAK_START_POS				= D3DXVECTOR3(6.0f, 2.7f, 1.3f);		//会話開始時のカメラ座標.
	const D3DXVECTOR3	SPEAK_START_LOOK			= D3DXVECTOR3(6.0f, 2.2f, 5.0f);		//会話開始時のカメラ注視点.
	const D3DXVECTOR3	CAMERA_POS_DISTANCE			= SPEAK_START_POS - INIT_CAMERA_POS;	//カメラの座標距離.
	const D3DXVECTOR3	CAMERA_LOOK_DISTANCE		= SPEAK_START_LOOK - INIT_CAMERA_LOOK;	//カメラの注視点距離.
	const float			CAMER_MOVE_SPEED			= 0.02f;								//カメラ移動速度.
	const int			GET_CLOSER_CAMERA_DIRECT	= 1;									//カメラが接近する方向.
	const int			FAR_AWAY_CAMERA_DIRECT		= -1;									//カメラが遠のく方向.

	//========================関数=============================//.
	void UpDate(const bool& ControlFlag);		//更新処理関数.
	void Render();								//描画処理関数.
	void Control();								//操作処理関数.


private:
	//========================関数=============================//.
	void Init();								//初期化処理関数.
	void Release();								//解放処理関数.
	void SettingEmotion();						//感情設定処理関数.

	//========================関数=============================//.
	CFontResource*						m_pCFontResource;		//フォント読み込みクラス.
	std::unique_ptr<CFloor>				m_pCFloor;				//床.
	std::unique_ptr<CBigGhost>			m_pCBigGhost;			//大きいお化け.
	std::unique_ptr<CSpeakBigGhost>		m_pCSpeakBigGhost;		//大きいお化け会話クラス.

	std::unique_ptr<CBackstageLight>	m_pCBackstageLight;		//舞台裏のライトクラス.

	bool								m_StageFinish;			//ステージ終了フラグ.

	bool								m_bOldSleepBigGhost;	//大きいお化け寝るフラグ差分用.
};

#endif //#ifndef CGHOST_SPEAK_STAGE_H.