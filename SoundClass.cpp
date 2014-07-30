#include "SoundClass.h"

SoundClass::SoundClass()
{
	m_audioDevice = nullptr;
}


SoundClass::~SoundClass()
{
}


HRESULT SoundClass::Initialize(HWND hwnd)
{
	HRESULT hr = S_OK;
	m_hWnd = hwnd;

	//Read Sound File right now;
	m_audioDevice = new AudioDevicePtr(OpenDevice());
	if (m_audioDevice == nullptr)
	{
		printf("No device\r\n");
		return E_FAIL;
	}
	OutputStream* m_soundDataStream = OpenSound(*m_audioDevice, "Sober.mp3", false);
	m_soundData = new OutputStreamPtr(m_soundDataStream);
	if (m_soundData == nullptr)
	{
		printf("No Sound File Found.\r\n");
		return E_FAIL;
	}
	m_soundData2 = new OutputStreamPtr(m_soundDataStream);
	(*m_soundData)->play();
	Sleep(1000);
	(*m_soundData2)->play();
	printf("Sound Loaded Ok.\r\n");
	return hr;
}

HRESULT SoundClass::Shutdown()
{
	return S_OK;
}

bool SoundClass::Play()
{
	return true;
}