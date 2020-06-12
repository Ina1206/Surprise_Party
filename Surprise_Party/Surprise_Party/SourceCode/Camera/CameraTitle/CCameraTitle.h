#ifndef CCAMERA_TITLE_H
#define CCAMERA_TITLE_H

#include "..\CCameraBase.h"

/*******************************************
*		タイトルカメラクラス.
*************/
class CCameraTitle
	: public CCameraBase
{
public:
	CCameraTitle();
	~CCameraTitle();

	//=======================関数==========================//.
	void Update();		//更新処理関数.
	
private:
	//=======================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CCAMERA_TITLE_H.