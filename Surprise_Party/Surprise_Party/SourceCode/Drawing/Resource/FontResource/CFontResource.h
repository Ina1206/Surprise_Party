#ifndef CFONT_RESOURCE_H
#define CFONT_RESOURCE_H

#include "..\..\..\Global.h"
#include "..\..\Font\CFont.h"
#include "..\..\Sprite\CDepth_Stencil.h"

/*********************************************
*	フォント読み込みクラス.
**********/
class CFontResource
{
public:
	CFontResource();
	~CFontResource();

	//=================定数====================//.
	const int		FONT_SIZE		= 500;													//フォントの大きさ.
	const float		BASIC_WIDTH		= 1.0f;													//基本の幅.

	//=================関数====================//.
	void Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);					//初期化処理関数.
	void Load(std::string str, bool InputPictureFlag = false);								//読み込み処理関数.
	void String_Render();																	//文字列描画処理関数.
	void Destroy();																			//削除処理関数.

	//==========情報置換処理関数===============//.
	void SetStartPos(const D3DXVECTOR3& vPos) { m_vStartPos = vPos; }						//開始座標.
	void SetFontScale(const float& fScale) { m_fFontScale = fScale; }						//フォント大きさ.
	void SetAlpha(const float& fAlpha, const int& FontNum) { m_fAlpha[FontNum] = fAlpha; }	//透過値.
	void SetWidthMax(const float& fWidthMax) { m_fWidthMax = fWidthMax; }					//表示横幅最大値.

	//==========情報獲得処理関数===============//.
	CFont*			GetFont() const { return m_pCFont[0].get(); }
	int				GetStrLength() const { return m_StrLength; }							//文字列長さ取得.
	D3DXVECTOR3		GetFontPos(const int& num) const { return m_vPos[num]; }				//フォント座標取得.
	unsigned int	GetInputPictureSize() const { return m_InputPictureNum.size(); }		//文章の中に入れる絵のサイズ.
	int				GetInputPictureNum(const int& num) { return m_InputPictureNum[num]; }	//文章の中に入れる絵の番号.
	std::string		GetPictureTypeNum(const int& num) { return m_PictureTypeNum[num]; }		//絵の種類番号.

private:
	//=================関数====================//.
	void Release();																			//解放処理関数.

	//=================変数====================//.
	ID3D11Device*							m_pDevice11;									//デバイスオブジェクト.
	ID3D11DeviceContext*					m_pContext11;									//コンテキスト.
	std::vector<std::unique_ptr<CFont>>		m_pCFont;										//フォントクラス.
	int										m_StrLength;									//文字列の長さ.
	D3DXVECTOR3								m_vStartPos;									//一文字目の位置.
	std::vector<D3DXVECTOR3>				m_vPos;											//座標.
	HFONT									m_hFont;										//フォント.
	HDC										m_hdc;											//デバイスコンテキスト.
	float									m_fFontScale;									//文字の大きさ.
	std::vector<float>						m_fAlpha;										//文字の透過値.
	float									m_fWidthMax;									//文章幅の最大数.
	std::vector<int>						m_InputPictureNum;								//アイコン入れる番号.
	std::vector<std::string>				m_PictureTypeNum;								//絵種類番号.
};

#endif	//#ifndef CFONT_RESOURCE_H.