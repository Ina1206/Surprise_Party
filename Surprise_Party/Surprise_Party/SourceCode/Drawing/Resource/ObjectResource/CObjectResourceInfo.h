#ifndef COBJECT_RESOURCE_INFO_H
#define COBJECT_RESOURCE_INFO_H

//�X�^�e�B�b�N���b�V���̎��.
enum class enStaticMeshType {
	Wall,				//��.
	Floor,				//��.
	Painting,			//�G��.
	BookShelf,			//�{�I.
	MoveObjectSwitch,	//�I�u�W�F�N�g�ړ��X�C�b�`.
	PlaySoundSwitch,	//������X�C�b�`.
	SwitchPushGhost,	//�X�C�b�`������������.
	Phone,				//�g��.
	HitSphere,			//�����蔻��p�X�t�B�A.
	Table,				//��.
	Vase_Flower,		//�ԕr.

	Max,		//�ő�l.
	Start = Wall,
};

//�X�L�����b�V���̎��.
enum class enSkinMeshType {
	Girl,				//���̎q.
	Boy,				//�j�̎q.
	DispGhost,			//����邨����.
	BigGhost,			//�傫��������.
	Max,				//�ő�l.
};

//�e�N�X�`���ύX�I�u�W�F.
enum class enSkinTexChange {
	Girl,	//���̎q.
	Max
};

#endif	//#ifndef COBJECT_RESOURCE_INFO_H.