#ifndef CBACKSTAGE_LIGHT_H
#define CBACKSTAGE_LIGHT_H

#include "..\CLightBase.h"

/*******************************************
*		���䗠�̃��C�g�N���X.
************/
class CBackstageLight
	: public CLightBase
{
public:
	CBackstageLight();
	~CBackstageLight();

	//=======================�萔==========================//.
	const float			LIGHT_INTENSITY = 27.0f;								//���C�g�̋���.
	const float			LIGHT_POS_WIDTH	= 20.0f;								//���C�g�̍��W��.
	const float			LIGHT_WIDTH		= 6.2f;									//���C�g�̕�.
	const float			LIGHT_MAX		= 1.0f;									//���C�g�̌�.
	const D3DXVECTOR3	LIGHT_COLOR		= D3DXVECTOR3(243.0f, 232.0f, 12.0f);	//���C�g�̐F.
	const float			LIGHT_BASE_COLOR= 255.0f;								//�F�̊�l.
	const D3DXVECTOR3	LIGHT_POS		= D3DXVECTOR3(26.2f, 11.7f, 6.7f);		//���C�g�̍��W.

	//=======================�֐�==========================//.
	void Update();		//�X�V�����֐�.

private:
	//=======================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CBACKSTAGE_LIGHT_H.