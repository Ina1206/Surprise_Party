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
	const unsigned int	START_TRANSPARENT_FLAG	= (1 << 0);							//透過スタートフラグ.
	const unsigned int	CHANGE_STAGE_FLAG		= (1 << 1);							//ステージ変更フラグ.

	const D3DXVECTOR3	INIT_FONT_POS			= D3DXVECTOR3(50.0f, 300.0f, 0.0f);	//文字列初期座標.
	const float			FONT_SCALE				= 90.0f;							//フォント大きさ.
	const float			STRING_WIDTH_MAX		= 1000.0f;							//文字列幅最大値.
	const float			ADJUSTMENT_HEIGHT		= 15.0f;							//カーソル高さ微調整.
	const int			FLASING_CNT_MAX			= 20;								//点滅カウント最大値.
	const int			CURSOR_NUM				= 0;								//カーソル番号.
	const int			PICTURE_NUM				= 1;								//写真番号.	

	//===========================関数=================================//.
	void Update();									//更新処理関数.
	void Render();									//描画処理関数.
	void DecideString(const int& EndingNum);		//文章決定処理関数.

	//=====================情報取得処理関数===========================//.
	//ステージ変更フラグ.
	unsigned int GetChangeStage() const { return m_ChangeStageFlag; }

private:
	//===========================関数=================================//.
	void Init();									//初期化処理関数.
	void Release();									//解放処理関数.
	void UpdateCursor();							//カーソル更新処理関数.
	void MoveCursor();								//カーソル移動.
	void DecidePicture(const int& EndingNum);		//写真決定処理関数.
	void RenderSpriteUI();							//スプライトUI描画処理関数.
	void TransparentAll();							//全ての透過処理関数.

	//===========================変数=================================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;		//スプライトUI.
	std::vector<D3DXVECTOR3>	m_vSpriteUIPos;		//スプライトUI座標.
	std::vector<float>			m_fSpriteUIAlpha;	//スプライトUI透過値.
	int							m_FlashingCursorCnt;//カーソル点滅カウント.
	std::vector<std::string>	m_stArticleDetail;	//記事詳細.
	int							m_EndingTypeNum;	//エンディングタイプ番号.
	unsigned int				m_ChangeStageFlag;	//ステージ変更フラグ.
};

#endif	//#ifndef CREPUTATION_SNS_H.