#include "stdafx.h"
#include "SoundGo.h"

SoundGo::SoundGo()
	:soundMute(true), currentMuteCheck(false)
{
	
}

SoundGo::~SoundGo()
{

}

void SoundGo::Init()
{
	bufferBackground.loadFromFile("sound/title_music.wav");
	soundBackground.setBuffer(bufferBackground);
}

void SoundGo::Play()
{
	soundBackground.play();
}