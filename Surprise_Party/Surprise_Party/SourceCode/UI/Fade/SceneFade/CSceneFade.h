#ifndef CSCENE_FADE_H
#define CSCENE_FADE_H

#include "..\CFade.h"

/****************************************
*		シーンのフェードクラス.
**********/
class CSceneFade
	: public CFade
{
public:
	CSceneFade();
	~CSceneFade();

	//==================定数======================//.
	const unsigned int	CLOSE_FLAG				= (1 << 0);							//フェードインフラグ.
	const unsigned int  OPEN_FLAG				= (1 << 1);							//フェードアウトフラグ.
	const unsigned int	CHANGE_SCENE_FLAG		= (1 << 2);							//シーン変更フラグ.

	const float			ADD_MOVE_SPEED			= 0.1f;								//加速移動速度.
	const float			SHUTTER_MOVE_SPEED		= 8.0f;								//シャッター移動速度.
	const float			SHUTTER_HEIGHT_MIN		= -850.0f;							//シャッター高さ最小値.
	const D3DXVECTOR3	SHUTTER_INIT_POS		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//シャッター初期値.

	const int			WAIT_CHANGE_SCENE_TIME	= 30;								//シーン変更待機時間.

	//==================関数======================//.
	void Update();								//更新処理関数.
	void Render();								//描画処理関数.

	//==============情報置換処理関数==============//.
	//シャッター動きフラグ.
	void SetShutterFlag(const unsigned int& flag) { m_ShutterFlag = flag; }

	//==============情報取得処理関数==============//.
	//シャッター動きフラグ.
	unsigned int GetShutterFlag() { return m_ShutterFlag; }
	//最終地点までの距離.
	float GetFinishPoDistanceRatio() { return m_fFinishPoDistanceRatio; }

private:
	//==================関数======================//.
	void Init();								//初期化処理関数.
	void Release();								//解放処理関数.
	void ShutterDown();							//シャッター下げる処理関数.
	void ShutterUp();							//シャッター上げる処理関数.

	//==================変数======================//.
	CSpriteUI*		m_pCSpriteUI;				//スプライトUI.
	D3DXVECTOR3		m_vPos;						//座標.
	float			m_fMoveSpeed;				//移動速度.

	unsigned int	m_ShutterFlag;				//シャッター動きフラグ.
	int				m_WaitChangeCnt;			//変更待機カウント.
	float			m_fFinishPoDistanceRatio;	//最終地点までの距離.
	bool			m_bPlaySound;				//音再生フラグ.
};

#endif	//#ifndef CSCENE_FADE_H.