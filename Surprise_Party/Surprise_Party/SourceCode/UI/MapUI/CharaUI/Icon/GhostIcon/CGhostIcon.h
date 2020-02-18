#ifndef CGHOST_ICON_H
#define CGHOST_ICON_H

#include "..\CIcon.h"

/*************************************
*		お化け用アイコンクラス.
*******/
class CGhostIcon
	: public CIcon
{
public:
	CGhostIcon();
	~CGhostIcon();

	//=======================列挙体=========================//.
	enum class enFaceType {
		Bad_Face = 0,	//悪いときの顔.
		Normal_Face,	//通常時の顔.
		Good_Face,		//良いときの顔.
		Great_Face,		//元気な時の顔.

		Max,			//最大数.
	};

	//========================定数==========================//.
	const D3DXVECTOR2	SELECTED_FACE		= D3DXVECTOR2(0.0f, 1.0f);			//選択中の顔.
	const D3DXVECTOR2	REST_FACE			= D3DXVECTOR2(2.0f, 1.0f);			//休憩中の顔.
	const D3DXVECTOR2	GREAT_FACE			= D3DXVECTOR2(1.0f, 0.0f);			//元気な時の顔.
	const D3DXVECTOR2	GOOD_FACE			= D3DXVECTOR2(0.0f, 0.0f);			//良いときの顔.
	const D3DXVECTOR2	NORMAL_FACE			= D3DXVECTOR2(1.0f, 2.0f);			//通常時の顔.
	const D3DXVECTOR2	BAD_FACE			= D3DXVECTOR2(0.0f, 2.0f);			//悪い時の顔.
	const float			STRENGTH_FACE_MAX	= static_cast<int>(enFaceType::Max);//体力表情最大数.

	//========================関数==========================//.
	void UpDate();		//更新処理関数.

	//===================情報置換処理関数===================//.
	//体力.
	void SetStrength(const float& fStrength) { m_fStrength = fStrength; }
	//体力最大値.
	void SetStrengthMax(const float& fStrength) { m_fStrengthMax = fStrength; }
	//休憩フラグ.
	void SetRestFlag(const bool& bFlag) { m_RestFlag = bFlag; }

	//===================情報取得処理関数====================//.
	//表情種類.
	int GetFaceType() { return m_FaceType; }

private:
	//========================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void ChangeFace();	//表情変更処理関数.

	//========================変数==========================//.
	float			m_fStrength;		//体力.
	float			m_fStrengthMax;		//体力最大値.
	int				m_FaceType;			//表情種類.
	bool			m_RestFlag;			//休憩フラグ.
};

#endif	//#ifndef CGHOST_ICON_H.