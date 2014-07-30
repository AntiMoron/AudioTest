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
	OutputStream* m_soundDataStream = OpenSound(*m_audioDevice, "Sober.mp3", false);
	m_soundData = new OutputStreamPtr(m_soundDataStream);
	if (m_soundData == nullptr)
	{
		printf("No Sound File Found.\r\n");
		return E_FAIL;
	}
	printf("Sound Loaded Ok.\r\n");
	int channel_count, sample_rate;
	SampleFormat sf;
	SampleSource x; x.getFormat(channel_count, sample_rate, sf);
	printf("Sound Length : %d",(*m_soundData)->getLength() / channel_count);
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
	(*m_soundData)->play();
	return true;
}