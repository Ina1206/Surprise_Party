#ifndef CMOVE_OBJECT_BASE_H
#define CMOVE_OBJECT_BASE_H

#include "..\CObjectBase.h"

/***************************************************
*		�����I�u�W�F�N�g���N���X.
***********/
class CMoveObjectBase
	: public CObjectBase
{
public:
	CMoveObjectBase();
	~CMoveObjectBase();

	//==============�萔===============//.
	const int	EFFECT_HANDLE_DEFAULT_VALUE = -1;		//�G�t�F�N�g�n���h�������l.

	//==============�֐�===============//.
	void EffectRender();								//�G�t�F�N�g�`�揈���֐�.
	void AttachedObjRender();							//�t���I�u�W�F�N�g�`�揈���֐�.

	//=========���u�������֐�========//.
	//�J�����\���t���O.
	void SetCameraDispFlag() { m_bCameraDisp = true; }
	//�t���I�u�W�F�N�g���W.
	void SetAttachedObjPos(const int objNum ,const D3DXVECTOR3& vPos) { m_vAttachedObjPos[objNum] = vPos; }
	//�t���I�u�W�F�N�g�p�x.
	void SetAttachedObjRot(const int objNum, const D3DXVECTOR3& vRot) { m_vAttachedObjRot[objNum] = vRot; }

protected:
	//==============�֐�===============//.
	void Hit();											//�����蔻�菈���֐�.
	void EffectUpdate();								//�G�t�F�N�g�X�V�����֐�.

	//==============�ϐ�===============//.
	CEffect*					m_pCEffect;				//�G�t�F�N�g.
	int							m_EffectHandle;			//�G�t�F�N�g�n���h��.
	bool						m_bCameraDisp;			//�J�����ɕ\�����Ă���t���O.
	D3DXVECTOR3					m_vEffectPos;			//�G�t�F�N�g���W.
	float						m_fEffectScale;			//�G�t�F�N�g�傫��.
	std::vector<CDX9Mesh*>		m_pCAttachedObjMesh;	//�t���I�u�W�F�N�g���b�V��.
	std::vector<D3DXVECTOR3>	m_vAttachedObjPos;		//�t���I�u�W�F�N�g���W.
	std::vector<D3DXVECTOR3>	m_vAttachedObjRot;		//�t���I�u�W�F�N�g�p�x.

private:
	//===============�֐�===============//.
	void EffectPlay();									//�G�t�F�N�g�Đ������֐�.
	void EffectStop();									//�G�t�F�N�g��~�����֐�.
};

#endif	//#ifndef CMOVE_OBJECT_BASE_H.