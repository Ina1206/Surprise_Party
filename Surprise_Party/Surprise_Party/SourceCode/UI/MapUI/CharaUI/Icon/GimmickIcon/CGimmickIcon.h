#ifndef CGIMMICK_ICON_H
#define CGIMMICK_ICON_H

#include "..\CIcon.h"

/******************************************
*		ギミックアイコンクラス.
*********/
class CGimmickIcon
	: public CIcon
{
public:
	CGimmickIcon();
	CGimmickIcon(int GimmickNum);
	~CGimmickIcon();

	//==========================定数==============================//.
	const D3DXVECTOR3	INIT_POS = D3DXVECTOR3(0.0f, 60.0f, 0.0f);	//初期座標.

	//=========================列挙体=============================//.
	//ギミックの種類.
	enum class enGimmickType {
		DispGhost = 0,	//お化けが現れる.
		SwitchObject,	//スイッチ.
	};

	//==========================関数==============================//.
	void UpDate();		//更新処理関数.

private:
	//==========================関数==============================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//==========================変数==============================//.
	int	m_GimmickType;	//ギミックタイプ.

};

#endif	//#ifndef CGIMMICK_ICON_H.