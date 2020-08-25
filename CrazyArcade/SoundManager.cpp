#include "stdafx.h"
#include "SoundManager.h"

FMOD_SYSTEM* CSound::g_sound_system;

CSound::CSound(const char* path, bool loop) {
	if (loop) {
		FMOD_System_CreateStream(g_sound_system, path, FMOD_LOOP_NORMAL, 0, &m_sound);
	}
	else {
		FMOD_System_CreateSound(g_sound_system, path, FMOD_DEFAULT, 0, &m_sound);
	}

	m_channel = nullptr;
	m_volume = SOUND_DEFAULT;
}

CSound::~CSound() {
	FMOD_Sound_Release(m_sound);
}


int CSound::Init() {
	FMOD_System_Create(&g_sound_system);
	FMOD_System_Init(g_sound_system, 32, FMOD_INIT_NORMAL, NULL);

	return 0;
}

int CSound::Release() {
	FMOD_System_Close(g_sound_system);
	FMOD_System_Release(g_sound_system);

	return 0;
}


int CSound::play() {
	FMOD_System_PlaySound(g_sound_system, FMOD_CHANNEL_FREE, m_sound, false, &m_channel);

	return 0;
}

int CSound::pause() {
	FMOD_Channel_SetPaused(m_channel, true);

	return 0;
}

int CSound::resume() {
	FMOD_Channel_SetPaused(m_channel, false);

	return 0;
}

int CSound::stop() {
	FMOD_Channel_Stop(m_channel);

	return 0;
}

int CSound::volumeUp() {
	if (m_volume < SOUND_MAX) {
		m_volume += SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(m_channel, m_volume);

	return 0;
}

int CSound::volumeDown() {
	if (m_volume > SOUND_MIN) {
		m_volume -= SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(m_channel, m_volume);

	return 0;
}


int CSound::Update() {
	FMOD_Channel_IsPlaying(m_channel, &m_bool);

	if (m_bool) {
		FMOD_System_Update(g_sound_system);
	}

	return 0;
}

SoundManager::SoundManager()
{
	CSound::Init();

	Sounds[0] = new CSound("/sounds/appear.wav", false);
	Sounds[1] = new CSound("/sounds/die.wav", false);
	Sounds[2] = new CSound("/sounds/draw.wav", false);
	Sounds[3] = new CSound("/sounds/explode.wav", false);
	Sounds[4] = new CSound("/sounds/get.wav", false);
	Sounds[5] = new CSound("/sounds/lay.wav", false);
	Sounds[6] = new CSound("/sounds/lose.wav", false);
	Sounds[7] = new CSound("/sounds/save.wav", false);
	Sounds[8] = new CSound("/sounds/start.wav", false);
	Sounds[9] = new CSound("/sounds/win.wav", false);
	Sounds[10] = new CSound("/sounds/bg/forest.mp3", true);
}


SoundManager::~SoundManager()
{
	delete[] Sounds;

	CSound::Release();
}
