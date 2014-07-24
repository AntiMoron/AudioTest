#include "SoundClass.h"

SoundClass::SoundClass()
{
	m_DirectSound = nullptr;
	m_primaryBuffer = nullptr;
	m_secondaryBuffer1 = nullptr;
	m_audioDevice = nullptr;
}


SoundClass::~SoundClass()
{
}


HRESULT SoundClass::Initialize(HWND hwnd)
{
	HRESULT hr = S_OK;
	m_hWnd = hwnd;

	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;


	// Initialize the direct sound interface pointer for the default sound device.
	hr = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
	if (FAILED(hr))
	{
		return hr;
	}

	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	hr = m_DirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(hr))
	{
		return hr;
	}

	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Get control of the primary sound buffer on the default sound device.
	hr = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if (FAILED(hr))
	{
		return hr;
	}
	//Read Sound File right now;
	m_audioDevice = new AudioDevicePtr(OpenDevice());
	if (m_audioDevice == nullptr)
	{
		printf("No device\r\n");
		return E_FAIL;
	}
	m_soundData = new OutputStreamPtr(OpenSound(*m_audioDevice, "Sober.mp3", false));
	if (m_soundData == nullptr)
	{
		printf("No Sound File Found.\r\n");
		return E_FAIL;
	}
	printf("Sound Loaded Ok.\r\n");
	

	m_source.push_back(0);
	m_source.push_back(-20);
	m_source.push_back(-40);
	m_source.push_back(-60);
	//waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	//waveFormat.nSamplesPerSec = 44100;
	//waveFormat.wBitsPerSample = 16;
	//waveFormat.nChannels = 2;
	//waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	//waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	//waveFormat.cbSize = 0;

	//// Set the primary buffer to be the wave format specified.
	//hr = m_primaryBuffer->SetFormat(&waveFormat);
	//if (FAILED(hr))
	//{
	//	return false;
	//}

	return hr;
}

HRESULT SoundClass::Shutdown()
{
	if (m_DirectSound != nullptr)
	{
		m_DirectSound->Release();
		m_DirectSound = nullptr;
	}
	if (m_primaryBuffer != nullptr)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = nullptr;
	}
	if (m_secondaryBuffer1 != nullptr)
	{
		m_secondaryBuffer1->Release();
		m_secondaryBuffer1 = nullptr;
	}
	return S_OK;
}

bool SoundClass::Play()
{
	if ((*m_soundData)->getPosition() <= (*m_soundData)->getLength())
		(*m_soundData)->play();
	else
		(*m_soundData)->stop();
	return (*m_soundData)->getPosition() <= (*m_soundData)->getLength();
}