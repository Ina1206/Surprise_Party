#ifndef CCAMERA_GHOST_SPEAK_STAGE_H
#define CCAMERA_GHOST_SPEAK_STAGE_H

#include "..\CCameraBase.h"

/**********************************************
*		お化けが話すステージのカメラクラス.
**************/
class CCameraGhostSpeakStage
	: public CCameraBase
{
public:
	CCameraGhostSpeakStage();
	~CCameraGhostSpeakStage();

	//========================関数==========================//.
	void Update();		//更新処理関数.
private:
	//========================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CCAMERA_GHOST_SPEAK_STAGE_H.