#ifndef CSCENE_BASE_H
#define CSCENE_BASE_H

#include "..\..\Global.h"

/************************************
*		�V�[�����N���X.
*****/
class CSceneBase
{
public:
	CSceneBase();
	virtual ~CSceneBase();

	//===================�֐�======================//.
	void	RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos);	//�`�揉���ݒ�.
	void	DebugSceneChange();			//�f�o�b�O�p�V�[���ύX�����֐�.
	
	virtual void UpDate()	= 0;		//�X�V�����֐�.
	virtual void Render()	= 0;		//�`�揈���֐�.

	//=============���l�������֐�================//.
	D3DXVECTOR4 GetBackColor()		{ return m_vBackColor; }	//���̐F���擾�����֐�.
	bool		GetChangeSceneFlag(){ return m_bChangeScene; }	//�V�[���ύX�t���O�擾�����֐�.
	bool		GetPauseFlag() const { return m_bPauseFlag; }	//�ꎞ��~�t���O.

	//=============���u�������֐�================//.
	void SetPauseFlag(const bool& flag) { m_bPauseFlag = flag; }//�ꎞ��~�t���O.

protected:
	//===================�֐�======================//.
	virtual void Init()		= 0;		//�����������֐�.
	virtual void Release()	= 0;		//��������֐�.

	//===================�ϐ�======================//.
	D3DXMATRIX	m_mView;		//�r���[�s��.
	D3DXMATRIX	m_mProj;		//�v���W�F�N�V�����s��.
	D3DXVECTOR3 m_vLightPos;	//���C�g���W.
	D3DXVECTOR3 m_vCameraPos;	//�J�������W.
	D3DXVECTOR4 m_vBackColor;	//���̐F.
	bool		m_bChangeScene;	//�V�[���ύX�t���O.
	bool		m_bPauseFlag;	//�ꎞ��~�t���O.

private:

};

#endif	//#ifndef CSCENE_BASE_H.