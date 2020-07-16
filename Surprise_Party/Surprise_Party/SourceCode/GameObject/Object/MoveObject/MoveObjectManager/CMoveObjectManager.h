#ifndef CMVOE_OBJECT_MANAGER_H
#define CMVOE_OBJECT_MANAGER_H

#include "..\..\FileLoad\FileResource\CFileResource.h"
#include "..\GhostDispPainting\CGhostDispPainting.h"
#include "..\Switch\ObjectMoveSwitch\CObjectMoveSwitch.h"
#include "..\Switch\PlaySoundSwitch\CPlaySoundSwitch.h"
#include "..\..\UI\MapUI\CharaUI\Icon\GimmickIcon\CGimmickIcon.h"
#include "..\..\UI\MapUI\CharaUI\MapCursor\MapGimmickCursor\CMapGimmickCursor.h"
#include "..\..\UI\GameWorldUI\GameWorldCursor\GameGimmickCursor\CGameGimmickCursor.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/**********************************
*	�ړ��I�u�W�F�N�g�Ǘ��N���X.
*****/
class CMoveObjectManager
{
public:
	CMoveObjectManager();
	CMoveObjectManager(const int& FileNum, const int& StageNum);
	~CMoveObjectManager();

	//================�񋓑�==================//.
	enum class enMoveObjectType {
		GhostDispPainting = 0,					//�������̌����G��.
		ObjectMoveSwitch,						//�I�u�W�F�N�g�ړ��X�C�b�`.
		PlaySoundSwitch,						//����炷�X�C�b�`.

		Max,									//�ő吔.
		Start = GhostDispPainting,
		UseAttachObjectMax = PlaySoundSwitch	//�t���I�u�W�F�N�g���g���I�u�W�F�N�g�ő吔.
	};

	//=================�萔===================//.
	const unsigned int	ATTACHED_MOVE_PREPARA_FLAG	= (1 << 0);							//�t���I�u�W�F�N�g�ړ������t���O.
	const unsigned int	ATTACHED_MOVE_FLAG			= (1 << 1);							//�t���I�u�W�F�N�g�ړ��t���O.
	const unsigned int	ATTACHED_MOVE_LEFT_FLAG		= (1 << 2);							//�t���I�u�W�F�N�g���ړ��t���O.
	const unsigned int	ATTACHED_MOVE_AFTER_FLAG	= (1 << 3);							//�t���I�u�W�F�N�g�ړ���t���O.

	const int			MOVEOBJECT_START_NUM		= 3;								//�ړ��I�u�W�F�N�g�̊J�n�ԍ�.
	const float			OBJECT_WIDTH				= 2.5f;								//�I�u�W�F�N�g�̕�.
	const float			DISP_CAMERA_WIDHT			= 16.8f;							//�\������J������.
	const D3DXVECTOR3	STANDERD_PAINTING_POS		= D3DXVECTOR3(0.0f, 5.0f, 1.0f);	//��{�̊G��̍��W.
	const float			GIMMICK_UP_GHOST_ADJUST		= 0.1f;								//�M�~�b�N�̏�ɂ�����������Ƃ��̔�����.
	const float			PAINTING_MOVE_GHOST_POS		= 3.4f;								//�M�~�b�N�������������̍��W.
	const float			PAINTING_MOVE_SPEED			= 0.25f;							//�G�悪�������x.
	const float			PAINTING_DOWN_MAX			= 0.5f;								//�G�旎����ő吔.

	const float			SWITCH_UP_DOWN_SPEED		= 0.3f;								//�X�C�b�`�㉺���x.
	const float			SWITCH_HIGHT_MIN			= -1.5f;							//�X�C�b�`�̍����ŏ��l.
	const float			SWITCH_HIGHT_MAX			= 0.0f;								//�X�C�b�`�̍����ő�l.

