#ifndef CGHOST_SPEAK_STAGE_H
#define CGHOST_SPEAK_STAGE_H

#include "..\StageBase\CStageBase.h"
#include "..\..\..\FileLoad\FileResource\CFileResource.h"
#include "..\..\GameObject\Object\StaticObject\Floor\CFloor.h"
#include "..\..\GameObject\Chara\Ghost\BigGhost\CBigGhost.h"
#include "..\..\UI\SpeakUI\SpeakBigGhost\CSpeakBigGhost.h"

/*****************************************
*	お化けとの会話ステージクラス.
*********/
class CGhostSpeakStage
	: public CStageBase
{
public:
	CGhostSpeakStage();
	CGhostSpeakStage(int stagenum);
	~CGhostSpeakStage();

	//========================関数=============================//.
	void UpDate(const bool& ControlFlag);		//更新処理関数.
	void Render();								//描画処理関数.
	void Control();								//操作処理関数.

private:
	//========================関数=============================//.
	void Init();								//初期化処理関数.
	void Release();								//解放処理関数.
	void LoadSpeakString();						//文章読み込み処理関数.

	//========================関数=============================//.
	CFontResource*					m_pCFontResource;
	std::vector<std::string>		changestr;
	std::unique_ptr<CFloor>			m_pCFloor;			//床.
	std::unique_ptr<CBigGhost>		m_pCBigGhost;		//大きいお化け.
	std::unique_ptr<CSpeakBigGhost>	m_pCSpeakBigGhost;	//大きいお化け会話クラス.
	
};

#endif //#ifndef CGHOST_SPEAK_STAGE_H.