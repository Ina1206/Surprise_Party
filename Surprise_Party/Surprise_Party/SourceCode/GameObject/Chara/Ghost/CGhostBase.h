#ifndef CGHOST_BASE_H
#define CGHOST_BASE_H

#include "..\CCharaBase.h"

class CGhostBase
	: public CCharaBase
{
public:
	CGhostBase();
	virtual ~CGhostBase();

	//=======================定数==========================//.
	const float			ANGLE_SPEED		= 0.08f;							//角度追加速度.
	const float			ANGLE_MAX		= 360.0f;							//角度最大値.
	const float			ANGLE_MIN		= 0.0f;								//角度最小値.
	const float			UP_DOWN_SPEED	= 0.01f;							//上下移動の速度.
	const float			VERTICAL_WIDTH	= 2.5f;								//縦の幅.
	const D3DXVECTOR3	SKY_DIRECT		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//空方向.

	//================列挙隊===================//.
	enum class enEmotionType {
		Sleep = 0,		//寝る.
		HaveTrounble,	//困る.
		Rejoice,		//喜ぶ.
		Question,		//疑問.
		Nothing,		//無し.
		GoodFeeling,	//ご機嫌.
		ViewSmartphone,	//スマートフォンを見る.

		Max,			//最大値.
	};

	//===========情報置換処理関数==============//.
	void SetEmotionNum(const int& Num) { m_EmotionNum = Num; }			//感情番号.
	void SetLookAtPos(const D3DXVECTOR3& vPos) { m_vLookAtPos = vPos; }	//見る座標.
	void SetRot(const D3DXVECTOR3& vRot) { m_vRot = vRot; }
	void SetChangeBeforePos(const D3DXVECTOR3& vPos) { m_vChangeBeforePos = vPos; }
protected:
	//=======================関数==========================//.
	void MoveUpDown();											//浮遊処理関数.
	void MoveRotation(const D3DXVECTOR3& vSalfPos, 
					  const D3DXVECTOR3& vTargetPos);			//移動角度処理関数.

	//=======================変数==========================//.
	int				m_EmotionNum;			//感情番号.
	D3DXVECTOR3		m_vLookAtPos;			//見る座標.
	D3DXVECTOR3		m_vPrePos;				//座標修正.
	D3DXVECTOR3		m_vChangeBeforePos;		//変更前の座標.		

private:
	//=======================関数==========================//.
	void ConvertRotationMatrixToRadian(const D3DXMATRIX& mMat);	//回転行列からクウォータニオンに変換処理関数.

	//=======================変数==========================//.
	float	m_fMoveAngle;		//移動角度.

};

#endif	//#ifndef CGHOST_BASE_H.