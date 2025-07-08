class SoundGo :
	public Singleton<SoundGo>
{
protected:
	std::string soundId;

	sf::SoundBuffer bufferHit;
	sf::SoundBuffer bufferPickUp;

	sf::Sound soundHit;
	sf::Sound soundPickUp;

	bool soundMute;
	bool currentMuteCheck;

public:
	SoundGo();
	~SoundGo();

	void Init();
	void Play(std::string id);
	void MuteSet(bool mute);
	bool MuteGet();
};

#define SOUND_MGR (SoundGo::Instance())