	const float			VASE_UP_DOWN_SPEED			= 0.3f;								//�ԕr�ړ����x.			
	const float			VASE_HIGHT_MAX				= 2.0f;								//�ԕr�̍����ő�l.
	const float			VASE_HIGHT_MIN				= 0.0f;								//�ԕr�̍����ŏ��l.
	const float			VASE_SWING_SPEED			= 0.06f;							//�ԕr�̗h��鑬�x.
	const float			VASE_ROT_MAX				= 0.5f;								//�ԕr�̊p�x�ő�l.
	const float			VASE_ROT_MIN				= -0.5f;							//�ԕr�̊p�x�ŏ��l.
	const float			VASE_ROT_RETURN				= 0.0f;								//�ԕr�̖߂�p�x.
	const int			VASE_SWING_MAX				= 1;								//�ԕr�̗h���񐔍ő�l.

	const unsigned int	NOT_MOVE_FALG				= (1 << 0);							//�ړ����Ȃ��t���O.
	const unsigned int	DOWN_FLAG					= (1 << 1);							//������t���O.
	const unsigned int	UP_FLAG						= (1 << 2);							//�オ��t���O.

	const unsigned int	POSSIBLE_PLAY_SE_FLAG		= (1 << 0);							//SE�炷���Ƃ��\.
	const unsigned int	PLAYED_SOUND				= (1 << 1);							//����炵����t���O.

	//=================�֐�===================//.
	void UpDate();																				//�X�V�����֐�.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& stLight);		//�`�揈���֐�.
	void RenderSwitch(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& stLight);	//�X�C�b�`�̕`�揈���֐�.
	void EffectRender();																		//�G�t�F�N�g�̕`�揈���֐�.
	int  FindSelectGimmickNumByType(const int& GimmickType, const int& GimmickNum);										//��ޕʃM�~�b�N�ԍ��������鏈���֐�.

	//===========���u�������֐�=============//.
	//�J�����̈ʒu.
	void SetCameraPos(const D3DXVECTOR3& vPos) { m_vCameraPos = vPos; }
	//�I�����Ă���ԍ�.
	void SetSelectionNum(const int& SelectionNum) { m_SelectionNum = SelectionNum; }
	//�������̍��W.
	void SetGhostPos(const std::vector<D3DXVECTOR3>& vPos) { m_vGhostPos = vPos; }
	//�������̍��W�v�f���ݒ�.
	void SetGhostElementCount(const int& Max) { m_vGhostPos.resize(Max); }
	//�M�~�b�N�ړ��t���O.
	void SetGimmickMoveFlag(const int& objNum, const unsigned int& flag) { m_ObjeMoveFlag[objNum] = flag; }
	//�M�~�b�N�\���t���O�ݒ�.
	void SetGimmickCurosrDispFlag(const bool& flag) { m_bGimmickCursorDisp = flag; }
	//�M�~�b�N�g���Ă��邩�t���O.
	void SetUsedGimmickFlag(const int& num, const bool& flag) { m_bUsedGimmickFlag[num] = flag; }
	//UI��`�悷�邩�̃t���O.
	void SetRenderUI(const bool& flag) { m_bRenderUI = flag; }
	//�|�[�Y�t���O.
	void SetPauseFlag(const bool& flag) { m_bPauseFlag = flag; }
	//�����������̋������I�u�W�F�N�g�̎��.
	void SetSurpriseObjToGhost(const CGameObject::enSurpriseObjectType& Type) { m_enGhostSurpriseObjType = Type; }

	//===========���l�������֐�=============//.
	//�M�~�b�N�A�C�R���ő吔.
	int GetGimmickIconMax() { return static_cast<int>(m_pCGimmickIcon.size()); }
	//�I������Ă���M�~�b�N�̏ꏊ.
	D3DXVECTOR3 GetGimmickPos() { return m_vMoveObjectPos[m_SelectionNum]; }
	//�M�~�b�N�̎��.
	CGameObject::enSurpriseObjectType GetSurpriseObjectType(const int& SelectNum) { return m_enSurpriseObjectType[SelectNum]; }
	//�M�~�b�N�̍��W.
	std::vector<D3DXVECTOR3> GetAllGimmickPos() { return m_vMoveObjectPos; }
	//�M�~�b�N�g���Ă��邩�t���O.
	bool GetUsedGimmickFlag(const int& num) { return m_bUsedGimmickFlag[num]; }
	//�M�~�b�N�ԍ����擾.
	int GetGimmickNumByType(const int& Type, const int&num) { return m_GimmickNumByType[Type][num]; }
	//��ނ��Ƃ̍ő�l.
	int GetGimmickMaxByType(const int& Type) { return static_cast<int>(m_GimmickNumByType[Type].size()); }

private:
	//=================�֐�===================//.
	void Init(const int& FileNum, const int& StageNum);																	//�����������֐�.
	void Release();																	//��������֐�.
	void GimmickSort();																//�M�~�b�N�v�f�����בւ������֐�.
	void PaintingUpDown(int objNum);												//�G��𗎂Ƃ�����グ�鏈���֐�..
	void SwitchPush(int objNum, CGameObject::enSurpriseObjectType enSurpriseObj);	//�X�C�b�`�������������֐�.
	void Table_VaseFlowerMove(int objNum);											//���Ɖԕr�̈ړ������֐�.

