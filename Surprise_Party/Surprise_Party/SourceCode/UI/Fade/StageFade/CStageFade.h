#ifndef CSTAGE_FADE_H
#define CSTAGE_FADE_H

#include "..\CFade.h"

/******************************************
*		ステージフェードクラス.
**************/
class CStageFade
	: public CFade
{
public:
	CStageFade();
	~CStageFade();

	//=================定数=====================//.
	const int			UI_MAX						= 4;									//UI最大値.
	const int			LEFT_CURTAIN_NUM			= 0;									//左カーテン番号.
	const int			RIHGT_CURTAIN_NUM			= 1;									//右カーテン番号.
	const int			SIGN_BOARD_NUM				= 2;									//看板番号.
	const int			STRING_NUM					= 3;									//文字番号.

	const unsigned int	OPENING_FLAG				= (1 << 0);								//開店時のカーテン移動フラグ.
	const unsigned int	CLOSE_FLAG					= (1 << 1);								//閉店時のカーテン移動フラグ.
	const unsigned int	CHANGE_STAGE_FLAG			= (1 << 2);								//ステージ変更フラグ.
	const unsigned int	CLOSE_CURTAIN_FLAG			= (1 << 3);								//閉じ切ったフラグ.
	const unsigned int	OPEN_CHANG_FLAG				= (1 << 4);								//看板変更フラグ.
	const unsigned int	SIGN_BOARD_SWING_FLAG		= (1 << 5);								//看板揺れフラグ.
	const unsigned int	OPEN_CURTAIN_FLAG			= (1 << 6);								//カーテン開くフラグ.

	const float			SCALE_MAX					= 1.0f;									//大きさ最大値.
	const float			ROT_MAX						= 3.1f;									//角度最大値.
	const float			HALF_ROT_ANGLE				= 1.6f;									//半回転角度.
	const float			CURTAIN_ROT_MIN				= -3.1f;								//カーテン角度最小値.
	const D3DXVECTOR3	BOARD_PRE_POS				= D3DXVECTOR3(-320.0f, -10.0f, 0.0f);	//板の誤差座標.
	const D3DXVECTOR3	SIGN_BOARD_INIT_POS			= D3DXVECTOR3(650.0f, -500.0f, 0.0f);	//看板の初期座標.
	const D3DXVECTOR3	STRING_PRE_POS				= D3DXVECTOR3(-150.0f, 300.0f, 0.0f);	//文章誤差座標.

	const float			SIGN_BOARD_HEIGHT_MAX		= 80.0f;								//看板高さ最大値.

	const int			OPEN_DIRECT					= -1;									//開く方向.
	const int			CLOSE_DIRECT				= 1;									//閉じる方向.

	const float			CURTAIN_ROT_SPEED			= 0.03f;								//カーテン角度速度.
	const float			SIGN_BOARD_MOVE_SPEED		= 6.0f;									//看板移動速度.
	const float			SIGN_BOARD_ROT_SPEED		= 0.1f;									//看板回転速度.
	const float			SIGN_BOARD_SCALE_SPEED		= 0.02f;								//看板拡縮速度.

	const int			CHANGE_DIRECT				= -1;									//方向変更.
	const float			SWING_ROT_MAX_SPEED			= 0.3f;									//揺れる角度最大速度.
	const float			SWING_SPEED					= 0.01f;								//揺れる速度.

	const float			SWING_ROT_LIMIT_MIN			= 0.1f;									//揺れる角度上限最小.
	const float			SWING_ROT_MIN				= 0.05f;								//揺れる角度最小値.
	const float			SWING_SPEED_MAX				= 0.04f;								//揺れる速度最大値.
	const float			SWING_ROT_MAX				= 0.6f;									//揺れる角度最大値.

	//================列挙体====================//.
	//看板揺れタイプ.
	enum class enSwingSignBoard {
		LeftSwing,	//左.
		RightSwing,	//右.
	};

	//=================関数=====================//.
	void Update();	//更新処理関数.
	void Render();	//描画処理関数.

	//============情報置換処理関数==============//.
	//カーテン移動フラグ.
	void SetCurtainMoveFlag(const unsigned int& flag) { m_CurtainMoveFlag = flag; }

	//============情報獲得処理関数==============//.
	//カーテン移動フラグ.
	unsigned int GetCurtainMoveFlag() { return m_CurtainMoveFlag; }
	//距離の割合.
	float GetDistanceRatio() const { return m_fDistanceRatio; }

private:
	//=================関数=====================//.
	void Init();												//初期化処理関数.
	void Release();												//解放処理関数.
	void OpeningCurtainMove();									//開店時のカーテン移動処理関数.
	void CloseCurtainMove();									//閉店時のカーテン移動処理関数.
	bool CurtainMove();											//カーテン移動処理関数(※看板も移動する).
	bool RotationSignBoard(CSpriteUI*	ChangeStringSpriteUI);	//看板回転処理関数.
	bool SwingSignBoard();										//看板揺れる処理関数.

	//=================変数=====================//.
	std::vector<CSpriteUI*>		m_pCUI;				//スプライトUIクラス.
	std::vector<D3DXVECTOR3>	m_vUIPos;			//座標.
	std::vector<float>			m_fUIScale;			//大きさ.
	std::vector<D3DXVECTOR3>	m_vUIRot;			//角度.
	std::vector<D3DXVECTOR3>	m_vPrePos;			//準備角度.

	unsigned int				m_CurtainMoveFlag;	//カーテン移動フラグ.
	enSwingSignBoard			m_enSwingSignBoard;	//看板の揺れタイプ.
	int							m_SwingRotDirect;	//揺れの角度方向.
	float						m_SwingRotMax;		//揺れの角度最大数.
	float						m_fSwingSpeed;		//揺れの速度.
	CSpriteUI*					m_pCOldSpriteUI;	//前のスプライトUIクラス.
	float						m_fDistanceRatio;	//距離の割合.
	bool						m_bPlayCurtainSE;	//カーテン再生フラグ.
	bool						m_bPlayOpneBell;	//開く音.
};

#endif	//#ifndef CSTAGE_FADE_H.