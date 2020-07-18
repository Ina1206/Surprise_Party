#ifndef CFRONTSTAGE_LIGHT_H
#define CFRONTSTAGE_LIGHT_H

#include "..\CLightBase.h"

/*********************************
*		�\����̃��C�g�N���X.
*************/
class CFrontstageLight
	: public CLightBase
{
public:
	CFrontstageLight();
	~CFrontstageLight();

	//======================�萔========================//.
	const float			REFLECTION_RANGE	= 16.0f;							//�ʂ�͈�.
	const D3DXVECTOR3	LIGHT_POS			= D3DXVECTOR3(0.0f, 21.7f, -0.5f);	//���W.
	const float			LIGHT_INTENSITY		= 119.0f;							//���C�g�̋���.
	const float			LIGHT_WIDTH			= 10.9f;							//���C�g��.
	const float			LIGHT_POS_WIDHT		= 20.0f;							//���C�g�̍��W��.
	const D3DXVECTOR3	LIGHT_COLOR			= D3DXVECTOR3(0.5f, 0.5f, 1.0f);	//���C�g�̐F.
	const float			LIGHT_MAX			= 3.0f;								//���C�g�̍ő�l.

	//======================�֐�========================//.
	void Update();										//�X�V�����֐�.
	void SettingAllLightPos(const float& fDistance);	//�S�Ẵ��C�g�̍��W�ݒ菈���֐�.

	//================���u�������֐�==================//.
	void SetCameraPos(const D3DXVECTOR3& vCameraPos) { m_vCameraPos = vCameraPos; }

private:
	//======================�֐�========================//.
	void Init();										//�����������֐�.
	void Release();										//��������֐�.

	//======================�ϐ�========================//.
	std::vector<D3DXVECTOR3>	m_vLightPos;			//���C�g�������W.
	D3DXVECTOR3					m_vCameraPos;			//�J�������W.
};

#endif	//#ifndef CFRONTSTAGE_LIGHT_H.