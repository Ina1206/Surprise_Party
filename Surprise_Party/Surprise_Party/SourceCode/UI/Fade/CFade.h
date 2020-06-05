#ifndef CFADE_H
#define CFADE_H

#include "..\CUI.h"

/******************************************
*		�t�F�[�h�N���X.
***********/
class CFade
	: public CUI
{
public:
	CFade();
	virtual ~CFade();

	//======================�֐�==========================//.
	virtual void Update() = 0;	//�X�V�����֐�.
	virtual void Render() = 0;	//�`�揈���֐�.


protected:
	//======================�֐�===========================//.
	virtual void Init() = 0;	//�����������֐�.
	virtual void Release() = 0;	//��������֐�.

	//======================�ϐ�===========================//.
	CResourceManager*	m_pCResourceManager;	//���\�[�X�Ǘ��N���X.

};

#endif	//#ifndef CFADE_H.