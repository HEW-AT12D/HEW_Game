#pragma once

#include <xaudio2.h>

// サウンドファイル
typedef enum
{

	SOUND_LABEL_BGM000 = 0,		// サンプルBGM
	SOUND_LABEL_BGM001,			// サンプルBGM
	SOUND_LABEL_SE000,			// サンプルSE
	SOUND_LABEL_SE001,			// サンプルSE



	SOUND_LABEL_MAX,
} SOUND_LABEL;

// パラメータ構造体
typedef struct
{
	LPCSTR filename;	// 音声ファイルまでのパスを設定
	bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
	bool SandW;			//! 音の強弱の切り替えが必要なサウンドを判定
	float volume;		//! 音の大きさ（1.0fがノーマル)
} PARAM;		//PARAM型構造体

class Sound {

private:
	

	PARAM m_param[SOUND_LABEL_MAX] =
	{
		{"asset/BGM/○○○.wav", true,true,1.0f},	// サンプルBGM（ループさせるのでtrue設定）
//		{"asset/BGM/○○○.wav", true},	// サンプルBGM
//		{"asset/SE/○○○.wav", false},  		// サンプルSE（ループしないのでfalse設定）
//		{"asset/SE/○○○.wav", false},		// サンプルSE



	};

	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX]; // WAVフォーマット
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_MAX];
	BYTE* m_DataBuffer[SOUND_LABEL_MAX];

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

	int Distance = 0;	//プレイヤーとオブジェクトの距離をもらう変数

public:
	// ゲームループ開始前に呼び出すサウンドの初期化処理
	HRESULT Init(void);

	// ゲームループ終了後に呼び出すサウンドの解放処理
	void Uninit(void);

	// 引数で指定したサウンドを再生する
	void Play(SOUND_LABEL label);		//enumで決めたデータで引数として渡している

	// 引数で指定したサウンドを停止する
	void Stop(SOUND_LABEL label);

	//! 引数で指定したサウンドの音量を変更する	//後から追加（出口）
	void ChangeVolume(SOUND_LABEL label,int );

	// 引数で指定したサウンドの再生を再開する
	void Resume(SOUND_LABEL label);

	//volume変数のセッター・ゲッター関数（音量調整のため）
	int SetDistance(int);
	int GetDistance(void);

	/*===サウンドフレームワーク設計===*/

	/*
	音の停止
	音の再生
	音のループ
	シーンごとでの音楽の切り替え(少し違うかも)
	音の強弱（ゲームシステム上画面外なら小さくなど）これが一番問題？
	*/
};