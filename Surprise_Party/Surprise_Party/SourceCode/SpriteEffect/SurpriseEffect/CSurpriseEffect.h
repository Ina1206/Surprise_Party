#ifndef CSURPRIES_EFFECT_H
#define CSURPRIES_EFFECT_H

#include "..\CSpriteEffectBase.h"

/*****************************************
*		驚きエフェクト.
*******************/
class CSurpriseEffect
	: public CSpriteEffectBase
{
public:
	CSurpriseEffect();
	~CSurpriseEffect();

	//======================関数===========================//.
	void Update();							//更新処理関数.
	void PlayStartInit(const int& num);		//再生開始初期化処理関数.

	//================情報置換処理関数=====================//.
	void SetDispFlag(const bool& flag) { m_bAllDispFlag = flag; }

private:
	//======================関数===========================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void AppeartJudgement(const int& num);	//表示判定処理関数.
	void Move(const int& num);				//移動処理関数.

	//======================変数===========================//.
	int					m_DispCnt;		//表示カウント.
	bool				m_bAllDispFlag;	//全体表示フラグ.
	std::vector<float>	m_fDistance;	//距離.

};

#endif	//#ifndef CSURPRIES_EFFECT_H.