#ifndef COBJECT_MANAGER_H
#define COBJECT_MANAGER_H

#include "..\..\..\FileLoad\FileResource\CFileResource.h"
#include "..\Floor\CFloor.h"
#include "..\Wall\CWall.h"
#include "..\Painting\CPainting.h"
#include "..\BookShelf\CBookShelf.h"

/********************************************
*		�ÓI�I�u�W�F�N�g�Ǘ��N���X.
*********/
class CStaticObjectManager
{
public:
	CStaticObjectManager();
	~CStaticObjectManager();

	//================�񋓑�===================//.
	//�I�u�W�F�N�g�̎��.
	enum class enStaticObjectType {
		Painting = 0,			//�G��.
		BookShelf,				//�{�I.
		Wall,					//��.
		Floor,					//�n��.

		Max,					//�ő�l.
		Start = Wall,			//�X�^�[�g�l.
		ObjMax = Wall,			//�I�u�W�F�N�g�̍ő�l.
	};

	//=================�萔===================//.
	const float			OBJECT_WIDTH			= 2.5f;									//�I�u�W�F�N�g�̕�.
	const float			DISP_CAMERA_WIDHT		= 16.8f;								//�\������J������.
	const int			CREATION_MAX			= 14;									//�쐬����ő吔.
	const int			COLUMN_MAX				= 4;									//��̍ő吔.
	const int			ALL_OBJECT_MAX			= CREATION_MAX * COLUMN_MAX;			//���ƕǂ̃I�u�W�F�N�g�̑���.
	const float			WALL_POS_Z				= 1.0f;									//�ǂ�z���W�̈ʒu.
	const D3DXVECTOR3	FLOOR_START_POS			= D3DXVECTOR3(-1.25f, -1.1f, -1.4f);	//���̊J�n�ʒu.
	const int			OTHER_CREATION_MAX		= 6;									//���̍쐬����I�u�W�F�N�g�̍ő吔.
	const D3DXVECTOR3	STANDERD_PAINTING_POS	= D3DXVECTOR3(0.0f, 5.0f, 1.0f);		//��{�̊G��̍��W.

	//=================�֐�====================//.
	void UpData();																						//�X�V�����֐�.
	void Render(const D3DXMATRIX& mView,const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos);		//�`�揈���֐�.

	//===========���u�������֐�==============//.
	//�J�������W.
	void SetCameraPos(const D3DXVECTOR3& vPos) { m_vCameraPos = vPos; }

	//===========���l�������֐�==============//.
	//�X�e�[�W�����ő吔.
	float GetStageDistanceMax() { return m_fStageDistanceMax; }

private:
	//=================�֐�====================//.
	void Init();					//�����������֐�.
	void Release();					//��������֐�.
	void WallAndFloorSetting();		//�ǂƏ��̐ݒ菈���֐�.
	void OtherObjectSetting();		//���̃I�u�W�F�N�g�ݒ菈���֐�.
	void ObjectRender(std::vector<CObjectBase*> obj, int max);


	//=================�ϐ�====================//.
	D3DXMATRIX					m_mView;
	D3DXMATRIX					m_mProj;
	D3DXVECTOR3					m_vLightPos;

	CFileResource*				m_pCFileResource;	//�t�@�C���ǂݍ���.
	std::vector<CObjectBase*>	m_pCObjectBase;		//�ǂƏ��̃I�u�W�F�N�g�N���X.
	std::vector<D3DXVECTOR3>	m_vObjectPos;		//�ǂƏ��̃I�u�W�F�N�g���W.

	std::vector<CObjectBase*>	m_pCOtherObjectBase;//���̃I�u�W�F�N�g�N���X.
	std::vector<D3DXVECTOR3>	m_vOtherObjectPos;	//���̃I�u�W�F�N�g���W.
	std::vector<unsigned int>	m_BeforeObjMax;		//�O�̃I�u�W�F�N�g�܂ł̑����l.
	D3DXVECTOR3					m_vCameraPos;		//�J�������W.
	float						m_fStageDistanceMax;//�X�e�[�W�����ő吔.
};

#endif	//#ifndef COBJECT_MANAGER_H.