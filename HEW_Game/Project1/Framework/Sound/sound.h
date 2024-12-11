#pragma once

#include <xaudio2.h>

// �T�E���h�t�@�C��
typedef enum
{

	SOUND_LABEL_BGM000 = 0,		// �T���v��BGM
	SOUND_LABEL_BGM001,			// �T���v��BGM
	SOUND_LABEL_SE000,			// �T���v��SE
	SOUND_LABEL_SE001,			// �T���v��SE



	SOUND_LABEL_MAX,
} SOUND_LABEL;

// �p�����[�^�\����
typedef struct
{
	LPCSTR filename;	// �����t�@�C���܂ł̃p�X��ݒ�
	bool bLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
	bool SandW;			//! ���̋���̐؂�ւ����K�v�ȃT�E���h�𔻒�
	float volume;		//! ���̑傫���i1.0f���m�[�}��)
} PARAM;		//PARAM�^�\����

class Sound {

private:
	

	PARAM m_param[SOUND_LABEL_MAX] =
	{
		{"asset/BGM/������.wav", true,true,1.0f},	// �T���v��BGM�i���[�v������̂�true�ݒ�j
//		{"asset/BGM/������.wav", true},	// �T���v��BGM
//		{"asset/SE/������.wav", false},  		// �T���v��SE�i���[�v���Ȃ��̂�false�ݒ�j
//		{"asset/SE/������.wav", false},		// �T���v��SE



	};

	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX]; // WAV�t�H�[�}�b�g
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_MAX];
	BYTE* m_DataBuffer[SOUND_LABEL_MAX];

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

	int Distance = 0;	//�v���C���[�ƃI�u�W�F�N�g�̋��������炤�ϐ�

public:
	// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
	HRESULT Init(void);

	// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
	void Uninit(void);

	// �����Ŏw�肵���T�E���h���Đ�����
	void Play(SOUND_LABEL label);		//enum�Ō��߂��f�[�^�ň����Ƃ��ēn���Ă���

	// �����Ŏw�肵���T�E���h���~����
	void Stop(SOUND_LABEL label);

	//! �����Ŏw�肵���T�E���h�̉��ʂ�ύX����	//�ォ��ǉ��i�o���j
	void ChangeVolume(SOUND_LABEL label,int );

	// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
	void Resume(SOUND_LABEL label);

	//volume�ϐ��̃Z�b�^�[�E�Q�b�^�[�֐��i���ʒ����̂��߁j
	int SetDistance(int);
	int GetDistance(void);

	/*===�T�E���h�t���[�����[�N�݌v===*/

	/*
	���̒�~
	���̍Đ�
	���̃��[�v
	�V�[�����Ƃł̉��y�̐؂�ւ�(�����Ⴄ����)
	���̋���i�Q�[���V�X�e�����ʊO�Ȃ珬�����Ȃǁj���ꂪ��Ԗ��H
	*/
};