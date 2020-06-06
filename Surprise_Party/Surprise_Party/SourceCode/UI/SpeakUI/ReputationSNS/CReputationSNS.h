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

	//===========================関数=================================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//===========================関数=================================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void UpdateCursor();//カーソル更新処理関数.
	void RenderCursor();//カーソル描画処理関数.

	//===========================変数=================================//.
	CSpriteUI*					m_pCSpriteUI;		//スプライトUI.	
	D3DXVECTOR3					m_vCursorPos;		//カーソル座標.
	float						m_fCursorAlpha;		//カーソル透過値.
	int							m_FlashingCursorCnt;//カーソル点滅カウント.
	std::vector<std::string>	m_stArticleDetail;	//記事詳細.
	int							m_EndingTypeNum;	//エンディングタイプ番号.

};

#endif	//#ifndef CREPUTATION_SNS_H.