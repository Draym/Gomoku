#pragma once

#include <map>
#include "Graphic\Sfml.h"
#include "Utils\Exception.h"

enum class ESound {
	NONE,
	CHINESE2,
	DREAMTEMPLE,
	END
};

class SoundMixer
{
public:
	static void		init();
	static void		launch(ESound sound);
	static void		launchNext();
	static void		start();
	static void		stop();
	static void		pause();
	static void		mute(bool value);
	static void		reverseMute();
private:
	static ESound						current;
	static std::map<ESound, sf::Music>	musics;
};

