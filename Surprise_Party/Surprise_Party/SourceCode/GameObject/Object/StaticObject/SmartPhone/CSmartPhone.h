#ifndef CSMART_PHONE_H
#define CSMART_PHONE_H

#include "..\CStaticObjectBase.h"

/********************************************
*		�X�}�[�g�t�H���N���X
*************/
class CSmartPhone
	: public CStaticObjectBase
{
public:
	CSmartPhone();
	~CSmartPhone();

	//=========================�萔==============================//.
	const float			SCROLL_SPEED	= 0.05f;								//�X�N���[�����x.
	const float			SCROLL_MAX		= 1.0f;									//�X�N���[���ő�l.
	const float			SCALE			= 0.05f;								//�傫��.
	const D3DXVECTOR3	ROT				= D3DXVECTOR3(-30.0f, 170.0f, -5.0f);	//�X��.

	//========================�񋓑�=============================//.
	//�s�����.
	enum class enMoveType {
		SeenGhsot,		//�������Ɍ����Ă��鎞.
		Drop,			//������
	};

	//=========================�֐�==============================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	

private:
	//=========================�֐�==============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//=========================�ϐ�==============================//.
	D3DXVECTOR2	m_vUV;	//UV���W.

};

#endif	//#ifndef CSMART_PHONE_H.