#ifndef CLOAD_H
#define CLOAD_H

#include "..\..\Drawing\Sprite\SpriteUI\CSpriteUI.h"

/*********************************
*		読み込みシーンクラス.
***********/
class CLoad
{
public:
	CLoad();
	~CLoad();

	//=======================関数============================//.
	void Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);	//初期化処理関数.
	void Render();																	//描画処理関数.

private:
	//=======================関数============================//.
	void Release();				//解放処理関数.

	//=======================変数============================//.
	std::unique_ptr<CSpriteUI>	m_pCSpriteUI;	//スプライトUI.
};

#endif	//#ifndef CLOAD_H.