	//=================�ϐ�===================//.
	D3DXMATRIX										m_mView;					//�r���[�s��.
	D3DXMATRIX										m_mProj;					//�v���W�F�N�V�����s��.
	std::vector<CMoveObjectBase*>					m_pCMoveObjectBase;			//�ړ��I�u�W�F�N�g.
	std::vector<D3DXVECTOR3>						m_vMoveObjectPos;			//�ړ��I�u�W�F�N�g���W.
	std::vector<D3DXVECTOR3>						m_vAttachObjPos;			//�t���I�u�W�F�N�g���W.
	std::vector<D3DXVECTOR3>						m_vAttachRot;				//�t���I�u�W�F�N�g�̊p�x.
	std::vector<int>								m_enMoveObjectType;			//�ړ��I�u�W�F�N�g�^�C�v.
	CFileResource*									m_pCFileResource;			//�ǂݍ��݃N���X.
	D3DXVECTOR3										m_vCameraPos;				//�J�������W.
	std::vector <std::unique_ptr<CGimmickIcon>>		m_pCGimmickIcon;			//�M�~�b�N�A�C�R���N���X.
	std::unique_ptr<CMapGimmickCursor>				m_pCMapGimmicKCursor;		//�}�b�v��̃M�~�b�N�J�[�\��.
	int												m_SelectionNum;				//�I�����Ă���ԍ�.
	std::unique_ptr<CGameGimmickCursor>				m_pCGameGimmickCursor;		//�M�~�b�N�J�[�\���N���X.
	std::vector<CGameObject::enSurpriseObjectType>	m_enSurpriseObjectType;		//�������I�u�W�F�N�g���.
	CGameObject::enSurpriseObjectType				m_enGhostSurpriseObjType;	//�������̋������I�u�W�F�N�g�^�C�v.
	std::vector<D3DXVECTOR3>						m_vGhostPos;				//���������W.
	int												m_GhostMax;					//�������ő吔.
	std::vector<unsigned int>						m_ObjeMoveFlag;				//�㉺�t���O.
	bool											m_bGimmickCursorDisp;		//�M�~�b�N�J�[�\���\���t���O.
	unsigned int									m_DispPaintingMax;			//�G��ő吔.		
	std::vector<unsigned int>						m_AttachedObjMoveFlag;		//�t���I�u�W�F�N�g�ړ��t���O.
	std::vector<int>								m_FlowerSwingCnt;			//�ԕr�̗h���J�E���g.
	std::vector<bool>								m_bUsedGimmickFlag;			//�M�~�b�N���g���Ă���t���O.
	std::vector<bool>								m_bPlayEffectSound;			//�G�t�F�N�g�Ɖ��Đ�.
	bool											m_bRenderUI;				//UI�`�悷�邩�ǂ����̃t���O.
	bool											m_bPauseFlag;				//�|�[�Y�t���O.
	std::vector<std::vector<int>>					m_GimmickNumByType;			//�^�C�v�ʃM�~�b�N�ԍ�.			
	CPlaySoundManager*								m_pCPlaySoundManager;		//�ȍĐ��Ǘ��N���X.
	std::vector<unsigned int>						m_bPlaySurpriseActSE;		//�������s��SE�Đ��t���O.
};

#endif	//#ifndef CMVOE_OBJECT_MANAGER_H.