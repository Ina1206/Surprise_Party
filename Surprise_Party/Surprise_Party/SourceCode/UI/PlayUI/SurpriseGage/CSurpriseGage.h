#ifndef CSURPRISE_GAGE_H
#define CSURPRISE_GAGE_H

#include "..\CPlayUI.h"

class CSurpriseGage
	: public CPlayUI
{
public:
	CSurpriseGage();
	CSurpriseGage(int SurprisePointMax);
	~CSurpriseGage();

	//===================定数======================//.
	const int	UI_MAX						= 4;		//UI最大数.
	const int	GAGE_GROUND_NUM				= 0;		//ゲージ下地番号.
	const int	GAGE_NUM					= 1;		//ゲージ番号.
	const int	STAMP_NUM					= 2;		//満員御礼ハンコ番号.
	const int	INFOM_NUM					= 3;		//通知番号.
	const float	INFOM_MOVE_SPEED			= 0.5f;		//通知移動速度.
	const float INFOM_ALPHA_SPEED			= 0.005f;	//通知透過速度.
	const float	CHANGE_ALPHA_HEIGHT			= 300.0f;	//透過変更高さ.
	const float	GET_BONUS_POINT_RATIO		= 0.7f;		//ボーナス貰えるポイント割合.

	const D3DXVECTOR3	GAGE_GROUND_POS		= D3DXVECTOR3(20.0f, 640.0f, 0.0f);		//ゲージ下地座標.
	const D3DXVECTOR3	GAGE_POS			= D3DXVECTOR3(50.0f, 663.0f, 0.0f);		//ゲージ座標.
	const D3DXVECTOR3	STAMP_POS			= D3DXVECTOR3(960.0f, 530.0f, 0.0f);	//満員御礼ハンコ座標.
	const D3DXVECTOR3	INFOM_POS			= D3DXVECTOR3(1080.0f, 180.0f, 0.0f);	//通知座標.

	const D3DXVECTOR3	SHRINK_STOP_SCALE	= D3DXVECTOR3(0.6f, 0.6f, 0.0f);		//縮むのを停止しするサイズ.
	const D3DXVECTOR3	SHRINK_SPEED		= D3DXVECTOR3(0.05f, 0.05f, 0.0f);		//縮む速度.

	const unsigned int BAD_FLAG				= (1 << 0);	//Badフラグ.
	const unsigned int GOOD_FLAG			= (1 << 1);	//Goodフラグ.
	const unsigned int GREAT_FLAG			= (1 << 2);	//Greatフラグ.

	//===================関数======================//.
	void Update();						//更新処理関数.
	void AddSurprisePoint(int Point);	//驚きポイント追加処理関数.

	//=============情報取得処理関数================//.
	//驚きポイント最大数になったフラグ.
	bool GetSurprisePointMax() const { return m_bSurprisePointMax; }
	//ボーナス取得フラグ.
	bool GetBornusGetFlag() const { return m_bBorusGetFlag; }
	//評価フラグ.
	unsigned int GetEvalutionFlag() const { return m_EvalutionFlag; }

private:
	//===================関数======================//.
	void Init();						//初期化処理関数.
	void Release();						//解放処理関数.
	void StampDisp();					//スタンプ表示処理関数.
	void InfomMove();					//通知移動処理関数.
	void EvalutionSurprisePoint();		//驚きポイント評価処理関数.

	//===================変数======================//.
	int				m_SurprisePoint;	//驚かしポイント.
	int				m_SurprisePointMax;	//驚かしポイント最大数.
	bool			m_bSurprisePointMax;//驚きポイント最大数になったフラグ.
	bool			m_bBorusGetFlag;	//ボーナス取得フラグ.
	unsigned int 	m_EvalutionFlag;	//評価フラグ.
};


#endif	//#ifndef CSURPRISE_GAGE_H.