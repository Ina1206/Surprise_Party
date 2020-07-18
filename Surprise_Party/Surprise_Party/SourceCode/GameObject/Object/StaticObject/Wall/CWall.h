#ifndef CWALL_H
#define CWALL_H

#include "..\CStaticObjectBase.h"

/*****************************************
*		�ǃI�u�W�F�N�g�N���X.
*******/
class CWall
	: public CStaticObjectBase
{
public:
	CWall();
	~CWall();

	//=====================�萔====================//.
	const float		ALPHA_DIVISOR	= 80.0f;	//���ߒl����l.
	const float		WALL_ALPHA_MIN	= 0.8f;		//�ǂ̓��ߒl�ŏ��l.
	const float		SCALE			= 0.1f;		//�傫��.

	//=====================�֐�====================//.
	void Update();		//�X�V�����֐�.

private:
	//=====================�֐�======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};

#endif	//#ifndef CWALL_H.