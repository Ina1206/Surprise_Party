#ifndef CCAMERA_BASE_H
#define CCAMERA_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"

/**************************************
*		�J�����N���X.
**************/
class CCamera
{
public:
	CCamera();
	~CCamera();

	//=======================�֐�==========================//.
	void Update();				//�X�V�����֐�.
	void InitGameMainStage();	//�Q�[�����C���X�e�[�W�̏����������֐�.
	void InitGhostSpeakStage();	//���������b���X�e�[�W�̏����������֐�.
	void InitEnding();			//�G���f�B���O�̏����������֐�.

	//=================���擾�����֐�====================//.
	//�J�������W.
	D3DXVECTOR3 GetCameraPos() const { return m_Camera.vPos; }

private:
	//=======================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//=======================�ϐ�==========================//.
	CAMERA	m_Camera;	//�J�������.

};

#endif	//#ifndef CCAMERA_BASE_H.