#ifndef CREPUTATION_SNS_H
#define CREPUTATION_SNS_H

#include "..\CSpeakUI.h"

/***************************************
*		SNSでの評判処理関数.
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

	//===========================変数=================================//.
	std::vector<std::string>	m_stArticleDetail;	//記事詳細.
	int							m_EndingTypeNum;	//エンディングタイプ番号.

};

#endif	//#ifndef CREPUTATION_SNS_H.