#ifndef CSCENE_BASE_H
#define CSCENE_BASE_H

#include "..\..\Global.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/************************************
*		シーン基底クラス.
*****/
class CSceneBase
{
public:
	CSceneBase();
	virtual ~CSceneBase();

	//===================定数======================//.
	const D3DXVECTOR4	BACK_COLOR	= D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);	//背景の色.


	//===================関数======================//.
	void	RenderInitSetting(const D3DXMATRIX& mProj);						//描画初期設定.

	virtual void UpDate()	= 0;											//更新処理関数.
	virtual void Render()	= 0;											//描画処理関数.
	void PlayBGM(const enBGMType& enBGMType);								//BGM再生処理関数.

	//=============情報獲得処理関数================//.
	D3DXVECTOR4 GetBackColor()		{ return m_vBackColor; }				//後ろの色情報取得処理関数.
	bool		GetChangeSceneFlag(){ return m_bChangeScene; }				//シーン変更フラグ取得処理関数.
	bool		GetPauseFlag() const { return m_bPauseFlag; }				//一時停止フラグ.
	int			GetEvaluation() const { return m_Evaluation; }				//評価.
	bool		GetTitleFlag() const { return m_bTitle; }					//タイトルフラグ.
	bool		GetChangeVolume() const { return m_bChangeVolume; }			//外部で音量変更フラグ.

	//=============情報置換処理関数================//.
	void SetPauseFlag(const bool& flag) { m_bPauseFlag = flag; }			//一時停止フラグ.
	void SetEvaluation(const int& Num) { m_Evaluation = Num; }				//評価.
	void SetPlayBGM(const enBGMType& enBGM) { m_enPlayBGMType = enBGM; }	//再生BGMの種類.
	void SetBGMVolume(const int& Volume); 									//音量.
	void SetTitleFlag(const bool& bFlag) { m_bTitle = bFlag; }				//タイトルフラグ.
protected:
	//===================関数======================//.
	virtual void Init()		= 0;											//初期化処理関数.
	virtual void Release()	= 0;											//解放処理関数.

	//===================変数======================//.
	D3DXMATRIX	m_mView;													//ビュー行列.
	D3DXMATRIX	m_mProj;													//プロジェクション行列.
	bool		m_bChangeScene;												//シーン変更フラグ.
	bool		m_bPauseFlag;												//一時停止フラグ.
	int			m_Evaluation;												//評価.
	bool		m_bTitle;													//タイトルへフラグ.
	int			m_BGMVolume;												//BGMの音量.
	enBGMType	m_enPlayBGMType;											//再生BGMの種類.
	bool		m_bChangeVolume;											//外部で音量変更フラグ.
private:
	//===================変数======================//.
	D3DXVECTOR4 m_vBackColor;												//後ろの色.

};

#endif	//#ifndef CSCENE_BASE_H.