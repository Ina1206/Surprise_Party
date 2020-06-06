#ifndef CREPUTATION_SNS_H
#define CREPUTATION_SNS_H

#include "..\CSpeakUI.h"

/***************************************
*		SNSでの評判クラス.
*******************/
class CReputationSNS
	: public CSpeakUI
{
public:
	CReputationSNS();
	~CReputationSNS();

	//===========================定数=================================//.
	const D3DXVECTOR3	INIT_FONT_POS		= D3DXVECTOR3(50.0f, 250.0f, 0.0f);	//文字列初期座標.
	const float			FONT_SCALE			= 90.0f;							//フォント大きさ.
	const float			STRING_WIDTH_MAX	= 1000.0f;							//文字列幅最大値.
	const float			ADJUSTMENT_HEIGHT	= 15.0f;							//カーソル高さ微調整.
	const int			FLASING_CNT_MAX		= 20;								//点滅カウント最大値.

	//===========================関数=================================//.
	void Update();									//更新処理関数.
	void Render();									//描画処理関数.
	void DecideString(const int& EndingNum);		//文章決定処理関数.

private:
	//===========================関数=================================//.
	void Init();									//初期化処理関数.
	void Release();									//解放処理関数.
	void UpdateCursor();							//カーソル更新処理関数.
	void RenderCursor();							//カーソル描画処理関数.
	void MoveCursor();								//カーソル移動.

	//===========================変数=================================//.
	CSpriteUI*					m_pCSpriteUI;		//スプライトUI.	
	D3DXVECTOR3					m_vCursorPos;		//カーソル座標.
	float						m_fCursorAlpha;		//カーソル透過値.
	int							m_FlashingCursorCnt;//カーソル点滅カウント.
	std::vector<std::string>	m_stArticleDetail;	//記事詳細.
	int							m_EndingTypeNum;	//エンディングタイプ番号.

};

#endif	//#ifndef CREPUTATION_SNS_H.