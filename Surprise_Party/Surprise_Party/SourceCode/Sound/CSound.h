#ifndef C_SOUND_H
#define C_SOUND_H

#include <Windows.h >
#include <string>

//ײ���ؓǍ�.
#pragma comment( lib, "winmm.lib" )

//�������ޯ̧.
const int STR_BUFF_MAX = 256;

/**********************************************************.
*	����޸׽.	
*		midi, mp3, wav�`����̧�ق̍Đ��E��~�����s��.
**/
class clsSound
{
public:
	clsSound();		//�ݽ�׸�.
	~clsSound();	//�޽�׸�.

	//����̧�ق��J��.
	bool Open(const LPCTSTR& sFName, const std::string& sAlias, HWND hWnd);

	//����̧�ق����.
	bool Close();

	//�Đ�.
	//��������ݸނŃ`�F�b�N�������ꍇ�O�ڂ̂������.
	//��Ԃ����������Ȃ��ꍇ����̫�Ă� false �������Ă���̂ň�������ł�OK.
	bool Play( bool bNotify = false );

	//��~.
	bool Stop();

	//��Ԃ��擾����֐�.
	bool GeaStatus( char *sStatus );

	//���̒�~���m�F����֐�.
	bool IsStopped();

	//���̍Đ������m�F����֐�.
	bool IsPlaying();

	//�Đ��ʒu���ŏ��ɖ߂��֐�.
	bool SeekToStart();

	//���ʂ𒲐�����֐�.
	bool VolumeConvert(const int& volume);

private:
	HWND	m_hWnd;	//����޳�����.
	char	m_sAlias[STR_BUFF_MAX];//��ر�.

	//�����ݒ�֐�.
	void SetInitParam( const std::string& sAlias, HWND hWnd );
};


#endif //#ifndef C_SOUND_H