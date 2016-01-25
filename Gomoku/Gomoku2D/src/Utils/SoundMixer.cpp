#include "Utils\SoundMixer.h"

ESound						SoundMixer::current = ESound::NONE;
std::map<ESound, sf::Music>	SoundMixer::musics;

void	SoundMixer::init() {
	if (!musics[ESound::CHINESE2].openFromFile("Resources/Sounds/chinese2.ogg"))
		throw Exception("Error", "can't open chinese2.ogg", "SoundMixer::init");
	if (!musics[ESound::DREAMTEMPLE].openFromFile("Resources/Sounds/dreamTemple.ogg"))
		throw Exception("Error", "can't open dreamTemple.ogg", "SoundMixer::init");
}

void SoundMixer::launch(ESound sound)
{
	stop();
	current = sound;
	start();
}

void SoundMixer::launchNext()
{
	int	value = (int)current;

	value = (value + 1 >= (int)ESound::END ? 1 : value + 1);
	stop();
	current = static_cast<ESound>(value);
	start();
}

void SoundMixer::start()
{
	if (current != ESound::NONE && current != ESound::END)
		musics[current].play();
}

void SoundMixer::stop()
{
	if (current != ESound::NONE && current != ESound::END)
		musics[current].stop();
}

void SoundMixer::pause()
{
	if (current != ESound::NONE && current != ESound::END)
		musics[current].pause();
}

void SoundMixer::mute(bool value)
{
	if (current != ESound::NONE && current != ESound::END) {
		if (value) {
			musics[current].setVolume(0);
		}
		else {
			musics[current].setVolume(100);
		}
	}
}

void SoundMixer::reverseMute()
{
	if (current != ESound::NONE && current != ESound::END) {
		if (musics[current].getVolume() == 0) {
			mute(false);
		}
		else {
			mute(true);
		}
	}
}

