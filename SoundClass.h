#pragma once
#include<Windows.h>
#include<mmsystem.h>
#include<dsound.h>
#include<audiere.h>
#include<vector>
#include<thread>
using namespace audiere;
#pragma comment(lib, "audiere.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

class SoundClass
{
public:
	SoundClass();
	~SoundClass();

	HRESULT Initialize(HWND hwnd);
	HRESULT Shutdown();

	bool Play();
private:
	HWND m_hWnd;
	OutputStreamPtr* m_soundData;
	AudioDevicePtr* m_audioDevice;
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;
	IDirectSoundBuffer8* m_secondaryBuffer1;
};

