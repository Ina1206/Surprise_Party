#ifndef CCAMERA_ENDING_H
#define CCAMERA_ENDING_H

#include "..\CCameraBase.h"

/******************************************
*		エンディングカメラクラス.
***************/
class CCameraEnding
	: public CCameraBase
{
public:
	CCameraEnding();
	~CCameraEnding();

	//===========================関数===============================//.
	void Update();	//更新処理関数.

private:
	//===========================関数===============================//.
	void Init();	//初期化処理関数.
	void Release();	//解放処理関数.


};

#endif	//#ifndef CCAMERA_ENDING_H.