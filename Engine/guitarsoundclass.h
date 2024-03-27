///////////////////////////////////////////////////////////////////////////////
// Filename: guitarsoundclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _GUITARSOUNDCLASS_H_
#define _GUITARSOUNDCLASS_H_

/////////////
// LINKING //
/////////////
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>


///////////////////////////////////////////////////////////////////////////////
// Class name: GuitarSoundClass
///////////////////////////////////////////////////////////////////////////////
class GuitarSoundClass
{
private:
	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

public:
	GuitarSoundClass();
	GuitarSoundClass(const GuitarSoundClass&);
	~GuitarSoundClass();

	bool Initialize(HWND);
	void Shutdown();

	bool PlayWaveFile(bool);
private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();

	bool LoadWaveFile(char*, IDirectSoundBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**);

private:
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;

	IDirectSoundBuffer8* m_secondaryBuffer1;
};

#endif