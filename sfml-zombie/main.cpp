#include "stdafx.h"

int main()
{
    sf::Music bgm;
    if (!bgm.openFromFile("sound/title_music.wav")) {
        return -1;
    }
    
    bgm.setLoop(true);      
    bgm.setVolume(50.f);   
    bgm.play();            

    /*while (bgm.getStatus() == sf::SoundSource::Playing) {
        sf::sleep(sf::milliseconds(100));
    }*/
    FRAMEWORK.Init(1280, 720, "Pong!!");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}