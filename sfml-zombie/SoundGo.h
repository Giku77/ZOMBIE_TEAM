#pragma once

class SoundGo :
	public Singleton<SoundGo>
{
protected:

public:
	std::string soundId;

	sf::SoundBuffer bufferBackground;
	sf::Sound soundBackground;

	bool soundMute;
	bool currentMuteCheck;
	SoundGo();
	~SoundGo();

	void Init();
	void Play();
};

#define SOUND_MGR (SoundGo::Instance())

